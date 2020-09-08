/*Aluna: Rita Teresa Oliveira (92546)*/
#include <stdio.h>
#include <stdlib.h>

#define INPUT 100
#define WHITE 0
#define GRAY 1
#define BLACK 2


/*---------Estruturas Grafos,Listas e Pilhas----------*/

typedef struct node *link;

struct node{
    int student; /*numero de um aluno*/
    link next;
};

struct graph{
    int V; /*numero de vertices que corresponde neste problema ao numero de alunos inscritos */
    int E; /*numero de arcos que corresponde neste problema ao numero de relacoes de amizade entre alunos*/
    int numSCCs; /*numero de componentes fortemente ligados (SCC) existentes no grafo*/
    link *adj;
    int *grades;/*nota estimada original de cada aluno*/
    int *compSCC;/*atribui se um numero a cada vertice para indicar a que SCC pertence. */
};

typedef struct graph *Graph;

Graph graph_friendship = NULL; /*grafo dirigido que mostra as relacoes de amizade entre alunos*/
link top=NULL;

/*-------Funcoes da Lista--------*/

link insertBegin(int v,link head){
    link l=malloc(sizeof(struct node));
    l->student=v;
    l->next=head;
    return l;
}
/*------Funcoes da Pilha---------*/

int is_empty(){
    return top==NULL;
}

void push(int student){
    top=insertBegin(student,top);
}

int pop(){
    int student;
    link old;

    if(!is_empty()){
        student=top->student;
        old=top;
        top=top->next;
        free(old);
        return student;
    }
    return -1;
}

int findStudent(int student){
    link l;
    for(l=top;l!=NULL;l=l->next){
        if(l->student==student)
            return 1;
    }
    return 0;
}

/*------Funcoes dos Grafos--------*/


Graph graphInit(int V){
    int i;
    Graph G=malloc(sizeof(struct graph));
    G->V=V;
    G->E=0;
    G->numSCCs=0;
    G->adj=malloc(V*sizeof(link));
    G->grades=malloc(V*sizeof(int));
    G->compSCC=malloc(V*sizeof(int));

    for(i=0; i<V; i++){
        G->adj[i]=NULL;
        G->grades[i]=0;
        G->compSCC[i]=0;
    }
    return G;
}

void insertGrade(Graph G,int student,int grade){
    G->grades[student]=grade;
}

void insertEdge(Graph G,int u,int v){
    G->adj[u]=insertBegin(v,G->adj[u]);
    G->E++;
}

void freeGraph(Graph G){
    free(G->adj);
    free(G->grades);
    free(G->compSCC);
    free(G);

}
/*----------------------------------------------------*/


/*--Funcao que le as notas e as amizades dos alunos e construi um grafo---*/

void readGradesAndFriendship(int N,int M,char*line){
    int num1;
    int num2;
    int i=0;

    while(i<N && fgets(line,INPUT,stdin)){
        sscanf(line,"%d",&num1);
        insertGrade(graph_friendship,i,num1);
        i++;
    }

    i=0;
    
    while(i<M && fgets(line,INPUT,stdin)){
        sscanf(line,"%d %d",&num1,&num2);
        insertEdge(graph_friendship,num1-1,num2-1);
        i++;
    }
}

/*----------------------------------------------------*/


/*-----Funcoes que aplicam o algoritmo de Tarjan-----*/

void tarjanVisit(int u,int*d,int*low,int*visited,Graph G){
    link l;
    d[u]=low[u]=*visited+1;
    (*visited)++;

    push(u);

    for(l=G->adj[u];l!=NULL;l=l->next){
        if(d[l->student]==0 || findStudent(l->student)){

            if(d[l->student]==0)
                tarjanVisit(l->student,d,low,visited,G);

            if(low[u]>low[l->student])
                low[u]=low[l->student];
        }
    }

    if(low[u]==d[u]){
        int student=-1;
        while(student!=u){
            student=pop();
            G->compSCC[student]=G->numSCCs;
        }
        G->numSCCs++;
    }
}

void SCC_Tarjan(Graph G){
    int u;
    int visited=0;
    int *d=malloc(sizeof(int)*G->V);
    int *low=malloc(sizeof(int)*G->V);

    for(u=0;u<G->V;u++)
        d[u]=0;
    for(u=0;u<G->V;u++)
        if(d[u]==0)
            tarjanVisit(u,d,low,&visited,G);
    free(d);
    free(low);
    free(top);
}

/*----------------------------------------------------*/


/*--Funcoes que ajudam a recalcular as notas estimadas de ASA---*/

link* consListSCC(Graph G){
    int u;
    link*SCC=malloc(G->numSCCs*sizeof(struct node)); 

    for(u=0;u<G->V;u++)
        SCC[G->compSCC[u]]=NULL;     
    for(u=0;u<G->V;u++)
        SCC[G->compSCC[u]]=insertBegin(u,SCC[G->compSCC[u]]);

    return SCC;
}



void SCCToOneVertex(Graph G, Graph newG, link* SCC){
    int num;
    int max=-1;
    link lScc;
    link lAdj;
    int *edge=malloc(G->numSCCs*sizeof(int));

    for(num=0;num<G->numSCCs;num++)
        edge[num]=0;

    for(num=0;num<G->numSCCs;num++){
        for(lScc=SCC[num];lScc!=NULL;lScc=lScc->next){

            if(max<G->grades[lScc->student])
                max=G->grades[lScc->student];

            for(lAdj=G->adj[lScc->student];lAdj!=NULL;lAdj=lAdj->next){

                if(edge[G->compSCC[lAdj->student]]!=1){
                    edge[G->compSCC[lAdj->student]]=1;
                    insertEdge(newG,num,G->compSCC[lAdj->student]);
                }
            }  
        }

        insertGrade(newG,num,max);
        max=-1;

        for(lScc=SCC[num];lScc!=NULL;lScc=lScc->next){ 
            for(lAdj=G->adj[lScc->student];lAdj!=NULL;lAdj=lAdj->next)
                edge[G->compSCC[lAdj->student]]=0;   
        }
    }
    free(edge);
}  


/*As duas funcao seguintes aplicam um algoritmo baseado no DFS*/
void serachBestSolutionVisit(Graph G,int u, int *color){
    link l;
    color[u]=GRAY;
    for(l=G->adj[u];l!=NULL;l=l->next){
        if(color[l->student]==WHITE)
            serachBestSolutionVisit(G,l->student,color);  
        if(G->grades[u]<G->grades[l->student])
            G->grades[u]=G->grades[l->student];
    }
    color[u]=BLACK;
}

void serachBestSolution(Graph G){
    int u;
    int *color=malloc(sizeof(int)*G->V);

    for(u=0;u<G->V;u++)
        color[u]=WHITE;
    for(u=0;u<G->V;u++)
        if(color[u]==WHITE)
            serachBestSolutionVisit(G,u,color);

    free(color);
}



void changeSCCStudentsGrades(Graph G,Graph G_SCC,link*SCC){
    int u;
    link l;
    for(u=0;u<G_SCC->V;u++){
        for(l=SCC[u];l!=NULL;l=l->next)
            G->grades[l->student]=G_SCC->grades[u];
    }
}



void freeSCC(Graph G,link *SCC){
    int u;
    link l;
    for(u=0;u<G->V;u++){

        while(SCC[u]){
            l=SCC[u];
            SCC[u]=SCC[u]->next;
            free(l);
        }

        while(G->adj[u]){
            l=G->adj[u];
            G->adj[u]=G->adj[u]->next;
            free(l);
        }
    }
    free(SCC);
    freeGraph(G);
}

/*----------------------------------------------------*/


/*----------Funcao que recalcula as notas----------------*/

void previsionASAGrades(){

    if(graph_friendship->numSCCs < graph_friendship->V){
        link* SCC=consListSCC(graph_friendship);
        Graph graph_SCC=graphInit(graph_friendship->numSCCs);

        SCCToOneVertex(graph_friendship,graph_SCC,SCC);

        if(graph_friendship->numSCCs>1)
            serachBestSolution(graph_SCC);

        changeSCCStudentsGrades(graph_friendship,graph_SCC,SCC);
        freeSCC(graph_SCC,SCC);
    }
    else
        serachBestSolution(graph_friendship);
}

/*----------------------------------------------------*/


/*----Funcao que mostra as notas estimadas e liberta o grafo----*/

void freeAndShow(Graph G){
    int i;
    link l;
    
    for(i=0;i<G->V;i++){
        printf("%d\n",G->grades[i]);

        while(G->adj[i]){
            l=G->adj[i];
            G->adj[i]=G->adj[i]->next;
            free(l);
        }
    }
    freeGraph(G);
}

/*----------------------------------------------------*/

int main(){
    char line[INPUT];
    int N;
    int M;

    if(fgets(line,INPUT,stdin))
        sscanf(line,"%d,%d",&N,&M);

    graph_friendship=graphInit(N);

    readGradesAndFriendship(N,M,line);

    SCC_Tarjan(graph_friendship);

    previsionASAGrades();
        
    freeAndShow(graph_friendship);

    return 0;

}