//Italo__Pereda-Cristobal_rodenas

#include<stdio.h>
#include<stdlib.h>
#include <omp.h>
#include <time.h> /* Nueva librería necesaria para la función srand */
#include<math.h>
#include <string.h>
#include <unistd.h>
#define pass (void)0
#define DIM 20
#define T 24
#define K 3
//secuencial

int *KmeansSecuencial(float **centroides,float **ELEMS,int N_DB){
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
float **promedioSecuencial(int *Cluster,float **centroides,float **ELEMS,int N_DB){
    int i,j,x;
    for(i=0;i<K;i++){
        int y=0;
        int iteracion=0;
        for(j=0;j<N_DB;j++){    //base de datos
            if(Cluster[j]==i){
                for(x=0;x<DIM;x++){
                    //centroides[i][x]=((centroides[i][x]+ELEMS[j][x]));//suma con centroide
                    centroides[i][x]+=ELEMS[j][x];

                }
                
                
                y++;                           
            } 
            iteracion++;   
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

int *KmeanunoSecuencial(int *kmeans,float **centroides,float **ELEMS,int N_DB){ 
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

        Cluster[i]=cluster;        
    }
    return Cluster;
}




//crear una funcion que devuelva el puntero del arreglo con los centroides
//generamos numeros aleatorios de 0 a n_db(cantidad de filas del archivo txt), luego retornamos en un arreglo los valores//bueno
//paralelo
int *Kmeans(float **centroides,float **ELEMS,int N_DB){
    int i,j,x;
    int *Cluster;
    Cluster=(int *)malloc(sizeof(int)*N_DB);
    #pragma omp parallel for private(i, j, x) shared(centroides,ELEMS,N_DB) num_threads(T)//shared todos los hilos tienen acceso a ella
    //private esatblece la varible como privada por lo tanto es una variable por cada hilo, y cada una tiene acceso a la variable local
    
    
    
    for(i=0;i<N_DB;i++){//base de datos 10
        float resultado=0;
        int cluster=0;
        for(j=0;j<K;j++){//cluster
            float aux=0;
            #pragma parallel barrier
            for(x=0;x<DIM;x++){//barrier
                //#pragma
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

    #pragma omp parallel for private(i, j, x) shared(Cluster,centroides,ELEMS,N_DB) num_threads(T)
    for(i=0;i<K;i++){
        int y=0;
        int iteracion=0;
        for(j=0;j<N_DB;j++){    //base de datos
            if(Cluster[j]==i){
                #pragma parallel barrier
                for(x=0;x<DIM;x++){
                    //centroides[i][x]=((centroides[i][x]+ELEMS[j][x]));//suma con centroide
                    centroides[i][x]+=ELEMS[j][x];
                }
                  
                y++;                           
            } 
            iteracion++;   
        }
       //printf("\n%i\n",y);
        if(y==0){
            #pragma parallel barrier
            for(j=0;j<DIM;j++){
                centroides[i][j]=(centroides[i][j])/1;
            } 
        }
        else{
            #pragma parallel barrier
            for(j=0;j<DIM;j++){
                centroides[i][j]=(centroides[i][j])/y;
            }   
        }
    }
    return centroides;
}
//implementacion de k_means //bueno

int *Kmeanuno(int *kmeans,float **centroides,float **ELEMS,int N_DB){ 
    int i,j,x; 
    int *Cluster;
    Cluster=(int *)malloc(sizeof(int)*N_DB);
    #pragma omp parallel for private(i, j, x) shared(kmeans,centroides,ELEMS,N_DB) num_threads(T)

    
    for(i=0;i<N_DB;i++){//base de datos
        float resultado=0;
        int cluster=0;
        for(j=0;j<K;j++){//cluster
            float aux=0;
            #pragma parallel barrier
            for(x=0;x<DIM;x++){ //barrier si o si
                aux=(pow(centroides[j][x]-ELEMS[i][x],2))+aux;
            }
            aux=sqrt(aux);
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

        Cluster[i]=cluster;        
    }
    return Cluster;
    
}

void EscribirTxt(int *Cluster,int N_DB, int num_cores, int num_threads, float paralelo,float cpu_time_used){
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
    fprintf(archivo, "Tiempo de ejecución paralelo: %f\n",paralelo);
    fprintf(archivo, "Tiempo de ejecución secuencial: %f segundos\n", cpu_time_used);
    fprintf(archivo, "Cantidad de vectores: %d\n", N_DB);
    fprintf(archivo, "Cantidad de núcleos del sistema: %ld\n", num_cores);
    fprintf(archivo, "Cantidad de hilos del sistema: %ld\n", num_threads);
    fprintf(archivo, "Speed-Up (Tiempo secuencial / Tiempo paralelo): %f\n",(cpu_time_used/paralelo));
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
    double start_time = omp_get_wtime();//abajo
    long num_cores = sysconf(_SC_NPROCESSORS_ONLN); // Número de cores
    long num_threads = sysconf(_SC_NPROCESSORS_CONF);   // Número de threads

 
    //omp_set_num_threads(T);//nuemero de hilos de la region paralela
    centroides = (float **)malloc(sizeof(float *) * K);
    for (i = 0; i < K; i++)
        centroides[i] = (float *)malloc(sizeof(float) * DIM);
    for (i = 0; i < K; i++) {
        for (j = 0; j < DIM; j++)
            centroides[i][j] = ELEMS[i][j];
    } 

    //problema de carrera estan usando la misma variable solucion cerrojo 

    //paralelo
    
    //-----------------
    kmeans=Kmeans(centroides,ELEMS,N_DB);
    centroides=promedio(kmeans,centroides,ELEMS,N_DB);
    for(i=0;i<N_DB;i++){
        printf("%i",kmeans[i]);
    }
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
            printf("iterados: %i\n",iterador);
        }
    }
    /*for(i=0;i<N_DB;i++){
        printf("%i",resultado[i]);
    }*/ 
    double end_time = omp_get_wtime(); 
    double tiempo_paralelo = end_time - start_time;

    //secuencial
    float **centroides2,**centroides1;
    int *kmeans2;
    int *kmeans1;
    centroides1 = (float **)malloc(sizeof(float *) * K);
    for (i = 0; i < K; i++)
        centroides1[i] = (float *)malloc(sizeof(float) * DIM);
    for (i = 0; i < K; i++) {
        for (j = 0; j < DIM; j++)
            centroides1[i][j] = ELEMS[i][j];
    }
    clock_t start, end;   // para medir el tiempo de ejecución
    
    start = clock(); // Medir el tiempo de ejecución
    kmeans1=KmeansSecuencial(centroides1,ELEMS,N_DB);
    centroides1=promedioSecuencial(kmeans1,centroides1,ELEMS,N_DB);

    /*for(i=0;i<N_DB;i++){
        printf("%i",kmeans[i]);
    }*/
    int *resultado1 = (int *)malloc(sizeof(int) * N_DB);
    int iterador1=1;
    while(1){
        int contador1=0;
        iterador1++;
        kmeans2=KmeanunoSecuencial(kmeans,centroides1,ELEMS,N_DB);
        centroides1=promedio(kmeans2,centroides1,ELEMS,N_DB);
        for(i=0;i<N_DB;i++){
            if(kmeans2[i]==kmeans1[i]){
                contador1++;
            }  
        }
        printf("\n");
        if(contador1==N_DB){  
            for(i=0;i<N_DB;i++){
                resultado[i]=kmeans2[i];
            }
           printf("iterados: %i\n",iterador1);
           break;
        }
        else{
            kmeans1=Kmeanuno(kmeans2,centroides1,ELEMS,N_DB);
            centroides1=promedio(kmeans1,centroides1,ELEMS,N_DB);
            printf("iterados: %i\n",iterador1);
        }
    }
    /*
    for(i=0;i<N_DB;i++){
        printf("%i",resultado1[i]);
    }*/
    end = clock();
    float cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    EscribirTxt(resultado,N_DB,omp_get_num_procs(), omp_get_max_threads(), tiempo_paralelo,cpu_time_used);
    //limpieza de memoria
    free(resultado);
    free(ELEMS);
    free(centroides_1);
    free(centroides);
    free(kmeans_1);
    free(kmeans);
    return 0;
}