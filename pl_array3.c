#include <stdio.h>
/* 이차원 배열을 출력하는 코드 */
void print(int n, float arr[][n+1]){
    printf("-------------------\n");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n + 1; j++){
            printf("%.2f ",arr[i][j]);
        } printf("\n");
    }
    printf("-------------------\n");
}

int main(){
    int n, i, j, k, l;

    /* 배열을 입력받는 곳 */
    printf("n차 방정식. n은 ? ");
    scanf("%d",&n);
    
    float array[n][n+1];

    printf("방정식을 입력하시오.(숫자만)\n");
    for(i = 0; i < n; i++){
        for(j = 0; j < n+1; j++){
            scanf("%f",&array[i][j]);
        }
    }
    print(n, array);

    /* 대각 행렬에 0이 들어있을 경우 */
    for(i = 0; i < n; i++){
        if(array[i][i] == 0){
            for(j = 0; j < n + 1; j++){
                if(i == n - 1){ // 마지막 행일 때는 전 행과 swap
                    float tmp = array[i][j];
                    array[i][j] = array[i-1][j];
                    array[i-1][j] = tmp;
                }else{ // swap
                    float tmp = array[i][j];
                    array[i][j] = array[i+1][j];
                    array[i+1][j] = tmp;
                }
            }
            i = -1; // 재검사
        }
    }

    print(n, array);


    for(i = 0; i < n; i++){
        if(i >= 1){
            /* 0으로 만드는 곳 */
            for(j = 0; j < i; j++){
                if(array[i][j] == 0) continue;
                else{
                    for(k = 1; k <= i; k++){
                        if(array[i-k][j] == 0) continue;
                        else break;
                    }
                    float x = (-1 * array[i][j]) / array[i-k][j];
                    for(l = 0; l < n + 1; l++){
                        array[i][l] += x * array[i-k][l];
                    }
                }
            }
        }
        /* 대각 행렬을 1로 바꾸는 곳 */
        if(array[i][i] != 1){
            float x = 1 / array[i][i];
            for(k = 0; k < n + 1; k++){
                array[i][k] *= x;
            }
        }
    }
    print(n, array);

    for(i = n - 2; i >= 0; i--){
        for(j = n - 1; j > i; j--){
            if(array[i][j] == 0) continue;
            else{
                /* 0으로 만드는 곳 */
                for(k = 1; k < n; k++){
                    if(array[i+k][j] == 0) continue;
                    else break;
                }
                float x = (-1 * array[i][j]) / array[i+k][j];
                for(l = 0; l < n + 1; l++){
                    array[i][l] += x * array[i+k][l];
                }
            }
        }
    }

    print(n, array);


    for(i = 0; i < n; i++){
        printf("%.2f ",array[i][n]);
    } printf("\n");
}