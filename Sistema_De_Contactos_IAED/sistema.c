# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include "contacto.h"
# include "sistema.h"
# include "hastables.h"


void iniciar_sistema(){
    /*Inicia as tabelas como tabela de 10 elementos*/
    iniciar_htnome(10);
    iniciar_htordem(10);
    iniciar_htdominio(10);
}

void inserir_no_sistema(char *nome,char *email,char *telefone){   
    contacto conc; /*con contem o novo contacto introduzido*/

    if(procura_htnome(nome,'a')==-1){ /*verifica se o nome do contacto ja existe*/
        conc=novo_contacto(nome,email,telefone);
        inserir_htnome(conc);
        inserir_htordem(conc);
        verificar_inserir_dominio(obter_dominio(email));  
    }
}

void procura_nome(char *nome){
    procura_htnome(nome,'p');
}

void remover_contacto(char *nome){
    procura_htnome(nome,'r');
}

void ocorrencia_dominio(char *dominio){
    int num; /*numero de ocorrencias do dominio*/
    num=procura_htdominio(dominio,'c');
    printf("%s:%d\n",dominio,num);
}

void free_sistema(){
    free_tables();
}





