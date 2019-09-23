int Add(int x, int y){
	int work=x+y;
	return work;
}

int Gank00(int* list, int count){
	int work=0;
	for(int i=0;i<count-1;i++){
		if(list[i]==work){
			work=Add(work,list[i+1]);
		}
	}
	return Mod256(work);
}

int Gank01(int* list, int count){
	int work=0;
	for(int i=0;i<count-2;i++){
		if(list[i]==work){
			work=Add(work,list[i+2]);
		}
	}
	return Mod256(work);
}

int Gank02(int* list, int count){
	int work=0;
	for(int i=0;i<count-3;i++){
		if(list[i]==work){
			work=Add(work,list[i+3]);
		}
	}
	return Mod256(work);
}

int Gank03(int* list, int count){
	int work=0;
	for(int i=0;i<count-1;i++){
		work=Add(work,Gank00(list+i,count-i));
	}
	return Mod256(work);
}

int Gank04(int* list, int count){
	int work=0;
	for(int i=0;i<count-2;i++){
		work=Add(work,Gank01(list+i,count-i));
	}
	return Mod256(work);
}

int Gank05(int* list, int count){
	int work=0;
	for(int i=0;i<count-2;i++){
		work=Add(work,Gank03(list+i,count-i));
	}
	return Mod256(work);
}

int Mod256(int value){
	int work=value;
	work=work%256;
	return work;
}

int Local(int value){
	int work=0;
	for(int i=0;i<value;i++){
		work+=value;
		work=Mod256(work);
	}
	return work;
}

int main (){
	printf("Try to Gank a list!\n");
	int a[10]={0,1,2,3,4,5,6,7,8,9};
	int b=10;
	int c;
	scanf("%d",&c);
	switch(c){
		case 0:
		int work = Gank00(a, b);
		break;
		
		case 1:
		int work = Gank01(a, b);
		break;
		
		case 2:
		int work = Gank02(a, b);
		break;
		
		case 3:
		int work = Gank03(a, b);
		break;
		
		case 4:
		int work = Gank04(a, b);
		break;
		
		case 5:
		int work = Gank05(a, b);
		break;
		
		default:
		break;
	}
	work=Local(work);
	printf("%d",work);
	return 0;
}