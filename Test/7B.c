int main(int argc, char* argv[]) 
{ 
unsigned short total = strlen(argv[1]) + strlen(argv[2]) + 1; 
char* buffer = (char*)malloc(total); 
strcpy(buffer, argv[1]); 
strcat(buffer, argv[2]); 
free(buffer); 
return 0; 
}
