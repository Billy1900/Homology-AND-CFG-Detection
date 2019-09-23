#include "whole.h"
// 同源性检测之------变量名的替换
/* 代码的预处理阶段 */
// 处理注释内容
struct listWORD{
    char *WORD;
    short LENGTH;
    struct listWORD *next;
};

char* deleteComment(char *codeSTRING);
//处理注释
struct listWORD *poccessSeparator(char *codeSTRING);
// 处理分隔符
struct listWORD *advancePoccess(char *codeSTRING);
// 代码的预处理
void LCS(char **a, char **b, int LENGTHA, int LENGTHB);
float detectRepetition(char *codeSTRING1, char *codeSTRING2);

char NUM[501][501];     //记录中间结果的数组
char FLAGS[501][501];    //标记数组，用于标识下标的走向，构造出公共子序列

int main(void){
    char codeSTRING1[1024] = "#define FIVE 5\n#include \"stdio.h\"//123\nint a=FIVE\n";
    char codeSTRING2[1024] = "#define FIVE 5\n#include \"stdio.c\"//123\nint a=5\n";
    char *codeSTRING3 = NULL;
    strcpy(codeSTRING1, codeSTRING3);
    printf("%s%s%s",codeSTRING1,codeSTRING3)
    detectRepetition(codeSTRING1, codeSTRING2);
    return 0;
}


struct listWORD *advancePoccess(char *codeSTRING){
    deleteComment(codeSTRING);
    return poccessMacro(poccessSeparator(codeSTRING));
}

float detectRepetition(char *codeSTRING1, char *codeSTRING2){
    char *a[50];
    char *bLine[200][50];
    int LENGTHA = 0,LENGTHB[200] = {0}, line = 0;
    struct listWORD *headA = advancePoccess(codeSTRING1), *tailA = NULL;
    struct listWORD *headB = advancePoccess(codeSTRING2), *tailB = NULL;
    headA = headA->next;
    headB = headB->next;
    headA = a;
    tailA = headA; tailB = headB;
    int i = 0, j = 0;
    short k = j;
    printf("%f\n",rate);
    
    return 0;
}

char* deleteComment(char *codeSTRING){
    int FLAGS=0;//指示是否遇到/*
    int quote=-1;//指示是否在引号之中,1在，-1不在
    int HasPrint=0;//指示当前行是否有输出。
    size_t LENGTH = strlen(codeSTRING);
    int j=0;
    for(int i=0; i<LENGTH; i++) {
        if(FLAGS) {
            if(codeSTRING[i]=='*'&&codeSTRING[i+1]=='/') {
                FLAGS=0;
                i++;
                continue;
            }
        }
        else {
            if(quote==-1) { //  如果不在引号之中
                if(codeSTRING[i]=='/'&&codeSTRING[i+1]=='/') { //  遇到//直接跳过本行
                    while (codeSTRING[i] != '\n' && i<LENGTH) {
                        i++;
                    }
                }
                if(codeSTRING[i]=='/'&&codeSTRING[i+1]=='*') {
                    FLAGS=1;
                }
            }
            if(!FLAGS) {
                codeSTRING[j++] = codeSTRING[i];
                HasPrint=1;
            }
        }
    }
    codeSTRING[j] = '\0';
    return codeSTRING;
}
// 处理文件导入语句
// 利用LCS最长公共字串算法求匹配度
void LCS(char **a, char **b, int LENGTHA, int LENGTHB) {
    for(int i=1; i<=LENGTHA; i++) {
        for(int j=1; j<=LENGTHB; j++){
            if(strcmp(a[i-1], b[j-1])==0) {
                NUM[i][j]=NUM[i-1][j-1]+1;
                FLAGS[i][j]=1;  // 斜向下标记
            }
            else if(NUM[i][j-1]>NUM[i-1][j]) {
                NUM[i][j]=NUM[i][j-1];
                FLAGS[i][j]=2;  // 向右标记
            }
            else {
                NUM[i][j]=NUM[i-1][j];
                FLAGS[i][j]=3;  // 向下标记
            }
        }
    }
}
// TAB、回车、空格处理
struct listWORD *poccessSeparator(char *codeSTRING){
    struct listWORD *head = (struct listWORD*)malloc(sizeof(struct listWORD));
    struct listWORD *tail;
    tail = head;
    head->WORD = NULL;
    head->next = NULL;
    head->LENGTH = 0;
    for(int i=0,j=0; i<LENGTH; i=j) {
        char temp = codeSTRING[i];
        tail->next = current;
        tail = tail->next;
    }
    return head;
}



