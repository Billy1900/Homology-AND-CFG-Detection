char mybuf2[450] ;
int main (int argc, char *argv[])
{
	HANDLE hHeap;
	char *buf1, *buf2;
	int i;
    
for(int i=0;i<450;i++){
 mybuf2[i]=’a’;
}	
LoadLibrary("user32");
	hHeap=HeapCreate(HEAP_GENERATE_EXCEPTIONS, 0x10000, 0xfffff);
	buf1 =(char*) HeapAlloc(hHeap, 0, 200);
	strcpy(buf1,mybuf2);
	buf2 =(char*) HeapAlloc(hHeap, 0, 200);
	HeapFree(hHeap, 0, buf1);
	HeapFree(hHeap, 0, buf2);
	return 0;
}
