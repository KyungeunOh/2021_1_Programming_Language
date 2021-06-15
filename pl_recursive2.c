//
//  pl_recursive2
//
//  Created by Kyungeun on 2021/03/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {ERR,PLUS,STAR,NUMBER,LP,RP,ID,PRINT,EQL,RET,eof} token;

int num;
int array[26];

int i=0; // token index
char arr[100]; // interpret할 문자열 저장

void get_token(void);
void statement(void);
int expr(void);
int term(void);
int factor(void);
void error(void);


void get_token(){
    char s = arr[i++];
    switch(s){
        case '+': token=PLUS; break;
        case '*': token=STAR; break;
        case '(': token=LP; break;
        case ')': token=RP; break;
        case '\0': token=eof; break;
        case '\n': token=RET; break;
        case '=': token=EQL; break;
        case ' ': get_token(); break;
        default:
            if('0'<=s && s <= '9'){ // 정수
                token=NUMBER;
                char num_c[5]={};
                num_c[0]=s;
                for(int k=1; arr[i] != '\0' && '0' <= arr[i] && arr[i] <= '9'; i++,k++){ // 두 자리 수 이상의 정수
                    num_c[k] = arr[i];
                }
                num=atoi(num_c); // num에 저장
            } else if('a'<=s && s <= 'z'){
                if(strncmp("print",&arr[i-1],5) == 0){
                    token=PRINT;
                    i+=4;
                } else{
                    token=ID;
                    num=s-65;
                }
            }
            else{
                token=ERR; error();
            }
    }
}

void statement(){
    if(token==ID){
        get_token();
        if(token!=EQL) error();
        else{
            int index = num; // array 저장 위치 받기
            get_token();
            array[index] = expr(); // 변수 저장
        }
    } else if(token==PRINT){
        get_token();
        printf("%d\n", expr());
    } else{
        error();
    }
}

int expr(){
    int r;
    r = term();
    while(token==PLUS){
        get_token();
        r = r + term();
    }
    return (r);
}

int term(){
    int r;
    r = factor();
    while(token==STAR){
        get_token();
        r = r * factor();
    }
    return (r);
}

int factor(){
    int r;
    if(token==NUMBER){
        r = num;
        get_token();
    } else if(token==ID){
        r = array[num];
        get_token();
    } else if(token==LP){
        get_token();
        r = expr();
        if(token==RP)
            get_token();
        else
            error();
    } else
        error();
    return (r);
}

void error(){
    printf("Error occured.\n");
    exit(0);
}

int main(void){
    while(1){
        i=0;
        scanf("%[^\n]s",arr);
        getchar();
        get_token();
        statement();
    }
}

