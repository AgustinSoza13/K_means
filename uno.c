#include<stdio.h>
#include<stdlib.h>
#include <time.h> /* Nueva librería necesaria para la función srand */

#define K 3

int **crear_arreglo(){
    int **matriz;
    time_t t;
    int N=2;
    int a,b;
    int **aleatorio;
    aleatorio = (int **)malloc(sizeof(int *)*K);
	for (int i=0; i < K; i++){
        aleatorio[i] = (int *)malloc(sizeof(int)*N);
        
    }
    srand((unsigned) time(&t));
    for( int i = 0 ; i < K ; i++ ) {
        aleatorio[i][0]=rand() % 100;
        aleatorio[i][1]=rand() % 20; 
    }
		
    
    /*matriz = (int **) malloc(2 * sizeof(int *));
    for(int i = 0; i < 2; i++){
        matriz[i] = (int *) malloc(2 * sizeof(int));
        for(int j = 0; j < 2; j++){
            matriz[i][j] = i + j;
        }
    }*/
    
    printf("%i",aleatorio[0][0]);
    return aleatorio;
}
int main(){
    int **matriz = crear_arreglo();
    
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
        
}

