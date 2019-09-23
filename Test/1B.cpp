	typedef int INTEGER; 
	typedef INTEGER int16; 
	static int16 do_poll(struct pllfd *pfd,unsigned int nfds,int16 timeout)
	{
	   int16 ret;
	   ret=poll(pfd,nfds,timeout);
	   if (ret<0){
	      if(errno==EINTR)
	         return 0;
	       log(LOG_ERR,"poll returned an error!\n");
	       return -1;
	   }
	   if (ret==0)
	       return 0;
	    return 1;
	 }
