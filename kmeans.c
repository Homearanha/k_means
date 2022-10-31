#include <stdlib.h>
#include <stdio.h>

#ifndef N
#define N 10000000 //numero de amostras
#endif
#ifndef K
#define K 4 //numero de clusters
#endif

struct ponto{
        float x,y;
        int clt;
};

struct ponto *p=NULL; //array de pontos
struct ponto *c=NULL; //array de centros de cluster

void inicializa() {
        //printf("hello");
        p=malloc(N*sizeof(struct ponto));
        c=malloc(K*sizeof(struct ponto));
        srand(10); //seed
        for(int i = 0; i < N; i++) {
                p[i].x = (float) rand() / RAND_MAX; //coordenada x do ponto i
                p[i].y = (float) rand() / RAND_MAX; //coordenada y do ponto i
                p[i].clt = 0; //cluster a que i pertence
                //printf("%d",i);
        }
        for(int i = 0; i < K; i++) {
                c[i].x = p[i].x; // x do centro do cluster = x do ponto
                c[i].y = p[i].y; // y do centro do cluster = y do ponto
                p[i].clt=i; // atribuiçao dos K primeiros centroides de cluster
        }
}

int atribuir_cluster() {
        int flag=0;
        float m,tmp;
        for(int i=0;i<N;i++){
                //m=sqrtf((p[i].x-c[p[i].clt].x) * (p[i].x-c[p[i].clt].x) )+( (p[i].y-c[ p[i].clt ].y ) * (p[i].y-c[ p[i
].clt ].y ) );
                m=((p[i].x-c[p[i].clt].x) * (p[i].x-c[p[i].clt].x) )+( (p[i].y-c[ p[i].clt ].y ) * (p[i].y-c[ p[i].clt ]
.y ) );
                for(int j=0;j<K;j++){
                        //tmp=sqrtf( (p[i].x-c[j].x) * (p[i].x-c[j].x) )+( (p[i].y-c[j].y ) * (p[i].y-c[j].y ) );
                        tmp=( (p[i].x-c[j].x) * (p[i].x-c[j].x) )+( (p[i].y-c[j].y ) * (p[i].y-c[j].y ) );
                        //printf("m: %f -- tmp: %f -- %d\n",m,tmp,m<tmp);
                        if(j!=p[i].clt && m>tmp){
                                m=tmp;
                                p[i].clt=j;
                                flag=1;
                        }

                }
        }
        return flag;
}

int reavaliar_centros(){
        int aux[K];
        int flag=0;
        struct ponto centro[4];
        for(int i=0;i<K;i++){
                aux[i]=0;
                centro[i].x=0;
                centro[i].y=0;
        }
        int j=0;
        for(int i=0;i<N;i++){
                j=(int) p[i].clt;
                aux[j]++;
                centro[j].x+=p[i].x;
                centro[j].y+=p[i].y;
        }

        for(int i=0;i<K;i++){
                centro[i].x /= aux[i];
                centro[i].y /= aux[i];
                if(c[i].x!=centro[i].x || c[i].y!=centro[i].y){
                        flag=1;
                        c[i]=centro[i];
                }
        }
        return flag;
}

int loop(){
        int it=-1, flag=1;
        while(flag){
                //printf("%d",it);
                flag=atribuir_cluster();
                flag+=reavaliar_centros();
                it++;
        }
        return it;
}

int main(){
        printf("inicio\n");

        int it; //numero de iterations

        int n[K]; // size do cluster
        for(int i=0;i<K;i++) n[i]=0;
        inicializa();
        it=loop();
        for(int i=0;i<N;i++) n[ p[i].clt ]++; // contar o size do cluster

        //output
        printf("N = %d, K = %d\n",N,K);
        for(int i=0;i<K;i++) printf("Center: (%f, %f) : Size: %d\n",c[i].x,c[i].y,n[i]);
        printf("Iterations: %d\n",it);

        free(p);
        free(c);

        return 0;
}