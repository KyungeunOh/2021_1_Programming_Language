//
//  main.c
//  pl_recursive
//
//  Created by Kyungeun on 2021/03/19.
//

#include <stdio.h>
#include <stdlib.h>

void get_next_token(void);
void expr(void);
void term(void);
void factor(void);
void error(void);

enum {NN,PLUS,STAR,NUMBER,LP,RP,END} token;

char expr_arr[100];
int i=0;



void get_next_token(){
    char s = expr_arr[i++];
    switch(s){
        case '+': token=PLUS; break;
        case '*': token=STAR; break;
        case '(': token=LP; break;
        case ')': token=RP; break;
        case '\0': token=END; break;
        case ' ': token=NN; get_next_token(); break;
        default:
            for(;expr_arr[i] != '\0' && '0'<=expr_arr[i] && expr_arr[i] <= '9';i++);
            token=NUMBER; break;
    }
}

void expr(){
    term();
    while (token==PLUS) {
        get_next_token();
        term();}
}

void term(){
    factor();
    while (token==STAR) {
        get_next_token();
        factor();}
}

void factor(){
    if (token==NUMBER)
        get_next_token();
    else if (token==LP) {
        get_next_token();
        expr();
        if(token==RP)
            get_next_token();
        else
            error();}
    else error();
}

void error(){
    printf("Error occured.\n");
    exit(0);
}

int main() {
    scanf("%[^\n]s",expr_arr);
    get_next_token();
    expr();
    if (token==END) printf("Correct.\n");
    else error();
}
