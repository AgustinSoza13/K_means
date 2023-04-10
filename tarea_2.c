#include<stdio.h>
#include<stdlib.h>
#include <omp.h>
#include <time.h> /* Nueva librería necesaria para la función srand */
#define DIM 20
#define T 8
#define K 3
//crear una funcion que devuelva el puntero del arreglo con los centroides

int **NumneroAleatorios(int N_DB){
    time_t t;
    int N=2;
    int i, j,a,b;
    int **aleatorio;
    aleatorio = (int **)malloc(sizeof(int *)*K);
	for (int i=0; i < K; i++){
        aleatorio[i] = (int *)malloc(sizeof(int)*N);   
    }
    srand((unsigned) time(&t));
    for( i = 0 ; i < K ; i++ ) {
        aleatorio[i][0]=rand() % N_DB;
        aleatorio[i][1]=rand() % 20; 
    }
    return aleatorio;
}
void lecturaDeMatriz(int filas,int columnas, int **m){
    for(int i = 0; i < filas; i++){//fila
        for(int j = 0; j < columnas; j++){//columna
            printf("%i ", m[i][j]);
        }
        printf("\n");
    }
    free(m);//liberamos memoria dinamica
}
float *BusquedaCentroide(int **aleatorio,float **ELEMS){
    int N=2;
    int a,b,i,j;
    float *centroides;
    centroides=(float *) malloc(K*sizeof(float));
    for (i=0; i < K; i++)
	{
		for (j=0; j < N; j++)
			if (j == 0)
                a=aleatorio[i][j];
			else
                b=aleatorio[i][j];
            centroides[i]=ELEMS[a][b];
	}
    return centroides;
}
int main()
{
	// Ejecutar como: ./a.out < test.txt
	int N_DB, i, j;
	float **ELEMS;
	scanf("%d", &N_DB);
	ELEMS = (float **)malloc(sizeof(float *)*N_DB);
	for (i=0; i < N_DB; i++)
		ELEMS[i] = (float *)malloc(sizeof(float)*DIM);
	//En este punto ELEMS es una matriz de tamaño [N_DB][DIM]
	for (i=0; i < N_DB; i++)
		for (j=0; j < DIM; j++)
			scanf("%f", &(ELEMS[i][j]));

	printf("%d\n", N_DB);//tamaño de base de datos
    int **matriz_aleatoria=NumneroAleatorios(N_DB);
    //lecturaDeMatriz(3,2,matriz_aleatoria);
    float *centroides=BusquedaCentroide(matriz_aleatoria,ELEMS);
    /*for ( i = 0; i < K; i++)
    {
        printf("%f\n",centroides[i]);
    }*/
    for (i=0; i < N_DB; i++)

	{
        float x,y,resultado;
		for (j=0; j < DIM; j++)
        {
			y=ELEMS[i][j];
            printf("%f\n",y);
        }
        printf("---------");//calclar distancia, y son los elemntos y x van a ser los 3 cluster creo que debe ir un if
	}
    //resultado 1 sqrt(y-x[0])^2 x cetroide
    //resultado 3 sqrt(y-x[2])^2
    //resultado 2 sqrt(y-x[1])^2

}
