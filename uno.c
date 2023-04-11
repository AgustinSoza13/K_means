#include<stdio.h>
#include<stdlib.h>
#include <time.h> /* Nueva librería necesaria para la función srand */
#include<math.h>
#define K 3
#define pass (void)0

int main(){
    float ELEMS[4][5] = { {10.0, 20, 30, 42.0, 50},{60.0,8.20, 35.0, 30, 50},{10.0, 20, 30, 80.0, 50},
    {10.0, 12.0, 30, 4.0, 0.50}};
    float centroides[2][5]={{60.0,8.20, 30, 30, 50},{10.0, 20, 30, 40, 50}};
    int i,j,k;
    
    for(i=0;i<4;i++){//cluster
        float resultado=0;
        int cluster=0;
        float aux=0;
        for(j=0;j<2;j++){
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
            
            //se realcaculan los cluster 
            //agrgar a que cluster pertence en una lista de lista             
        }
        printf("\nññññi el cluster es:%i",cluster);
        printf("la distancia menor es_%f\n\n",resultado);
        


        
        
    }
    

    return 0;   
}

