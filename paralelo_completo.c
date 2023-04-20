//Italo_Pereda_Soza-Cristobal_Rodenas_Rodenas

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
//Código secuencial

int *KmeansSecuencial(float **centroides,float **ELEMS,int N_DB){
    int i,j,x;//declaramos variables
    int *Cluster;
    Cluster=(int *)malloc(sizeof(int)*N_DB);
    for(i=0;i<N_DB;i++){//base de datos 
        float resultado=0;
        int cluster=0;
        for(j=0;j<K;j++){//cluster
            float aux=0;//variable para la sumatoria
            for(x=0;x<DIM;x++){//dimenciones 
                aux=(pow(centroides[j][x]-ELEMS[i][x],2))+aux;//calculo de distancia
            }
            aux=sqrt(aux);//obtenemos la raiz de la dictacia
            //aqui seleccionaremos cual  las distancias euclidianas es menor, de los k centroides
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
        Cluster[i]=cluster;   //almacenamos a que cluster pertenece ese vector
    }
    return Cluster;
}

float **promedioSecuencial(int *Cluster,float **centroides,float **ELEMS,int N_DB){
    int i,j,x;//definimos variables
    float **promedios;
    //con promedios buscamos sumar todos los vectores asignados a cada cluster correspondiente 
    promedios = (float **)malloc(sizeof(float *) * K);
    for (i = 0; i < K; i++){
        promedios[i] = (float *)malloc(sizeof(float) * DIM);
    }
    for (i = 0; i < K; i++) {
        for (j = 0; j < DIM; j++)
            promedios[i][j] = 0;//iniciamos con todas las varibles de promedio,como 0
    }
    for(i=0;i<K;i++){//cantidad de cluster 
        int y=0;//sera para contar cuantas veces se cumple que k esta en el arreglo cluster
        int iteracion=0;
        for(j=0;j<N_DB;j++){ //base de datos
            if(Cluster[j]==i){//si en el arreglo Cluster esta el K(cluster) entramos al for sino continua iterando 
                for(x=0;x<DIM;x++){//dimenciones
                    promedios[i][x]+=ELEMS[j][x];//sumamos los vectores 
                }
                y++;                           
            } 
            iteracion++;   
        }
        if(y==1){//en caso de que solo se encuentre uno o no tenga ninguno conjunto asociado en la primera iteracion el cluster se divide por uno
            for(j=0;j<DIM;j++){
                centroides[i][j]=(promedios[i][j])/1;
            } 
        }
        else{
            for(j=0;j<DIM;j++){//el promedio lo dividimos por la cantidad de vectores que tenga asociado en este caso y
                centroides[i][j]=(promedios[i][j])/y;
            }   
        }

    }
    free(promedios);//liberamos memoria y retornamos
    return centroides;
}
//implementacion de k_means //bueno

int *KmeanunoSecuencial(int *kmeans,float **centroides,float **ELEMS,int N_DB){ 
    int x,j,i;//declaramos variables
    int *Cluster;
    Cluster=(int *)malloc(sizeof(int)*N_DB);
    for(i=0;i<N_DB;i++){//base de datos
        float resultado=0;
        int cluster=0;
        for(j=0;j<K;j++){//cluster
            float aux=0;//variable para la sumatoria
            for(x=0;x<DIM;x++){ //dimenciones
                aux=(pow(centroides[j][x]-ELEMS[i][x],2))+aux;//calculo de distacia
            }
            aux=sqrt(aux);//obtenemos la raiz de la distancia
            //aqui seleccionaremos cual  las distancias euclidianas es menor, de los k centroides
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

        Cluster[i]=cluster;//almacenamos a que cluster pertenece ese vector        
    }
    return Cluster;
}


//Código paralelo

int *Kmeans(float **centroides,float **ELEMS,int N_DB){
    int i,j,x;//declaramos variables
    int *Cluster;
    Cluster=(int *)malloc(sizeof(int)*N_DB);
    // pragma parallel for, se indica que puede ser ejecutado con varios hilos de forma paralela en el bucle for.
    //estamos colocando como privado i,j,x, estas se crean copias de cada una de estas, por cada hilo.
    //shared seran las variables que seran compartidas porlo que cada hilo tendra acceso a ella.
    omp_set_num_threads(T);
    #pragma omp parallel for private(i, j, x) shared(centroides,ELEMS,N_DB) 
    //shared todos los hilos tienen acceso a ella,nose necesita barrier ya lo sincroniza
    //private esatblece la varible como privada por lo tanto es una variable por cada hilo, y cada una tiene acceso a la variable local
    
    for(i=0;i<N_DB;i++){//base de datos 
        float resultado=0;
        int cluster=0;
        for(j=0;j<K;j++){//cluster
            float aux=0;//variable para la sumatoria
            for(x=0;x<DIM;x++){//dimenciones
                #pragma omp atomic//nos aseguramos que la operacion se realice , por un hilo a la vez, los demas hilos tienen que esperar
                aux=(pow(centroides[j][x]-ELEMS[i][x],2))+aux;//calculo de distancia
            }
            aux=sqrt(aux);//obtenemos la raiz de la dictacia
            //aqui seleccionaremos cual  las distancias euclidianas es menor, de los k centroides
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
        Cluster[i]=cluster; //almacenamos a que kluster pertenece ese vector
    }
    return Cluster; 
}

float **promedio(int *Cluster,float **centroides,float **ELEMS,int N_DB){
    int i,j,x;//definimos variables
    float **promedios;//con promedios buscamos sumar todos los vectores asignados a cada cluster correspondiente 
    promedios = (float **)malloc(sizeof(float *) * K);
    for (i = 0; i < K; i++){
        promedios[i] = (float *)malloc(sizeof(float) * DIM);
    }
    for (i = 0; i < K; i++) {
        for (j = 0; j < DIM; j++)
            promedios[i][j] = 0;//iniciamos con todas las varibles de promedio,como 0
    }

    // pragma parallel for, se indica que puede ser ejecutado con varios hilos de forma paralela en el bucle for.
    //estamos colocando como privado i,j,x, estas se crean copias de cada una de estas, por cada hilo.
    //shared seran las variables que seran compartidas porlo que cada hilo tendra acceso a ella.
    omp_set_num_threads(T);
    #pragma omp parallel for private(i, j, x) shared(Cluster,centroides,ELEMS,N_DB,promedios)
    for(i=0;i<K;i++){//cantidad de cluster
        int y=0;//sera para contar cuantas veces se cumple que k esta en el arreglo cluster
        for(j=0;j<N_DB;j++){//base de datos
            if(Cluster[j]==i){//si en el arreglo Cluster esta el K(cluster) entramos al for sino continua iterando 
                for(x=0;x<DIM;x++){//dimenciones
                    #pragma omp atomic//nos aseguramos que la operacion se realice , por un hilo a la vez, los demas hilos tienen que esperar
                    promedios[i][x]+=ELEMS[j][x];//sumamos los vectores 
                }

                y++;                           
            }  
        }
        if(y==1){
            for(j=0;j<DIM;j++){//en caso de que solo se encuentre uno o no tenga ninguno conjunto asociado en la primera iteracion el cluster se divide por uno 
                centroides[i][j]=(promedios[i][j])/1;
            } 
        }
        else{
            for(j=0;j<DIM;j++){//el promedio lo dividimos por la cantidad de vectores que tenga asociado en este caso y
                #pragma omp critical
                centroides[i][j]=(promedios[i][j])/y;
            }   
        }
    }
    free(promedios);
    return centroides;
}

int *Kmeanuno(int *kmeans,float **centroides,float **ELEMS,int N_DB){ 
    int i,j,x; 
    int *Cluster;
    Cluster=(int *)malloc(sizeof(int)*N_DB);
    // pragma parallel for, se indica que puede ser ejecutado con varios hilos de forma paralela en el bucle for.
    //estamos colocando como privado i,j,x, estas se crean copias de cada una de estas, por cada hilo.
    //shared seran las variables que seran compartidas porlo que cada hilo tendra acceso a ella.
    omp_set_num_threads(T);
    #pragma omp parallel for private(i, j, x) shared(kmeans,centroides,ELEMS,N_DB) 

    
    for(i=0;i<N_DB;i++){//base de datos
        float resultado=0;
        int cluster=0;
        for(j=0;j<K;j++){//cluster
            float aux=0;//variable para la sumatoria
            for(x=0;x<DIM;x++){//dimenciones
                #pragma omp atomic//nos aseguramos que la operacion se realice , por un hilo a la vez, los demas hilos tienen que esperar
                aux=(pow(centroides[j][x]-ELEMS[i][x],2))+aux;//calculo de distancia
            }
            aux=sqrt(aux);//obtenemos la raiz de la dictacia
            //aqui seleccionaremos cual  las distancias euclidianas es menor, de los k centroides
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

        Cluster[i]=cluster;//almacenamos a que cluster pertenece ese vector        
    }
    return Cluster;
    
}
//obtener datos del procesador
void Cpu(char* cpuinfo)
{
    FILE* file = fopen("/proc/cpuinfo", "r");
    if (file == NULL) {
        printf("Error al abrir el archivo /proc/cpuinfo\n");
        return;
    }
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "model name : %[^\n]", cpuinfo) == 1) {
            break;
        }
    }
    fclose(file);
}

//escribo
void EscribirTxt(int *Cluster,int N_DB, int num_cores, int num_threads, float paralelo,float cpu_time_used){
    char cpuinfo[256];
    FILE *archivo;
    Cpu(cpuinfo);
    archivo = fopen("resultados.txt", "w");//abrimos el archivo para escribir

    if (archivo == NULL)
    {
        printf("Error al abrir el archivo.\n");
    }
    for (int i = 0; i < N_DB; i++)
    {
        fprintf(archivo, "El vector %i pertenece al clúster: %i\n",i, Cluster[i]);//escribimos a que kluster pertenece cada vector
    }
    fprintf(archivo, "\n---- Datos generales ----\n");
    fprintf(archivo, "Tiempo de ejecución paralelo: %f\n",paralelo);
    fprintf(archivo, "Tiempo de ejecución secuencial: %f segundos\n", cpu_time_used);
    fprintf(archivo, "Cantidad de vectores: %d\n", N_DB);
    fprintf(archivo, "Cantidad de núcleos del sistema: %ld\n", num_cores);
    fprintf(archivo, "Cantidad de hilos del sistema: %ld\n", num_threads);
    fprintf(archivo, "Nombre del procesador y frecuencia: %s\n", cpuinfo);
    fprintf(archivo, "Tamaño de caché L1 de datos: %ld bytes\n", sysconf(_SC_LEVEL1_DCACHE_SIZE));
    fprintf(archivo, "Tamaño de caché L2 de datos: %ld bytes\n", sysconf(_SC_LEVEL2_CACHE_SIZE));
    fprintf(archivo, "Tamaño de caché L3 de datos: %ld bytes\n", sysconf(_SC_LEVEL3_CACHE_SIZE));
    fprintf(archivo, "Speed-Up (Tiempo secuencial / Tiempo paralelo): %f\n",(cpu_time_used/paralelo));
    fclose(archivo);
}

int main()
{
	// Creamos los valores y punteros que contendran la base de datos

	int N_DB, i, j,a,iterador;
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

    //declaramos variables
    float **centroides_1,**centroides;
    int *kmeans_1,*kmeans,*resultado;
    double start_time = omp_get_wtime();//tiempo de inicio
    long num_cores = sysconf(_SC_NPROCESSORS_ONLN); // Número de procesadores
    long num_threads = sysconf(_SC_NPROCESSORS_CONF);   // Número de hilos

 
    //tomamos los primeros centroides
    centroides = (float **)malloc(sizeof(float *) * K);
    for (i = 0; i < K; i++)
        centroides[i] = (float *)malloc(sizeof(float) * DIM);
    for (i = 0; i < K; i++) {
        //int idx = rand() % N_DB;para hacerlo ramdon
        for (j = 0; j < DIM; j++)
            centroides[i][j] = ELEMS[i][j];
    } 

   

    //Código paralelo
    
    //-----------------ejecutamos el algoritmo kmeans y recalculamos los centroides
    kmeans=Kmeans(centroides,ELEMS,N_DB);
    centroides=promedio(kmeans,centroides,ELEMS,N_DB);
    //for(i=0;i<N_DB;i++){printf("%i",kmeans[i]);}

    //se crea el puntero con dimenciones N_DB  para saber a que cluster pertenece
    resultado = (int *)malloc(sizeof(int) * N_DB);
    iterador=1;
    while(1){
        int contador=0;
        iterador++;
        kmeans_1=Kmeanuno(kmeans,centroides,ELEMS,N_DB);
        centroides=promedio(kmeans_1,centroides,ELEMS,N_DB);
        for(i=0;i<N_DB;i++){
            if(kmeans_1[i]==kmeans[i]){//comparo si en la ejecucion anterior resultaron y el resultado actual  los mismo kluster
                contador++;
            }  
        }
        printf("\n");
        if(contador==N_DB){  //si contador resulta ser igual a N_DB significa que los datos del kmeans anterior son igual al kmeans actual
            for(i=0;i<N_DB;i++){
                resultado[i]=kmeans_1[i];
            }
           printf("iteración: %i\n",iterador);
           break;
        }
        else{//en caso de que los cluster nos sean iguales que la iteracion anterior, volvemos el kmeans con su nuevo promedio
            kmeans=Kmeanuno(kmeans_1,centroides,ELEMS,N_DB);
            centroides=promedio(kmeans,centroides,ELEMS,N_DB);
            printf("iteración: %i\n",iterador);
        }
    }
    for(i=0;i<N_DB;i++){
        printf("\n%i\n",resultado[i]);
    }
    
    double end_time = omp_get_wtime();//  tiempo de fin
    double tiempo_paralelo = end_time - start_time;//tiempo de ejecucion


    // Código secuencial
    printf("-----------------Secuencial-----------------");
    float **centroides2,**centroides1;
    int *kmeans2,*kmeans1,*resultado1;
    clock_t start, end;   // para medir el tiempo de ejecución

    //asiganamos los k primeros vectores de N_DB, como centroides
    centroides1 = (float **)malloc(sizeof(float *) * K);
    for (i = 0; i < K; i++)
        centroides1[i] = (float *)malloc(sizeof(float) * DIM);
    for (i = 0; i < K; i++) {
        //int idx = rand() % N_DB;para hacerlo ramdon
        for (j = 0; j < DIM; j++)
            centroides1[i][j] = ELEMS[i][j];
    }
   
    
    start = clock(); // Medir el tiempo de ejecución
    kmeans1=KmeansSecuencial(centroides1,ELEMS,N_DB);
    centroides1=promedioSecuencial(kmeans1,centroides1,ELEMS,N_DB);

    //for(i=0;i<N_DB;i++){printf("%i",kmeans[i]);}

    resultado1 = (int *)malloc(sizeof(int) * N_DB);
    int iterador1=1;
    while(1){
        int contador1=0;
        iterador1++;
        kmeans2=KmeanunoSecuencial(kmeans,centroides1,ELEMS,N_DB);
        centroides1=promedioSecuencial(kmeans2,centroides1,ELEMS,N_DB);
        for(i=0;i<N_DB;i++){
            if(kmeans2[i]==kmeans1[i]){//comparo si en la ejecucion anterior resultaron y el resultado actual  los mismo kluster
                contador1++;
            }  
        }
        printf("\n");
        if(contador1==N_DB){  //si contador resulta ser igual a N_DB significa que los datos del kmeans anterior son igual al kmeans actual
            for(i=0;i<N_DB;i++){
                resultado1[i]=kmeans2[i];
            }
           printf("iteración: %i\n",iterador1);
           break;
        }
        else{//en caso de que los cluster nos sean iguales que la iteracion anterior, volvemos el kmeans con su nuevo promedio
            kmeans1=KmeanunoSecuencial(kmeans2,centroides1,ELEMS,N_DB);
            centroides1=promedioSecuencial(kmeans1,centroides1,ELEMS,N_DB);
            printf("iteración: %i\n",iterador1);
        }
    }
    //for(i=0;i<N_DB;i++){printf("%i",resultado1[i]);}

    end = clock();
    float cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;//tiempo de ejeción del codigo  secuencial

    int sumita;
    for(i=0;i<N_DB;i++){
        if(resultado[i]==resultado1[i]){
            sumita++;
        }   
    }
    printf("es igual %i ",sumita);
    //escritura
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
