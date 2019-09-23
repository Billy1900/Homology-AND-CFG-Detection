void CopyIntArray(int *array,int len)
{
	int* myarray,i;
	myarray = malloc(len*sizeof(int));
	if(myarray == NULL)
		return;
	for(i=0;i<len;i++)
		myarray[i] = arrary[i];
}
