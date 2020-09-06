#ifndef PARTES_H
#define PARTES_H

/*--------
Estrutura partes contem a string par que contera informacoes do input
--------*/
typedef struct {
    char *par;
}partes;

/*------
Esta funcao permite ler o input(strings) introduzido, separa lo em partes conforme o espaco vazio 
e guardar estas partes num vetor de tipo partes. Tambem aloca memoria para o vetor partes. 
O comando, nome, email e telefone sao separados por espaco vazio. Devolve este mesmo vetor.
-------*/
partes *lelinha();
/*------
Esta funcao permite libertar memoria associada com o vetor partes. Recebe o vetor e o numero de 
elementos neste vetor
--------*/
void freepartes(partes *p,int n); 

#endif