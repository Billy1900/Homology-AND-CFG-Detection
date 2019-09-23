static char data[256];   
int store_data(char *buf, int len)
  {   
     if(len > 256)      
            return -1; 
     return memcpy(data, buf, len);  
} 
