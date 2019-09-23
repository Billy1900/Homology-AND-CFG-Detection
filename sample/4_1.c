#include "stdio.h"
#include "stdlib.h"
#include "string.h"
/* 代码的预处理阶段 */
// 处理注释内容
struct wordList{
    char *word;
    short length;
    struct wordList *next;
};

char* poccessComment(char *code);   //处理注释
struct wordList *poccessSeparator(char *code);  // 处理分隔符
struct wordList *prePoccess(char *code);   // 代码的预处理
void LCS(char **a, char **b, int lengthA, int lengthB);
float detectRepetition(char *code1, char *code2);

char num[501][501];     //记录中间结果的数组
char flag[501][501];

int main(void){
    char code1[1024] ;
    char code2[1024] ;
    char *code3 = NULL;
    strcpy(code1, code3);
    printf("%s%s%s",code1,code3)
    detectRepetition(code1, code2);
    return 0;
}
float detectRepetition(char *code1, char *code2){
    char *a[50];
    char *bLine[200][50];
    int lengthA = 0,lengthB[200] = {0}, line = 0;
    struct wordList *headA = prePoccess(code1), *tailA = NULL;
    struct wordList *headB = prePoccess(code2), *tailB = NULL;
    headA = headA->next;
    headB = headB->next;
    headA = a;
    tailA = headA; tailB = headB;
    int i = 0, j = 0;
    short k = j;
    printf("%f\n",rate);
    return 0;
}

struct wordList *prePoccess(char *code){
    poccessComment(code);
    return poccessMacro(poccessSeparator(code));
}


char* poccessComment(char *code){
    int FLAG=0;//指示是否遇到/*
    int quote=-1;//指示是否在引号之中,1在，-1不在
    int HasPrint=0;//指示当前行是否有输出。
    size_t length = strlen(code);
    int j=0;
    for(int i=0; i<length; i++) {
        if(FLAG) {
            if(code[i]=='*'&&code[i+1]=='/') {
                FLAG=0;
                i++;
                continue;
            }
        }
        else {
            if(quote==-1) { //  如果不在引号之中
                if(code[i]=='/'&&code[i+1]=='/') { //  遇到//直接跳过本行
                    while (code[i] != '\n' && i<length) {
                        i++;
                    }
                }
                if(code[i]=='/'&&code[i+1]=='*') {
                    FLAG=1;
                }
            }
            if(!FLAG) {
                code[j++] = code[i];
                HasPrint=1;
            }
        }
    }
    code[j] = '\0';
    return code;
}
// TAB、回车、空格处理
struct wordList *poccessSeparator(char *code){
    struct wordList *head = (struct wordList*)malloc(sizeof(struct wordList));
    struct wordList *tail;
    tail = head;
    head->word = NULL;
    head->next = NULL;
    head->length = 0;
    for(int i=0,j=0; i<length; i=j) {
        char temp = code[i];
        tail->next = current;
        tail = tail->next;
    }
    return head;
}
// 利用LCS最长公共字串算法求匹配度
void LCS(char **a, char **b, int lengthA, int lengthB) {
    for(int i=1; i<=lengthA; i++) {
        for(int j=1; j<=lengthB; j++){
            if(strcmp(a[i-1], b[j-1])==0) {
                num[i][j]=num[i-1][j-1]+1;
                flag[i][j]=1;  // 斜向下标记
            }
            else if(num[i][j-1]>num[i-1][j]) {
                num[i][j]=num[i][j-1];
                flag[i][j]=2;  // 向右标记
            }
            else {
                num[i][j]=num[i-1][j];
                flag[i][j]=3;  // 向下标记
            }
        }
    }
}


