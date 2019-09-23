	int DES_Encrypt(char *plainFile, char *keyStr,char *cipherFile){  
	    ElemType plainBlock[8],cipherBlock[8],keyBlock[8];  
	    ElemType bKey[64];  
	    ElemType subKeys[16][48]; 
	    FILE *plain,*cipher;  
	    int count;  
	    
	    if((plain = fopen(plainFile,"rb")) == NULL){  
	  return PLAIN_FILE_OPEN_ERROR; 
	}     
	    if((cipher = fopen(cipherFile,"wb")) == NULL){  
	        return CIPHER_FILE_OPEN_ERROR;  
	    }  	

	    memcpy(keyBlock,keyStr,8);   
	    Char8ToBit64(keyBlock,bKey);    
	    DES_MakeSubKeys(bKey,subKeys);  	      
	    while(!feof(plain)){  	          
	        if((count = fread(plainBlock,sizeof(char),8,plain)) == 8){  
	            DES_EncryptBlock(plainBlock,subKeys,cipherBlock);  
	            fwrite(cipherBlock,sizeof(char),8,cipher);    
	        }  
	    }  

	    if(count){  	         
	        memset(plainBlock + count,'\0',7 - count);  
	        plainBlock[7] = 8 - count;  
	        DES_EncryptBlock(plainBlock,subKeys,cipherBlock);  
	        fwrite(cipherBlock,sizeof(char),8,cipher);  
	    }  
	    fclose(plain);  
	    fclose(cipher);  
	 return OK;  
	}
