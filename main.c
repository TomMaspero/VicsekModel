#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "vector.h"
#include "funh.h"
#include "glut.h"
#define PI 3.141592654

double frand()
{
    double k=1.0*rand()/RAND_MAX;
    while(k==1)
        k=1.0*rand()/RAND_MAX;
    return k;
}

pez *sist;
int n=1000;
int hash_Lx=10, hash_Ly=10; //cantidad de cajas (10 y 10)
double hash_cell_x=0, hash_cell_y=0; //tamaño de las cajas

int main(int argc, const char **argv)
{
    double eta, r, magnitud=10, dt=0.1; //r distancia entre los pececitos
    double ruido=0.25, R=10;

    int aux_h=0, *aux_mem;
    hash_cell_x=(1000/hash_Lx); //Tamano de las cajas, con esto las cajas pueden no ser cuadradas
    hash_cell_y=(1000/hash_Ly);
    vector dpos;
    int numcajas = hash_Lx*hash_Ly; //memh=4;

    int *cajas;
    cajas = (int*) calloc(numcajas, sizeof(int));
    if(cajas==NULL){
        printf("error al asignar memoria a cajas\n");
        exit(117);
    }

    int** hash;
    hash=(int**) calloc(numcajas, sizeof(int*));
    if(hash==NULL){
        printf("error al asignar memoria a hash\n");
        exit(117);
    }

    for(int i=0; i<numcajas; i++){
        hash[i]=(int*) calloc(n, sizeof(int));
        if(hash[i]==NULL){
            printf("error al asignar memoria a hash 2\n");
            exit(117);
        }
    }

//    aux_mem=(int*) calloc(1, sizeof(int));
//    if(aux_mem==NULL){
//        printf("error al asignar la memoria a aux_mem\n");
//        exit(444);
//    }

    srand(time(NULL));
    for(int i=0; i<100; i++){rand();}

    sist = (pez*) calloc(n, sizeof(pez));
    if(sist==NULL){
        printf("error al asignar memoria a pez\n");
        exit(117);
    }

    for(int i=0; i<n; i++){
        sist[i].pos = vv(rand()%1000,rand()%1000);
        sist[i].angulo = 2*frand()*PI;
        sist[i].vel = vv(magnitud*cos(sist[i].angulo), magnitud*sin(sist[i].angulo));
    }

    glutStuff(argc, argv);

    while(1){

        for(int i=0; i<n; i++){
            sist[i].h = calcH(sist[i]);

            if(sist[i].h>=numcajas){printf("error, numero de cajas excedido %d\n", sist[i].h);}
            hash[sist[i].h][cajas[sist[i].h]]=i;
            cajas[sist[i].h]+=1;

//            if(cajas[sist[i].h]==memh){
//                for(int j=0; j<numcajas; j++){
//                    aux_mem[0] = (int*) realloc(hash[j], 2*memh*sizeof(int));
//                    if(aux_mem == NULL){
//                        printf("error al realocar memoria al hash\n");
//                        exit(117);
//                    }
//                    else{hash[j]=aux_mem;}
//                    memh*=2;
//                }
//            }
        }

        for(int i=0; i<n; i++){
            sist[i].promedio=0;
            sist[i].vecinos=0;
            aux_h = sist[i].h;

            for(int j=0; j<cajas[aux_h]; j++){
                if(hash[aux_h][j]!=i){
                    r = norm(dif(sist[i].pos, sist[hash[aux_h][j]].pos));
                    if(r<=R){
                        sist[i].promedio += sist[hash[aux_h][j]].angulo;
                        sist[i].vecinos += 1;
                    }
                }
            }

            if(sist[i].vecinos>0){
                sist[i].promedio /= 1.0*sist[i].vecinos; //hacer esto de otra forma para que no vayan siempre a la izquierda???
                sist[i].angulo = sist[i].promedio;
                sist[i].promedio=0;
            }
        }

        for(int i=0; i<n; i++){
            eta = (0.5 - frand())*ruido;
            sist[i].angulo += eta;

            while(sist[i].angulo > 2*PI){sist[i].angulo -= 2*PI;}
            while(sist[i].angulo < 0){sist[i].angulo += 2*PI;}

            if(sist[i].pos.x < 0.1){sist[i].pos.x = 999;}
            else if(sist[i].pos.x > 999){sist[i].pos.x = 0.1;}
            if(sist[i].pos.y < 0.1){sist[i].pos.y = 999;}
            else if(sist[i].pos.y > 999){sist[i].pos.y = 0.1;}

            sist[i].vel = vv(magnitud*cos(sist[i].angulo), magnitud*sin(sist[i].angulo));

            dpos = esc(sist[i].vel, dt);
            sist[i].pos = add(sist[i].pos, dpos);

        }

    for(int i=0; i<numcajas; i++){cajas[i]=0;} //reseteo el cajas
        callGlut();
    }

    return 0;
}
