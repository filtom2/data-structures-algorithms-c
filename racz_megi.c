#include <stdlib.h>
#include <stdio.h>


int Binar(int *prvaCast, int *druhaCast, int prvaCastHlad, int druhaCastHlad, int N){
    int right = N - 1;
    int left = 0;
    int stred;

    while(left <= right) {
        stred = left + (right - left) / 2;
        if( prvaCast[stred] == prvaCastHlad) {
            if(druhaCast[stred] == druhaCastHlad) {
                return stred + 1;
            }
            else {
                for(int i = left;i <right; i++) {
                    if(prvaCast[i] == prvaCastHlad){
                        if(druhaCast[i] == druhaCastHlad){
                            return i + 1;
                        }
                    }
                }
            }
        }
        if (prvaCast[stred] < prvaCastHlad){
            left = stred + 1;
        } else {
            right = stred - 1;
        }
    }
    return 0;
}



int main(){
    int N,M;
    scanf("%d", &N);
    if (N < 1 || N > 50000) {
        return 1;
    }

    int *prvaCAST = (int *)malloc(N * sizeof(int));
    int *druhaCAST = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N;i++) {
        scanf("%d", &prvaCAST[i]);
        druhaCAST[i] = 0;
        char peek = getchar();
        if (peek == ',') {
            scanf("%d", &druhaCAST[i]);
            while(druhaCAST[i] % 10 == 0 && druhaCAST[i] != 0) {
                druhaCAST[i] = druhaCAST[i] / 10;
            }
        }
    }

    scanf("%d", &M);
    if (M < 1 || M > 100000) {
        return 1;
    }

    int prvaCASTHlad;
    int druhaCASTHlad;
    for (int j = 0;j < M; j++){
        scanf("%d", &prvaCASTHlad);
        druhaCASTHlad = 0;
        char peek = getchar();
        if (peek == ',') {
            scanf("%d", &druhaCASTHlad);
            while(druhaCASTHlad % 10 == 0 && druhaCASTHlad != 0) {
                druhaCASTHlad = druhaCASTHlad / 10;
            }
        }
        int vysledok = Binar(prvaCAST, druhaCAST, prvaCASTHlad, druhaCASTHlad, N);
        printf("%d", vysledok);
        if(j < M-1) {
            printf("\n");
        }
    }

    free(prvaCAST);
    free(druhaCAST);
    return 0;
}