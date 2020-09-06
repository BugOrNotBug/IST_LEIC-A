/*---------|Constante|---------*/

#define MAXCARACTER 2  /*Maximo de caracteres com tamanho 2*/

/*------|Bibliotecas|-------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "contacto.h"

static int ordem_contac=0; /*ordenacao do novo contacto inserido. Vai aumentando a medida que se inserem contactos*/

contacto novo_contacto(char *nome, char *email, char*telefone){

    contacto novo = (contacto)malloc(sizeof(struct conexao));/*Novo Contacto*/

    novo->nome= (char*) malloc(sizeof(char)*(strlen(nome)+1));        
    novo->email=(char*) malloc(sizeof(char)*(strlen(email)+1)); 
    novo->telefone=(char*) malloc(sizeof(char)*(strlen(telefone)+1)); 

    strcpy(novo->nome,nome);
    strcpy(novo->email,email);
    strcpy(novo->telefone,telefone);

    novo->ordem=ordem_contac;
    ordem_contac++;

    return novo;
}

void freecontacto(contacto con){
    free(con->nome);
    free(con->email);
    free(con->telefone);
    free(con);
}


void printf_contacto(contacto con){
    printf("%s %s %s\n",con->nome,con->email,con->telefone);
}

char *obter_dominio(char *email){
    char *token;
    char car[MAXCARACTER]="@";
    token=strtok(email,car);
    if(token!=NULL)
        token=strtok(NULL,car);
    return token;
}