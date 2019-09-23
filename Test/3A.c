int AFunc(int i,int j)
{
int m = 3;
int n = 4;
    char szBuf[8] = {0}; 
    strcpy(szBuf, “This is a overflow buffer!”)；
  m = i;
    n = j;
  return 8;
}
