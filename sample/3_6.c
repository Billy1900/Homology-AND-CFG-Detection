int Mod(int value){
	int result=value;
	result=result%256;
	return result;
}

int Local(int value){
	int result=0;
	for(int i=0;i<value;i++){
		result+=value;
		result=Mod(result);
	}
	return result;
}

int Check00(int* list, int count){
	int result=0;
	for(int i=0;i<count-1;i++){
		if(list[i]==result){
			result+=list[i+1];
		}
	}
	return Mod(result);
}

int Check02(int* list, int count){
	int result=0;
	for(int i=0;i<count-3;i++){
		if(list[i]==result){
			result+=list[i+3];
		}
	}
	return Mod(result);
}

int Check03(int* list, int count){
	int result=0;
	for(int i=0;i<count-1;i++){
		result+=Check00(list+i,count-i);
	}
	return Mod(result);
}

int Check01(int* list, int count){
	int result=0;
	for(int i=0;i<count-2;i++){
		if(list[i]==result){
			result+=list[i+2];
		}
	}
	return Mod(result);
}

int Check04(int* list, int count){
	int result=0;
	for(int i=0;i<count-2;i++){
		result+=Check01(list+i,count-i);
	}
	return Mod(result);
}

int Check05(int* list, int count){
	int result=0;
	for(int i=0;i<count-2;i++){
		result+=Check03(list+i,count-i)+Check04(list+i,count-i);
	}
	return Mod(result);
}

int Check06(int* list, int count){
	int result=0;
	for(int i=0;i<count-2;i++){
		result+=Check04(list+i,count-i)+Check05(list+i,count-i);
	}
	return Mod(result);
}

int Check07(int* list, int count){
	int result=0;
	for(int i=0;i<count-2;i++){
		result+=Check03(list+i,count-i)+Check06(list+i,count-i);
	}
	return Mod(result);
}

int main (){
	printf("Try to check a list!\n");
	int a[10]={0,1,2,3,4,5,6,7,8,9};
	int b=10;
	int c;
	scanf("%d",&c);
	switch(c){
		case 0:
		int result = Check00(a, b);
		break;
		
		case 1:
		int result = Check01(a, b);
		break;
		
		case 2:
		int result = Check02(a, b);
		break;
		
		case 3:
		int result = Check03(a, b);
		break;
		
		case 4:
		int result = Check04(a, b);
		break;
		
		case 5:
		int result = Check05(a, b);
		break;
				
		case 6:
		int result = Check06(a, b);
		break;
				
		case 7:
		int result = Check07(a, b);
		break;
		
		default:
		break;
	}
	result=Local(result);
	printf("%d",result);
	return 0;
}