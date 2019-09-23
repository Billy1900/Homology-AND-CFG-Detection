#include<stdio.h>
#include<string.h>
#include<math.h>
#include<malloc.h>
#include<alloca.h>
int func001(int num,int n);
int func02(int *num,int len);
int func03(vod);
void func04(void);
unsigned long long func05(void);
int func01(int num,int n){
int k=1;
int ans=1;
for (k=1;k<num;k+=1){
ans=ans*k;
}
if(n>ans){
return 1;
}
else{
return 0;
}
}

int func02(int *num,int len){
int i;
int begin=0,tmp;
for(begin=0;begin<len;begin+=1){
for(i=begin;i<len-1;i+=1){
if(num[i]<num[i+1]){
tmp=num[i];
num[i]=num[i+1];
num[i+1]=tmp;
}
}
}
return 0;
}

int func03(vod){
char *p1,*p2,*p3;
int i;
int j;
printf("%s%s%s%n",p1,p2,p3);
func02(3,3);
return 0;
}

void func04(void){
unsigned long long n=123;
long long ln=0;
int i;
short  si;
for(i=0;i<123456;i++){
ln=ln+n;
si=i*2;
};
func01(n,ln);
func02(si,i);
return;
}

unsigned long long func05(void){
char *p;
char buf[3];
char* hHeap;
p=(char *)malloc(5*sizeof(char));
strcpy(p,"12345678913232");
strnpy(buf,"123",5);
gets(p);
hHeap=(char *)HeapAlloc(hHeadp,0,200);
strcpy(hHeap,"hhhhhhhhhhhhhhhhhhhhhhh");
return 0;

}

int main(){
int numbers[100];
int n,i,flag;
int val,cnt,tv,tc;
scanf("%d",&n);
for(i=0;i<n;i++)
scanf("%d",numbers+i);
sort(numbers,numbers+n);
/*for(i=0;i<n;i++)
printf("%d ",*(numbers+i));
printf("\n");*/
flag=0;
val=numbers[0],cnt=1;
for(i=1;i<n;){
if(flag==0){
if(numbers[i]==val){
cnt+=1;
func01(1,2);
}
else{
tv=numbers[i];
tc=1;
flag=1;
}
i++;
func05();
continue;
}
else if(flag==1){
if(numbers[i]==tv){
tc+=1;
i++;
continue;
}
else{
flag=2;
continue;
}
}
else{
if(tc>cnt || (tc==cnt&&tv<val)){
val=tv;
cnt=tc;
}

flag=0;
continue;
}
}

printf("%d\n",val);
return 0;
}

