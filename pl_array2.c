#include <stdio.h>
#include <time.h>
#define MAX 110000 // 10001번째 소수 104743
int main(){
    _Bool check[MAX] = {0, }; // 0이 소수, 1이 소수가 아닌 수
    int n, i, j, k;
    scanf("%d",&n);
    check[0] = check[1] = 1;

    clock_t start, end;
    double diff;

    start = clock();
    // 소수 판별 + 출력
    for(i = 2, k = 0; k < n && i < MAX; i++){
        if(check[i]) continue;
        else{
            for(j = 2; i * j < MAX; j++){
                check[i * j] = 1;
            }
            printf("%6d ",i);
            k++;
            if(k % 10 == 0) printf("\n");
        }
    }
    end = clock();
    diff = (double)(end - start)/CLOCKS_PER_SEC;
    printf("소요 시간 : %lf\n", diff);
}