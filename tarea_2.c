#include<stdio.h>
#include<stdlib.h>
#include <omp.h>
#include <time.h> /* Nueva librería necesaria para la función srand */
#include<math.h>
#include <string.h>
#include <unistd.h>
#define pass (void)0
#define DIM 20
#define T 8
#define K 3
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
            if(aux==0){
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
    float **promedios;
    promedios = (float **)malloc(sizeof(float *) * K);
    for (i = 0; i < K; i++){
        promedios[i] = (float *)malloc(sizeof(float) * DIM);
    }
    for (i = 0; i < K; i++) {
        for (j = 0; j < DIM; j++)
            promedios[i][j] = 0;
    }


    for(i=0;i<K;i++){
        int y=0;
        int iteracion=0;
        for(j=0;j<N_DB;j++){    //base de datos
            if(Cluster[j]==i){
                for(x=0;x<DIM;x++){
                        //centroides[i][x]=((centroides[i][x]+ELEMS[j][x]));//suma con centroide
                    promedios[i][x]+=ELEMS[j][x];
                }
                y++;                           
            } 
            iteracion++;   
        }
       //printf("\n%i\n",y);
        if (y==0){
            printf("aqui estoy bombon");
        }
        if(y==1){
            for(j=0;j<DIM;j++){
                centroides[i][j]=(promedios[i][j])/1;
            } 
        }
        else{
            for(j=0;j<DIM;j++){
                centroides[i][j]=(promedios[i][j])/y;
            }   
        }

        /*printf("\n%i",y);
        printf("\nel promedio es:");
        for(j=0;j<DIM;j++){
            printf("++%f++",centroides[i][j]);
        }*/
    }
    free(promedios);
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
                aux=(pow(centroides[j][x]-ELEMS[i][x],2))+aux;
            }
            aux=sqrt(aux);
            //printf("\n");
            //("%f",aux);
            if(aux==0){
                resultado=aux;
                cluster=j;
                break;
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
       // printf("\n--------------------------%i",cluster);
        Cluster[i]=cluster;        
    }
    return Cluster;
}

void EscribirTxt(int *Cluster,int N_DB, long num_cores, long num_threads, float cpu_time_used){
    FILE *archivo;
    archivo = fopen("resultados.txt", "w");

    if (archivo == NULL)
    {
        printf("Error al abrir el archivo.\n");
    }
    for (int i = 0; i < N_DB; i++)
    {
        fprintf(archivo, "%d\n", Cluster[i]);
    }
    fprintf(archivo, "\n---- Datos generales ----\n");
    fprintf(archivo, "Tiempo de ejecución paralelo: X\n");
    fprintf(archivo, "Tiempo de ejecución secuencial: %f segundos\n", cpu_time_used);
    fprintf(archivo, "Cantidad de vectores: %d\n", N_DB);
    fprintf(archivo, "Cantidad de núcleos del sistema: %ld\n", num_cores);
    fprintf(archivo, "Cantidad de hilos del sistema: %ld\n", num_threads);
    fprintf(archivo, "Speed-Up (Tiempo secuencial / Tiempo paralelo): X\n");
    fclose(archivo);
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
    int *kmeans;
    clock_t start, end;   // para medir el tiempo de ejecución
    double cpu_time_used; // para medir el tiempo de ejecución
    long num_cores = sysconf(_SC_NPROCESSORS_ONLN); // Número de cores
    long num_threads = sysconf(_SC_NPROCESSORS_CONF);   // Número de threads
    start = clock(); // Medir el tiempo de ejecución
    centroides = (float **)malloc(sizeof(float *) * K);
    for (i = 0; i < K; i++)
        centroides[i] = (float *)malloc(sizeof(float) * DIM);
    for (i = 0; i < K; i++) {
        for (j = 0; j < DIM; j++)
            centroides[i][j] = ELEMS[i][j];
    } 
    
    kmeans=Kmeans(centroides,ELEMS,N_DB);
  
    centroides=promedio(kmeans,centroides,ELEMS,N_DB);
    int *resultado = (int *)malloc(sizeof(int) * N_DB);
    int iterador=1;
    while(1){
        int contador=0;
        iterador++;
        kmeans_1=Kmeanuno(kmeans,centroides,ELEMS,N_DB);
        centroides=promedio(kmeans_1,centroides,ELEMS,N_DB);
        for(i=0;i<N_DB;i++){
            if(kmeans_1[i]==kmeans[i]){
                contador++;
            }  
        }
        printf("\n");
        if(contador==N_DB){
            
            for(i=0;i<N_DB;i++){
                resultado[i]=kmeans_1[i];
            }
           printf("iterados: %i\n",iterador);
           break;
        }
        else{
            kmeans=Kmeanuno(kmeans_1,centroides,ELEMS,N_DB);
            centroides=promedio(kmeans,centroides,ELEMS,N_DB);
        }
        printf("%i iteracion:",iterador);
    }
    for(i=0;i<N_DB;i++){
        printf("%i",resultado[i]);
    }
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    EscribirTxt(resultado,N_DB,num_cores/2, num_threads, cpu_time_used);
    free(resultado);
    free(ELEMS);
    free(centroides_1);
    free(centroides);
    free(kmeans_1);
    free(kmeans);
    return 0;
}