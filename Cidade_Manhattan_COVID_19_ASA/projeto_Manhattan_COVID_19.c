/*Aluna: Rita Teresa Oliveira (92546)*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT 100
#define WHITE 0
#define GREY 1
#define BLACK 2
#define CAPACITY 1 /*capacidade de cada arco do grafo*/


typedef struct node *link;

struct node{
    int crossroad;/*indice do vertice v*/
    int flow; /*fluxo entre os vertice u e v*/
    int capacity;/*capacidade entre u e v*/
    link next;
};

/*O grafo e representado por listas de adjacencia*/
struct graph{
    int V;
    int s;
    int t;
    link *adj;
};


typedef struct graph *Graph;


link insertBegin(int v,link head){
    link l=malloc(sizeof(struct node));
    l->crossroad=v;
    l->flow=0;
    l->capacity=CAPACITY;
    l->next=head;
    return l;
}


int insertEdge(Graph G,int u,int v){
    link l;
    /*verifica se o arco (u,v) existe no grafo G*/
    for(l=G->adj[u];l!=NULL;l=l->next){
        if(l->crossroad==v){
            if(l->flow==l->capacity)
                l->flow-=l->capacity;
            return 0;
        }
    }
    G->adj[u]=insertBegin(v,G->adj[u]);
    return 1;
}


Graph graphInit(int M,int N){
    int i;
    Graph G=malloc(sizeof(struct graph));
    G->V = 2*(M*N) + 2;
    G->s = G->V - 2;
    G->t = G->V - 1;
    G->adj=malloc((G->V)*sizeof(link));
    for(i=0; i<G->V; i++)
        G->adj[i]=NULL;
    return G;
}


int whichVertex(Graph G, int m, int n,int M){
    return (M * n) - (M - m + 1);
}

/*Para cada cruzamento (m,n), adiciona um arco para (m+1) e (n+1) */
void buildRoads(Graph G,int M,int N){
    int i,j,u,v;

    for(i=1; i<=N;i++){
        for(j=1;j<=M;j++){

            u=whichVertex(G,j,i,M);
            if(j+1<=M){
                /*adiciona um arco para (m+1)*/
                v=whichVertex(G,j+1,i,M);
                insertEdge(G,u+(M*N),v); 
                insertEdge(G,v+(M*N),u); 
            
            }
            if(i+1<=N){
                /*adiciona um arco para (n+1)*/
                v=whichVertex(G,j,i+1,M);
                insertEdge(G,u+(M*N),v); 
                insertEdge(G,v+(M*N),u);  
            }
            /*adiciona o arco de vertice de entrada para o vertice de saida */
            insertEdge(G,u,u+(M*N));
        }
    }
}


void addCitizen(Graph G,int m,int n,int M){
    int v=whichVertex(G,m,n,M);
    insertEdge(G,G->s,v);
    
}


void addSupermarkets(Graph G,int m,int n,int M,int N){
    int v=whichVertex(G,m,n,M);
    insertEdge(G,v +(M*N),G->t);  
}


void addingCitizenAndSupermarkets(Graph G,int S,int C,int M,int N,char*line){
    int num1;
    int num2;
    int i=0;

    while(i<S && fgets(line,INPUT,stdin)){
        sscanf(line,"%d %d",&num1,&num2);
        addSupermarkets(G,num1,num2,M,N); /*Adicao dos arcos para t no grafo */
        i++;
    }

    i=0;
    while(i<C && fgets(line,INPUT,stdin)){
        sscanf(line,"%d %d",&num1,&num2);
        addCitizen(G,num1,num2,M); /*Adicao dos arcos a partir de s no grafo */
        i++;
        
    }
}

int QUEUEempty(link *head){
    return *head==NULL;
}

void QUEUEput(link *head,link *tail,int n){
    if((*head)==NULL){
        (*head)=(*tail)=insertBegin(n,(*head));
        return;
    }
    (*tail)->next=insertBegin(n,(*tail)->next);
    (*tail)=(*tail)->next;
     
}

int QUEUEget(link *head){
    int n= (*head)->crossroad;
    link l=(*head)->next;
    free((*head));
    (*head)=l;
    return n;
}

void freeQUEUE(link *head){
    link l;
    while(*head){
        l=(*head)->next;
        free((*head));
        (*head)=l;
    }
}


int* BFS(Graph G,int s,int*p){
    link head=NULL;
    link tail=NULL;
    int *color=malloc(G->V*sizeof(int));
    memset(p,-1,G->V*sizeof(int));
    memset(color,WHITE,G->V*sizeof(int));
    p[s]=-2;
    QUEUEput(&head,&tail,s);
    while(!QUEUEempty(&head)){
        link l;
        int u=QUEUEget(&head);
        for(l=G->adj[u];l!=NULL;l=l->next){
            int v=l->crossroad;
            if (color[v]==WHITE && l->capacity-l->flow>0){
                p[v]=u;
                if(v==G->t){
                    free(color);
                    freeQUEUE(&head);
                    return p;
                }
                color[v]=GREY;
                QUEUEput(&head,&tail,v);
            }
        }
        color[u]=BLACK;
    } 
    free(color);
    return p;
}


int edmondsKarp(Graph G){
    int max=0;
    int *p=malloc(G->V*sizeof(int));

    while(1){
        int i;
        link l;
        p=BFS(G,G->s,p);
        if(p[G->t]==-1)
            break;
        i=G->t;
        while(p[i]!=-2){
            for(l=G->adj[p[i]];l!=NULL;l=l->next){
                if(l->crossroad==i)
                    l->flow+=l->capacity; 
            }
            insertEdge(G,i,p[i]); /*adciona o arco para tras. Se existe este arco, a funcao insertEdge diminui o fluxo deste arco */
            i=p[i];
        }
        max+=1;
    }
    free(p);
    return max;
}


void freeCity(Graph G){
    int i;
    link l;
    for(i=0;i<G->V;i++){
        while(G->adj[i]){
            l=G->adj[i];
            G->adj[i]=G->adj[i]->next;
            free(l);
        }
    }
    free(G->adj);
    free(G);
}


int main(){
    char line[INPUT];
    int M;
    int N;
    int S;
    int C;
    Graph City;

    /*Leitura da primeira linha dos dados de entrada que contem o numero de avenidas (M) e o numero de ruas (N)*/
    if(fgets(line,INPUT,stdin))  
        sscanf(line,"%d %d",&M,&N);

    /*Inicializacao do grafo representado por listas de adjacencia com 2(MN) + 2 vertices*/
    City=graphInit(M,N); 

     /*Adicao dos arcos no grafo*/
    buildRoads(City,M,N);

    /*Leitura da segunda linha dos dados de entrada que contem o numero de supermercados(S) e o numero de cidadaos(C)*/
    if(fgets(line,INPUT,stdin)) 
        sscanf(line,"%d %d",&S,&C);

    /*Leitura de S e C linhas do input*/
    addingCitizenAndSupermarkets(City,S,C,M,N,line); 

    /*Aplicacao do Edmonds Karp para encontrar o numero maximo de cidadaos que podem deslocar-se aos supermercados sem se encontrarem e
    apresentacao deste numero no output*/
    printf("%d\n",edmondsKarp(City)); 

    /*Libertacao do grafo*/
    freeCity(City);
    return 0;
}