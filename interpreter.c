//
//  main.c
//  pl_assign1_1
//
//  Created by Kyungeun on 2021/03/08.
//

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

char var[10]={}; // 변수 이름 배열
char *var_value[10]={}; // 변수 값 배열.

// ctrl_c 정상종료 구현

void ctrl_c(int sig){
    exit(0);
}

// 스택 부분 구현

char *stack[50]; // 50칸의 stack
int top = -1;

int isEmpty(){
    if(top<0) return 1;
    else return 0;
}
void push(char value[]){
    stack[++top] = (char*)malloc(sizeof(char) * (strlen(value)+1));
    strcpy(stack[top],value);
}
char* pop(){
    return stack[top--];
}
char* peek(){
    return stack[top];
}

// 연산 우선순위

int priority(char s[]){
    char ch = s[0];
    switch(ch) {
        case '(': case ')': return 0;
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        default: return 3; // 정수
    }
}

// 수식 계산 함수

int func(char arr[], int signal, int num){

    // 치환문
    if(signal){
        int i;
        for(i = 0 ; i < num ; i++){ // 이미 선언한 변수인지 확인
            if(strncmp(&var[i], arr, 1) == 0){
                var_value[i]=NULL;
                var_value[i] = (char*)malloc(sizeof(char) * 10);
                sprintf(var_value[i], "%d", func(&arr[2],0,0));
                return 0;
            }
        }
        if(i == num){ // 같은 변수 이름이 없다면
            var[num] = arr[0]; // 변수 이름
            var_value[num] = (char*)malloc(sizeof(char) * 10);
            sprintf(var_value[num], "%d", func(&arr[2],0,0)); // 변수이름과 =을 제외한 문자열
            return 0;
        }
    }
    
    // infix to postfix
    char poststr[100]={};
    int n1 = 0, n2 = 0; // 수식 오류 확인
    for(int i = 0; arr[i] != '\0'; i++){
        char s = arr[i];
        if(s == '('){
            push(&s);
            n1++;
        } else if(s == ')'){
            n2++;
            if(n1 != n2) {
                printf("Error\n");
                exit(0);
            }
            while(strncmp(peek(),"(",1) != 0){
                strcat(poststr,pop());
                strcat(poststr," ");
            }
            pop();
        } else if(s == '+' || s == '-' || s == '*' || s == '/'){
            while(!isEmpty() && priority(&s) <= priority(peek())){
                strcat(poststr,pop());
                strcat(poststr," ");
            }
            push(&s);
        } else if(s >= 'a' && s <= 'z'){ // 변수
            int var_check = 0;
            for(int i = 0; i < 10 ; i++){
                if(var[i] == s){
                    strcat(poststr,var_value[i]);
                    strcat(poststr," ");
                    var_check = 1;
                }
            }
            if(!var_check){
                printf("Error\n");
                exit(0);
            }
        } else { // 정수
            char num_c[5]={};
            for(int k=0; arr[i] != '\0' && '0' <= arr[i] && arr[i] <= '9'; i++,k++){
                num_c[k] = arr[i];
            }
            i--;
            strcat(poststr,num_c);
            strcat(poststr," ");
        }
    }
    while(!isEmpty()){
        strcat(poststr,pop());
        strcat(poststr," ");
    }

    // prove 단계
    char *ptr = strtok(poststr, " ");

    for(n1 = n2 = 0; ptr != NULL; ptr = strtok(NULL, " ") ){
        char s = ptr[0];
        char s1[10];
        if(s == '+' || s == '-' || s == '*' || s == '/'){
            n2 = atoi(pop());
            if(peek() == NULL) n1 = 0;
            else n1 = atoi(pop());
            switch(s){
                case '+': sprintf(s1, "%d", n1+n2); break;
                case '-': sprintf(s1, "%d", n1-n2); break;
                case '*': sprintf(s1, "%d", n1*n2); break;
                case '/': sprintf(s1, "%d", n1/n2); break; // 실수의 경우는 고려 X
            }
            push(s1);
        }
        else push(ptr);
    }

    return atoi(pop());
}

int main(){
    char arr[50]; // 명령문을 받을 배열
    int var_num = 0; // 변수 index

    signal(SIGINT, ctrl_c); // ctrl_c 누르면 정상종료

    while(1){
        scanf("%[^\n]s",arr);
        getchar();
        int check = strncmp("print",arr,5);
        if(!check){ // 프린트문
            printf("%d\n", func(&arr[6],0,0)); // print 예약어와 ' '를 제외한 문자열
        }
        else if(strncmp("=",&arr[1],1) == 0){ // 치환문
            func(arr,1,var_num);
            var_num++;
        }
        else { // 에러
            printf("Error\n");
            exit(0);
        }
    }
}

