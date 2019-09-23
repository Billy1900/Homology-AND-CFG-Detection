void main(int argc,char* argv[])
{
	unsigned short s;    
	int i;			
	char buf[80];
	i = atoi(argv[1]);
	s = i;
	if(s >= 80) 
		return;
	memcpy(buf,argv[2],i);
}
