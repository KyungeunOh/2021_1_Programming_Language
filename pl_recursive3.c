#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum e {ERROR,NUMBER,ID,PRINT,PLUS,STAR,LP,RP,RET,EQL,END} TOKEN;
TOKEN token;

int num; char ch = ' ';
int array[26];

void statement(void);
int expr(void);
int term(void);
int factor(void);
void error(void);
TOKEN get_token(void);

TOKEN get_token(){
    char string[32]; int i = 0;
    while((ch == ' ') || (ch == '\t')) ch = getchar(); // 토큰 앞의 빈칸을 무시
    if(ch == '+') { ch = getchar(); return(PLUS); }
    if(ch == '*') { ch = getchar(); return(STAR); }
    if(ch == '(') { ch = getchar(); return(LP); }
    if(ch == ')') { ch = getchar(); return(RP); }
    if(ch == '\n') { return(RET); }
    if(ch == '=') { ch = getchar(); return(EQL); }
    if(ch == EOF) { ch = getchar(); return(END); }
    if((ch >= '0') && (ch <= '9')){
        num = 0;
        do {
            num = num * 10 + ch - '0'; ch = getchar();
        } while((ch >= '0') && (ch <= '9'));
        return(NUMBER);
    }
    if((ch >= 'a') && (ch <= 'z')) { // 이름의 길이가 여러글자인 경우도 고려
        do {
            string[i++] = ch; ch = getchar(); //이름을 저장
        } while((ch >= 'a') && (ch <= 'z'));
        string[i]=0;
        if(strcmp(string,"print") == 0) return(PRINT); // 이름이 print 인지 검사
        if(strlen(string) == 1) { num = string[0] - 'a'; return(ID); }
    }
    return(ERROR);
}

void statement(){
    if(token == ID){
        token = get_token();
        if(token != EQL) error();
        else{
            int index = num; // array 저장 위치 받기
            token = get_token();
            array[index] = expr(); // 변수 저장
        }
    } else if(token == PRINT){
        token = get_token();
        printf("%d\n", expr());
    } else if(token == ERROR) error();
}

int expr(){
    int r;
    r = term();
    while(token==PLUS){
        token = get_token();
        r = r + term();
    }
    return (r);
}

int term(){
    int r;
    r = factor();
    while(token==STAR){
        token = get_token();
        r = r * factor();
    }
    return (r);
}

int factor(){
    int r;
    if(token==NUMBER){
        r = num;
        token = get_token();
    } else if(token==ID){
        r = array[num];
        token = get_token();
    } else if(token==LP){
        token = get_token();
        r = expr();
        if(token==RP)
            token = get_token();
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
        token = get_token();
        statement();
        ch = ' ';
    }
}

