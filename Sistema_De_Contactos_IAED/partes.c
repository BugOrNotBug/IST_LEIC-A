
/*------|Bibliotecas|-------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "partes.h" 

#define MAXINPUT 1600 /*Maximo de caracteres no input*/
#define MAXCARACTER 2  /*Maximo de caracteres com tamanho 2*/


partes *lelinha(){
    char *token=NULL;
    char input[MAXINPUT]; /*A string do input tem 1600 caracteres*/
    const char car[MAXCARACTER]=" "; /*A string tem 2 caracteres*/
    int i=0;
    int j=0;
    int espacos=0; /*numero de espacos vazios que existe na string input*/
    int tamanho=0; /*numero de caracteres de uma string*/
    partes *p;

    fgets (input,MAXINPUT,stdin);

    /*conta o numero de espacos vazios*/
    while (input[j]!='\0'){
        if(input[j]==' ')
            espacos++;
        j++;
    }
    
    p=(partes*)malloc(sizeof(partes)*(espacos+1));

    /*separa o input em partes conforme os espacos vazios no input*/
    token=strtok(input,car);
    if(token!=NULL){
        while(token!=NULL){
            tamanho=strlen(token);
            p[i].par=(char*)malloc(sizeof(char)*(tamanho+1));
            strcpy(p[i].par,token);
            token=strtok(NULL,car);
            i++;
        }
        tamanho=strlen(p[i-1].par);
        p[i-1].par[tamanho-1]='\0'; 
    }
    return p;
  
}

void freepartes(partes *p, int n){ 
    int i;
    for(i=0;i<n;i++){
        free(p[i].par);
    }
    free(p);
}
