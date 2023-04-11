#include<stdio.h>
#include<stdlib.h>
#include <omp.h>
#include <time.h> /* Nueva librería necesaria para la función srand */
#define pass (void)0
#define DIM 20
#define T 8
#define K 3
//crear una funcion que devuelva el puntero del arreglo con los centroides
//generamos numeros aleatorios de 0 a n_db(cantidad de filas del archivo txt), luego retornamos en un arreglo los valores
int *NumneroAleatorios(int N_DB){
    time_t t;
    int i, j;
    int *aleatorio;
    aleatorio = (int*)malloc(K*sizeof(int));
    srand((unsigned) time(&t));
    for( i = 0 ; i < K ; i++ ) {
        aleatorio[i]=rand() % N_DB;
    }
    return aleatorio;
}
//mostramos los valores de la matriz anidada
void lecturaDeMatrizAnidada(int filas,int columnas, int **m){
    for(int i = 0; i < filas; i++){//fila
        for(int j = 0; j < columnas; j++){//columna
            printf("%i ", m[i][j]);
        }
        printf("\n");
    }
    free(m);//liberamos memoria dinamica
}
//mostramos los valores de la matriz
void lecturaDeMatriz(int *m){
    int i;
    for (i=0;i<K;i++){
        printf("%i\n",m[i]);
    }
}
//buscamos los centroides dentro de la base de datos
float **BusquedaCentroide(int *aleatorio,float **ELEMS){
    int a,i;
    float **centroides;
    centroides=(float **)malloc(sizeof(float *)*K);
    for (i=0; i < K; i++)
	{
        a=aleatorio[i];
        centroides[i]=ELEMS[a];
	}
    return centroides;
}
int *Euclidiana(int *aleatorio,float **ELEMS,int N_DB){
    int a,i,j,k;
    float  *memoria[K];
    for (i=0; i < K; i++)
	{
        a=aleatorio[i];
        memoria[i]= (float*)&ELEMS[a];//copiamos la direccion de memoria
	}
    memoria;
    int resultado;
    for(i=0;i<N_DB;i++){
        for(j=0;j<K;j++){
            if(memoria[j]==(float*)&ELEMS[i]){
                pass;
            }
            else
              
        }
    }
    return 0;
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
    int *matriz_aleatoria=NumneroAleatorios(N_DB);
    float **centroides;
    int *euclidiana;
    centroides=BusquedaCentroide(matriz_aleatoria,ELEMS);
    euclidiana=Euclidiana(matriz_aleatoria,ELEMS,N_DB);
    //calclar distancia, y son los elemntos y x van a ser los 3 cluster creo que debe ir un if
	
    //resultado 1 sqrt(y-x[0])^2 x cetroide
    //resultado 3 sqrt(y-x[2])^2
    //resultado 2 sqrt(y-x[1])^2

}
