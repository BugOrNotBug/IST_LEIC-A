# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include "contacto.h"
# include "hastables.h"

static int M_htnome; /*tamanho da tabela htnome*/
static int N_htnome; /*numero de elementos da tabela htnome*/

static int M_htordem; /*tamanho da tabela htordem*/
static int N_htordem; /*numero de elementos da tabela htordem*/

static int M_htdominio; /*tamanho da tabela htdominio*/
static int N_htdominio; /*numero de elementos da tabela htdominio*/

static int num_cont=0; /*Numero de contactos que foram inseridos*/

/*tabelas de dispersao*/
static contacto *ht_nome; /*guarda contactos*/
static contacto *ht_ordem; /*guarda contactos*/
static dominio *ht_dominio; /*guarda dominio*/
 

/*--------------|Funcoes de dispersao|-----------------------*/

static unsigned hash_string(char *nome,int M){
    unsigned long hash =5381;
    int c;
    while((c=*nome++))
        hash=hash*33 +c;
    return hash%M;
}

static int hash_int(int ordem,int M){
    return ordem % M;
}

/*-----------|Inicializacao das tabelas de dispersao|--------------*/

void iniciar_htnome(int num){
    int i;
    N_htnome=0;
    M_htnome=num;
    ht_nome = (contacto*)malloc(M_htnome*sizeof(contacto));
    for(i=0;i<M_htnome;i++)
        ht_nome[i]=NULL;
}

void iniciar_htordem(int num){
    int i;
    N_htordem=0;
    M_htordem=num;
    ht_ordem= (contacto*)malloc(M_htordem*sizeof(contacto));
    for(i=0;i<M_htordem;i++)
        ht_ordem[i]=NULL; 
}


void iniciar_htdominio(int num){
    int i=0;
    N_htdominio=0;
    M_htdominio=num;
    ht_dominio= (dominio*)malloc(M_htdominio*sizeof(dominio));
    for(i=0;i<M_htdominio;i++)
        ht_dominio[i]=NULL; 
}

/*-------------|Adicao nas tabelas|---------------*/

void inserir_htnome(contacto con){
    int i;
    i=hash_string(con->nome,M_htnome);
    while(ht_nome[i]!=NULL)
        i=(i+1)%M_htnome;
    ht_nome[i]=con;
    if(N_htnome++> M_htnome/2)
        expandir_htnome();
}

void inserir_htordem(contacto con){
    int j;
    j=hash_int(con->ordem,M_htordem);
    while(ht_ordem[j]!=NULL)
        j=(j+1)%M_htordem;
    ht_ordem[j]=con;
    num_cont++;
    if(N_htordem++ > M_htordem/2)
        expandir_htordem();   
}

void inserir_htdominio(dominio domi){
    int i;
    i=hash_string(domi->dominio,M_htdominio);
    while(ht_dominio[i]!=NULL)
        i=(i+1)%M_htdominio;
    ht_dominio[i]=domi;
    if(N_htdominio++>M_htdominio/2)
        expandir_htdominio();
}

void verificar_inserir_dominio(char* d){
    dominio dom;
    if(!procura_htdominio(d,'a')){
        dom=(dominio)malloc(sizeof(struct domi));
        dom->dominio=(char*) malloc(sizeof(char)*strlen(d)+1);
        strcpy(dom->dominio,d);
        dom->ocorrencia=1;
        inserir_htdominio(dom);
    }
}

/*---------------|Expandir as tabelas|--------------------------*/

void expandir_htnome(){
    int i;
    contacto* aux=ht_nome; /*Uma tabela auxiliar */
    iniciar_htnome(M_htnome+M_htnome); /*Cria uma nova tabela de dispersao com o dobro do tamanho*/
    for(i=0;i<M_htnome/2;i++){
        if(aux[i]!=NULL)
            inserir_htnome(aux[i]); /*Os contactos da tabela antiga serao inseridos na nova */
    }
    free(aux);
}

void expandir_htordem(){
    int i;
    contacto* aux=ht_ordem;
    iniciar_htordem(M_htordem+M_htordem);
    for(i=0;i<M_htordem/2;i++){
        if(aux[i]!=NULL)
            inserir_htordem(aux[i]);
    }
    free(aux);
}

void expandir_htdominio(){
    int i;
    dominio*aux=ht_dominio;
    iniciar_htdominio(M_htdominio+M_htdominio);
    for(i=0;i<M_htdominio/2;i++){
        if(aux[i]!=NULL)
            inserir_htdominio(aux[i]);
    }
    free(aux);
}

/*-----------|Procura nas tabelas|---------------*/

int procura_htnome(char *nome,char car){
    int i;
    contacto con;
    i=hash_string(nome,M_htnome);
    while(ht_nome[i]!=NULL){
        if(!strcmp(ht_nome[i]->nome,nome)){
            con=ht_nome[i];
            if(car=='a') 
                /*Se caracter recebido for a, entao a funcao, se o contacto existir, indica que este existe*/
                printf("Nome existente.\n");
            if(car=='p')
                /*Se for p, escreve no terminal o nome,email e telefone do contacto*/
                printf_contacto(con);
            if(car=='r')
             /*Se for r, remove o contacto na tabela com funcao remover_ht*/
                remover_ht(i);
            return i;
        }
        else
            i=(i+1)%M_htnome;
    }
    if(car!='a')
        printf("Nome inexistente.\n");
    return -1;
}

int procura_htdominio(char *dominio,char car){
    int i;
    i=hash_string(dominio,M_htdominio);
    while(ht_dominio[i]!=NULL){
        if(!strcmp(ht_dominio[i]->dominio,dominio)){
            if(car=='a') /*Se o caracter for a, aumenta a ocorrencia do dominio*/
                ht_dominio[i]->ocorrencia++;
            if(car=='r') /*Se for r, diminui a ocorrencia */
                ht_dominio[i]->ocorrencia--;
            return ht_dominio[i]->ocorrencia;
        }
        else
            i=(i+1)%M_htdominio;        
    }
    return 0;
}


/*------------|Listar ordenadamente uma tabela|--------------*/

void listar_contactos(){
    int i,j;
    for(i=0;i<num_cont;i++){
        j=hash_int(i,M_htordem);
        while(ht_ordem[j]!=NULL){
            if(ht_ordem[j]->ordem==i){  
                printf_contacto(ht_ordem[j]);
                break;
            }
            else
                j=(j+1)%M_htordem;
        }
    }
}

/*---------------|Removacao e alterecao nas tabelas|---------------*/

void remover_ht(int i){
    int j,e,r;
    contacto con;

    j=hash_int(ht_nome[i]->ordem,M_htordem);

    /*Procura o contacto na tabela htordem*/
    while(ht_ordem[j]!=NULL){
        if(ht_nome[i]->ordem==ht_ordem[j]->ordem)
            break;
        else
            j=(j+1)%M_htordem;
    }
    
    /*Diminui a ocorrencia do dominio do email do contacto*/
    procura_htdominio(obter_dominio(ht_nome[i]->email),'r');

    /*Liberta a memoria associada ao contacto, ou seja,
    remove o contacto de posicao i na tabela htnome e posicao j na tabela htordem*/
    freecontacto(ht_nome[i]); ht_nome[i]=NULL; ht_ordem[j]=NULL;

    N_htnome--; N_htordem--; /*Diminui os numeros de ambas as tabelas*/

    /*Reinsere os elementos seguintes da tabela htnome*/
    for(e=(i+1)%M_htnome;ht_nome[e]!=NULL;e=(e+1)%M_htnome){
        con=ht_nome[e];
        ht_nome[e]=NULL;
        inserir_htnome(con);
    }

    /*Reinsere os elementos seguintes da tabela htordem*/
    for(r=(j+1)%M_htordem;ht_ordem[r];r=(r+1)%M_htordem){
        con=ht_ordem[r];
        ht_ordem[r]=NULL;
        inserir_htordem(con);
    }
}


void mudar_email(char *nome,char *email){
    int i=procura_htnome(nome,'e');

    if(i!=-1){ /*Verifica se o nome existe*/
        procura_htdominio(obter_dominio(ht_nome[i]->email),'r');
        free(ht_nome[i]->email);

        /*Coloca o novo email*/
        ht_nome[i]->email=(char*) malloc(sizeof(char)*(strlen(email)+1)); 
        strcpy(ht_nome[i]->email,email);

        /*Verifica se o dominio do email ja existe. Adiciona na tabela ou aumenta a ocorrencia
        conforme a existencia*/
        verificar_inserir_dominio(obter_dominio(email));
    
    }
}

/*--------------|Libertacao de memoria|--------------*/

void free_tables(){
    int i;
    for(i=0;i<M_htnome;i++){
        if(ht_nome[i]!=NULL)
            freecontacto(ht_nome[i]);
        else
            free(ht_nome[i]);
    }
    free(ht_nome); free(ht_ordem);

    for(i=0;i<M_htdominio;i++){
        if(ht_dominio[i]!=NULL)
            free(ht_dominio[i]->dominio);
        free(ht_dominio[i]);   
    }  
    free(ht_dominio);        
}


