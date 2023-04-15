#include<stdio.h>
#include<stdlib.h>
#include <time.h> /* Nueva librería necesaria para la función srand */
#include<math.h>
#define K 3
#define pass (void)0

float **euclidiana(float centroides,float ELEMS){
    int i,j,k;
    int *Cluster;
    Cluster=(int *)malloc(sizeof(int)*5);
    for(i=0;i<5;i++){//base de datos
        float resultado=0;
        int cluster=0;
        float aux=0;
        for(j=0;j<2;j++){//cluster
            for(k=0;k<5;k++){
                aux=(pow(centroides[j][k]-ELEMS[i][k],2))+aux;
                printf("--%f--",aux);
            }
            aux=sqrt(aux);

            printf("\n**%f**",aux); 
            if (resultado==0){
                resultado=aux;
                cluster=j;

            }else
                if(resultado>aux){
                    resultado=aux;    
                    cluster=j;   
                }
                else
                    continue;           
        }
        Cluster[i]=cluster;   
    }/*
    for ( i = 0; i < 5; i++)
    {
        printf("\nel cluster es:%i",Cluster[i]);
    }*/
    return Cluster;
}



int main(){
    float ELEMS[5][5] = { {64.0, 20, 30, 42.0, 50},{60.0,8.20, 35.0, 30, 50},{10.0, 20, 15.2, 80.0, 50},
    {10.0, 12.0, 30, 4.0, 0.50},{34.6,56.0,5,12.0,1}};
    float centroides[2][5]={{60.0,8.20, 30, 30, 50},{10.34, 20, 30, 40, 50}};
    
    

    

    float *Cluster=euclidiana(centroides,ELEMS);





    
   
    /*int busqueda=1;
    int t=0;
    //a=detectar();

    for (int x = 0; x < 2; x++) {//fila elemntos
        int y=1;
        for(j=0;j<5;j++){
            
            if(Cluster[j]==x){
                
                for(k=0;k<5;k++){
                    centroides[x][k]=((centroides[x][k]+ELEMS[j][k]));
                }
                y++;   
            }
        }
        
        printf("contador:%i\n",y);
        for(j=0;j<5;j++){
            printf("%f\n",centroides[x][j]/y);  //nuevos centroides
        }
        
    }
*/
    //comparar los centroides
    printf("\n");/*
    for(i=0;i<2;i++){
        for(j=0;j<5;j++){
            printf("%f\n",centroides[i][j]);
        }
        printf("\n");
        
    }
*/
    

    return 0;   
}

