/*

 * Ficheiro:     projeto_parte_2.c
 * Autora:       Rita Castro Oliveira
 * Descricao:    um progrma que desenvolve um sistema de gestao de contactos que permita 
                 associar um endereco de email e numero de telefone a um nome
*/

/*------|Bibliotecas|-------*/

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include "partes.h" 
# include "contacto.h"
# include "sistema.h"
# include "hastables.h"



int main(){
    char comando; /*string comando contem o comando introduzido*/
    partes *dados; /*dados e vetor de string que contem o input do programa*/


/*------aqui inicia o programa. O sistema prepara se para guardar os contactos ou para 
        remover ou para fazer alteracoes-----*/

    iniciar_sistema();    

    while(1){

        dados=lelinha(); /*introduziu o input. O primeiro caracter do vetor dados de indicie 0 contem o comando*/
        comando=dados[0].par[0]; 
        
        switch(comando){
            case 'a':
            /*-----
            ---> O comando a tem como objetivo adicionar um novo contacto ao sistema
            -@ Indicie 1 do vetor dados contem o nome do contacto
            -@ Indicie 2 contem o email 
            -@ Indicie 3 contem o numero de telefone
            ------*/
                inserir_no_sistema(dados[1].par,dados[2].par,dados[3].par);
                freepartes(dados,4);
                break;
            case 'l':
            /*-----
            ---> O comando l tem como objetivo listar todos os contactos pela ordem em que foram introduzidos
            ------*/
                listar_contactos();
                freepartes(dados,1);
                break;
            case 'p':
            /*-----
            ----> O comando p permite procurar um contacto atraves do nome
            -@ Indicie 1 do vetor dados contem o nome do contacto que se quer procurar
            -----*/
                procura_nome(dados[1].par);
                freepartes(dados,2);
                break;
            case 'r':
            /*-----
            -----> O comando r permite apagar um contacto atraves do nome
            -@ Indicie 1 do vetor dados contem o nome do contacto que se quer remover
            -----*/
                remover_contacto(dados[1].par);
                freepartes(dados,2);
                break;
            case 'e':
            /*----
            -----> O comando e permite alterar o endereco do email de um contacto
            -@ Indicie 1 do vetor dados contem o nome do contacto que se quer alterar. 
            -@ Indicie 2 do vetor dados contem o novo endereco do email
            ----*/
                mudar_email(dados[1].par,dados[2].par);
                freepartes(dados,3);
                break;
            case 'c':
            /*----
            ----> O comando c permite contar o numero de ocorrencias de um dominio de email atraves do dominio
            -@ Indicie 1 do vetor dados contem o dominio de email
            ----*/
                ocorrencia_dominio(dados[1].par);
                freepartes(dados,2);
                break;
            case 'x':
            /*-----
            ----> O comando x permite terminar o programa e tambem permite libertar os dados existentes 
            ------*/
                free_sistema();
                freepartes(dados,1);
                return 0;
        }
    }
    return -1;
}

