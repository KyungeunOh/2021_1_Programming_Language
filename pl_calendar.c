#include <stdio.h>
int main(){
    int year, x, i;
    int array[42], *p;
    
    printf("출력하고 싶은 연도를 입력하시오 : ");
    scanf("%d", &year);
    year--;
    
    x = (year * 365 + year / 4 - year / 100 + year / 400 ) % 7;

    p = array;
    for(i = 0; i < 42; i++, p++){
        if((i < x) || (i - x + 1 > 31)) *p = 0;
        else *p = i - x + 1;
    }
    p = array;

    printf("\n <%d년 1월>\n Sun Mon Tue Wed Thu Fri Sat\n", year);
    for(i = 0; i < 42; i++, p++){
        if(*p == 0) printf("    ");
        else printf("%4d",*p);
        if((i!=0) && (i % 7 == 6)) printf("\n");
    }
}
