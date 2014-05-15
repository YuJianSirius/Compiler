//
//  LexicalAnalysis.c
//  Compiler
//
//  Created by xiaojia on 4/15/14.
//  Copyright (c) 2014 sirius. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "string.h"

// ---------------- 关键词表 ----------------------
char *keyword[] = {"auto","double","int","struct","break","else","long","switch","case","enum","register",
        "typedef","char","extern","return","union","const","float","short","unsigned","continue","for",
         "signed","void","default","goto","sizeof","volatile","do","while","static","if"};

// ---------------- 运算符表 ----------------------
char *operator[] = {"+", "-" ,"*", "/" , "<" ,">"};
    
// ---------------- 限界符表 ----------------------
char *boundword[] = {"=",";",",","\"",":","(",")","."};

//关键词种别码
#define AUTO       1
#define DOUBLE     2
#define INT        3
#define STRUCT     4
#define BREAK      5
#define ELSE       6
#define LONG       7
#define SWITCH     8
#define CASE       9
#define ENUM      10
#define REGISTER  11
#define TYPEDEF   12
#define CHAR      13
#define EXTERN    14
#define RETURN    15
#define UNION     16
#define CONST     17
#define FLOAT     18
#define SHORT     19
#define UNSIGNED  20
#define CONTINUE  21
#define FOR       22
#define SIGNED    23
#define VOID      24
#define DEFAULT   25
#define GOTO      26
#define SIZEOF    27
#define VOLATITLE 28
#define DO        29
#define WHILE     30
#define STATIC    31
#define IF        32
#define KEY_DESC  "关键字"

//标识符种别码
#define IDENTIFER 40
#define IDENTIFER_DESC "标识符"

//常量标种别码
#define INT_VAL     51   //整形常量
#define CHAR_VAL    52   //字符常量
#define FLOAT_VAL   53   //单精度浮点数常量
#define DOUBEL_VAL  54   //双精度浮点数常量
#define CONSTANT_DESC "常量"

//运算符
#define ADD 60   //+
#define SUB 61   //-
#define MUL 62   //*
#define DIV 63   ///
#define LESS_THAN    64  //<
#define GTEATER_THAN 65  //>
#define OPERATOR_DESC "运算符"

//限界符
#define EQU 100  //=
#define SEM 101  //;
#define COM 102  //,
#define DOUBLE_QUO 103  //"
#define COL 104  //:
#define LEFT_PAR  105 //(
#define RIGHT_PAR 106 //)
#define BOUNTWROD_DESC "限界符"

#define NOTE1 150 // //注释//
#define NOTE2 151 // /*注释*/
#define NOTE_DESC "注释"

#define HEADER 160 // 头文件
#define HEADER_DESC "头文件"

#define MAX_CHAR_NUMBER   100000
char charSET[MAX_CHAR_NUMBER];

typedef struct NormalNode
{
    char content[50];
    char description[30];
    int  type;
    int  address;
    int  line;
    struct NormalNode *next;
}NormalNode;

typedef struct IdentiferNode
{
    char content[50];
    char description[30];
    int  type;
    int  address;
    int  line;
    struct IdentiferNode *next;
}IdentiferNode;


NormalNode *normalHead;
IdentiferNode *identiferHead;

void initNode()
{
    normalHead = (NormalNode *)malloc(sizeof(NormalNode));
    strcpy(normalHead->content,  "");
    strcpy(normalHead->description, "");
    normalHead->type = -1;
    normalHead->address = -1;
    normalHead->line = -1;
    normalHead->next = NULL;
    
    identiferHead = (IdentiferNode *)malloc(sizeof(IdentiferNode));
    strcpy(identiferHead->content, "");
    strcpy(identiferHead->description, "");
    identiferHead->type = -1;
    identiferHead->address = -1;
    identiferHead->line = -1;
    identiferHead->next = NULL;
}

void createNewNode(char *content,char *describe,int type,int address,int line)
{
    NormalNode *p = normalHead;
    NormalNode *tmp = (NormalNode *)malloc(sizeof(NormalNode));
    
    while ( p->next != NULL) {
        p = p->next;
    }
    
    strcpy(tmp->content,content);
    strcpy(tmp->description,describe);
    tmp->type = type;
    tmp->address = address;
    tmp->line = line;
    tmp->next = NULL;
    
    p->next = tmp;
}

int createIdeNode(char *content,char *describe,int type,int address,int line)
{
    IdentiferNode *p = identiferHead;
    IdentiferNode *tmp = (IdentiferNode *)malloc(sizeof(IdentiferNode));
    
    int address_count = 1;
    
    while (p->next != NULL){
        p = p -> next;
        address_count++;
        if(!strcmp(p->content, content))          //标识符已经存在
            return p->address;
    }
    strcpy(tmp->content,content);
    strcpy(tmp->description,describe);
    tmp->type = type;
    tmp->address = address_count;
    tmp->line = line;
    tmp->next = NULL;
    
    p->next= tmp;
    
    return tmp->address;
}

void displaynormalNode()
{
    NormalNode *p = normalHead;
    
    printf("%6内容%10描述%8种别码%5内存地址%6行号\n");
    
    while ( (p = p -> next)) {
        printf("%10s",p->content);
        printf("%15s",p->description);
        printf("%10d",p->type);
        if (p->address!=-1) {
            printf("%10d",p->address);
        }else{
            printf("          ");
        }
        printf("%10d",p->line);
        printf("\n");
    }
}

int marchID(char *word)
{
    for (int i = 0; i < 32; i++) {
        if(strcmp(word, keyword[i]) == 0){
            return i+1;
        }
    }
    return IDENTIFER;
}

void preProcess(char *word, int line)
{
    const char *head_define = "define";
    const char *head_include = "include";
    
    
    
    
    
}


int main(){
    
    initNode();
    FILE *fp;
    char ch;
    int count = 0;
    int line  = 1;
    
    char tmp[30];
    char *word;    //  保存description
    
    if((fp = fopen("/users/xiaojia/desktop/options.txt", "r")) == NULL){
        printf("文件不存在");
    }

    while( ch!= EOF){
        ch = fgetc(fp);
        //putchar(ch);
        
        
        //处理注释
        if (ch == '/') {
            ch = fgetc(fp);
            
            //处理    //类型//
            if(ch == '/') {
                while (ch != ' ' && ch != '\n') {
                    ch = fgetc(fp);
                }
                createNewNode("空", NOTE_DESC, NOTE1, -1, line);
            }
            
            //处理    /*类型注释*/
            else if(ch == '*'){
                line++;
                ch = fgetc(fp);
                while (ch != '*'){
                    ch = fgetc(fp);
                    if(ch == '\n'){
                        line++;
                    }
                }while (ch != '/'){
                    ch = fgetc(fp);
                }
                createNewNode("空", NOTE_DESC, NOTE2, -1, line);
            }
            
            //处理 运算符/
            else {
                createNewNode("/", OPERATOR_DESC, DIV, -1, line);
            }
        }
        
        //处理关键字和标识符
        if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_'){
            count = 0;
            while ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_') {
                tmp[count++] = ch;
                ch = fgetc(fp);
            }
            word = (char *)malloc(sizeof(char)*count);
            memcpy(word, tmp, count);
            word[count] = '\0';
            int id = marchID(word);
            if (id == IDENTIFER ) {
                int address_id = createIdeNode(word, IDENTIFER_DESC, IDENTIFER, -1, line);
                createNewNode(word, IDENTIFER_DESC, IDENTIFER, address_id, line);
            }else{
                createNewNode(word, KEY_DESC, id, -1, line);
            }
            fseek(fp,-1L,SEEK_CUR);//向后回退一位
        }
        
        
        //处理数字常量
        else if(ch >= '0' && ch <= '9'){
            count = 0;
            int isFloat = 0;
            int isDouble = 0;
            while (ch >= '0' && ch <= '9') {
                tmp[count++] = ch;
                ch = fgetc(fp);
            }
            
            //处理float
            if (ch == '.') {
                isFloat = 1;
                tmp[count++] = ch;
                ch = fgetc(fp);
                if (ch >= '0' && ch <= '9') {
                    while (ch >= '0' && ch <= '9' ){
                        tmp[count++] = ch;
                        ch = fgetc(fp);
                    }
                }else{
                    isFloat = -1;      //出错，-1表示 小数点后没有数字.
                }
            }
            
            //处理double
            if(ch == 'E' || ch == 'e'){
                isDouble = 1;
                tmp[count++] = ch;
                ch = fgetc(fp);
                if (ch == '+' || ch == '-') {
                    tmp[count++] = ch;
                    ch = fgetc(fp);
                }
                if (ch >= '0' && ch <= '9') {
                    tmp[count++] = ch;
                    ch = fgetc(fp);
                }else{
                    isDouble = -1;    //出错，-1表示 E后面的格式不对.
                }
            }
            
            word = (char *)malloc(sizeof(char)*(count+1));
            memcpy(word, tmp, count);
            word[count] = '\0';
            if (isFloat==1) {
                createNewNode(word, CONSTANT_DESC, FLOAT_VAL, -1, line);
            }else if(isDouble==1){
                createNewNode(word, CONSTANT_DESC, DOUBEL_VAL, -1, line);
            }else if(isFloat!=-1 && isDouble!=-1){
                createNewNode(word, CONSTANT_DESC, INT_VAL, -1, line);
            }
            fseek(fp,-1L,SEEK_CUR);//向后回退一位
        }
        
        //处理换行
        else if(ch == ' ' || ch == '\t' || ch == '\r' || ch =='\n' ){
            if(ch == '\n'){
                line++;
            }
        }
        
        //处理头文件和宏常量(预处理)
        else if(ch == '#'){
            
        }
    
        else if(ch == '*'){
            createNewNode("*", OPERATOR_DESC, MUL, -1, line);
        }
        
        
        
        else if(ch == ';'){
            createNewNode(";", BOUNTWROD_DESC, SEM, -1, line);
        }
        
        else if(ch == ','){
            createNewNode(",", BOUNTWROD_DESC, COM, -1, line);
        }
        
        else if(ch == '"'){
            createNewNode("\"", BOUNTWROD_DESC, DOUBLE_QUO, -1, line);
        }
        
        else if(ch == ':'){
            createNewNode(":", BOUNTWROD_DESC, COL, -1, line);
        }
        
        else if(ch == '('){
            createNewNode("(", BOUNTWROD_DESC, LEFT_PAR, -1, line);
        }
        
        else if(ch == ')'){
            createNewNode(")", BOUNTWROD_DESC, RIGHT_PAR, -1, line);
        }
        

        //{"=",";",",","'",":","(",")","."};
        
        
        if (ch != ' '&& ch != '\n') {   //去掉空格和换行符
            charSET[count] = ch;
            count++;
        }
    }
    fclose(fp);
    
    displaynormalNode();
    
}