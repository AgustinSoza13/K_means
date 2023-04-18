#include<stdio.h>
#include<stdlib.h>
#include <omp.h>
#include <time.h> /* Nueva librería necesaria para la función srand */
#include<math.h>
#include <string.h>
#define pass (void)0
#define DIM 20
#define T 8
#define K 5

//crear una funcion que devuelva el puntero del arreglo con los centroides
//generamos numeros aleatorios de 0 a n_db(cantidad de filas del archivo txt), luego retornamos en un arreglo los valores//bueno


int *Kmeans(float **centroides,float **ELEMS,int N_DB){
    int i,j,x;
    int *Cluster;
    Cluster=(int *)malloc(sizeof(int)*N_DB);
    for(i=0;i<N_DB;i++){//base de datos 10
        float resultado=0;
        int cluster=0;
        for(j=0;j<K;j++){//cluster
            float aux=0;
            for(x=0;x<DIM;x++){
                aux=(pow(centroides[j][x]-ELEMS[i][x],2))+aux;
            }
            aux=sqrt(aux);
            //printf("\n");
            //printf("%f",aux);
            if(i==j){
                resultado=aux;
                cluster=j;
                break;
            }
            if(resultado==0){
                resultado=aux;
                cluster=j;
                }
            else
                if(resultado>aux){
                    resultado=aux;    
                    cluster=j;   
                }
                    else{
                        continue;
                    }                     
        }
        //printf("\n--------------------------%i",cluster);
        Cluster[i]=cluster;   
    }
    return Cluster;
}

//bueno
float **promedio(int *Cluster,float **centroides,float **ELEMS,int N_DB){
    int i,j,x;
    /*float **pro;
    pro = (float **)malloc(sizeof(float *)*K);
	for (i=0; i < K; i++)
		pro[i] = (float *)malloc(sizeof(float)*DIM);*/
    for(i=0;i<K;i++){
        int y=0;
        for(j=0;j<N_DB;j++){    
            if(Cluster[j]==i){
                if(i==j){
                    centroides[i][x]=(centroides[i][x]);
                }
                else{
                    for(x=0;x<DIM;x++){
                        centroides[i][x]=((centroides[i][x]+ELEMS[j][x]));
                    }
                }
                y++;                           
            }      
        }
       //printf("\n%i\n",y);
        if(y==0){
            for(j=0;j<DIM;j++){
                centroides[i][j]=(centroides[i][j])/1;
            } 
        }
        else{
            for(j=0;j<DIM;j++){
                centroides[i][j]=(centroides[i][j])/y;
            }   
        }

        /*printf("\n%i",y);
        printf("\nel promedio es:");
        for(j=0;j<DIM;j++){
            printf("++%f++",centroides[i][j]);
        }*/
    }
    return centroides;
}
//implementacion de k_means //bueno

int *Kmeanuno(int *kmeans,float **centroides,float **ELEMS,int N_DB){ 
    int x,j,i; 
    int *Cluster;
    Cluster=(int *)malloc(sizeof(int)*N_DB);
    for(i=0;i<N_DB;i++){//base de datos
        float resultado=0;
        int cluster=0;
        for(j=0;j<K;j++){//cluster
            float aux=0;
            for(x=0;x<DIM;x++){ 
                //printf("\n%f++%f\n",centroides[j][x],ELEMS[i][x]);
                aux=(pow(centroides[j][x]-ELEMS[i][x],2))+aux;
            }
            aux=sqrt(aux);
            //printf("\n");
            //printf("%f",aux);
            if(i<K){
                if(aux==0){
                   resultado=aux;
                    cluster=j;
                    //printf("%f",aux);
                    break; 
                }
                else
                    pass;

            }
            
            if(resultado==0){
                resultado=aux;
                cluster=j;
            }else
                if(resultado>aux){
                    resultado=aux;    
                    cluster=j;   
                }
                else
                    pass;    
        }
        //printf("\n--------------------------%i",cluster);

        Cluster[i]=cluster;        
    }
    return Cluster;
}
int main()
{
	// Creamos los valores y punteros que contendran la base de datos
	int N_DB, i, j,a;
	float **ELEMS;//doble puntero para almacenar los datos datos en arregos anidados
	scanf("%d", &N_DB);
	ELEMS = (float **)malloc(sizeof(float *)*N_DB);
	for (i=0; i < N_DB; i++)
		ELEMS[i] = (float *)malloc(sizeof(float)*DIM);
	//En este punto ELEMS es una matriz de tamaño [N_DB][DIM]
	for (i=0; i < N_DB; i++)
		for (j=0; j < DIM; j++)
			scanf("%f", &(ELEMS[i][j]));
	printf("%d\n", N_DB);//tamaño de base de datos
    //se llama la funcion NumneroAleatorios que retorna un puntero con valores alatorios
    
    float **centroides_1,**centroides;
    int *kmeans_1;
    
    centroides = (float **)malloc(sizeof(float *) * K);
    for (i = 0; i < K; i++)
        centroides[i] = (float *)malloc(sizeof(float) * DIM);
    for (i = 0; i < K; i++) {
        for (j = 0; j < DIM; j++)
            centroides[i][j] = ELEMS[i][j];
    }
    /*centroides = (float **)malloc(sizeof(float *) * K);
    for (i = 0; i < K; i++)
        centroides[i] = (float *)malloc(sizeof(float) * DIM);
    // Inicializar los centroides con elementos aleatorios del conjunto de datos
    srand(time(0));
    for (i = 0; i < K; i++) {
        int indice_aleatorio = rand() % N_DB;
        for (j = 0; j < DIM; j++)
            centroides[i][j] = ELEMS[indice_aleatorio][j];
    }*/
    int *kmeans;
    kmeans=Kmeans(centroides,ELEMS,N_DB);
    centroides=promedio(kmeans,centroides,ELEMS,N_DB);
    //printf("original\n");
    for(i=0;i<N_DB;i++){
        //printf("%i",kmeans[i]);
    }
    //printf("\n");
    int *resultado = (int *)malloc(sizeof(int) * N_DB);
    int iterador=0;
    while(1){
        int contador=0;
        kmeans_1=Kmeanuno(kmeans,centroides,ELEMS,N_DB);
        centroides=promedio(kmeans_1,centroides,ELEMS,N_DB);
        //printf("\nen el iterado: %i\n",iterador) ;
        for(i=0;i<N_DB;i++){
            //printf("%i",kmeans_1[i]);
            if(kmeans_1[i]==kmeans[i]){
                contador++;
            }
            
        }
        printf("\n");
        if(contador==N_DB){
            for(i=0;i<N_DB;i++){
                resultado[i]=kmeans_1[i]; 
            }
            //printf("el arreglo es:\n");
           //for(i=0;i<N_DB;i++){
            //printf("%i",kmeans_1[i]);
           //}
           //printf("\nen el iterado: %i\n",iterador) ;
           //printf("\nel contador fue: %i\n",contador) ;
           printf("iterados: %i\n",iterador);
           break;
        }
        else{
            kmeans=Kmeanuno(kmeans_1,centroides,ELEMS,N_DB);
            centroides=promedio(kmeans,centroides,ELEMS,N_DB);

        }
        iterador++;
    }

    for(i=0;i<N_DB;i++){
        printf("%i",resultado[i]);
    }    
    return 0;
}
