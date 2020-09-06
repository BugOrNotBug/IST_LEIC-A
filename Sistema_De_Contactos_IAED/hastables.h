#ifndef HASTABLES_H
#define HASTABLES_H

/*Existem tres tabelas de dispersao:
-->htnome e uma tabela que guarda um contacto cuja chave e o nome do contacto
-->htordem e uma tabela que guarda um contacto cuja chave e a ordem do contacto
-->htdominio e uma tabela que guarda um dominio de um email cuja chave e este dominio
*/

/*-----------------|Inicializacao das tabelas de dispersao|------------------*/

/*As tres funcoes iniciam a respestiva tabela como tabela com num elementos*/
void iniciar_htnome(int num);
void iniciar_htordem(int num);
void iniciar_htdominio(int num);

/*-------------|Adicao nas tabelas|---------------------*/

/*Esta funcao adciona o contacto recebido na tabela htname*/
void inserir_htnome(contacto con);
/*Esta funcao adciona o contacto recebido na tabela htordem*/
void inserir_htordem(contacto con);
/*Esta funcao adciona o dominio recebido na tabela htdominio*/
void inserir_htdominio(dominio domi);

/*Esta funcao verifica se existe o dominio na tabela. Se nao existe, entao
coloca a ocorrencia do dominio igual a 1 e adciona o dominio na tabela*/
void verificar_inserir_dominio(char* d);

/*---------------|Expandir as tabelas|----------------------*/

/*Estas funcoes tem como objetivo duplicar o tamanho da respetiva 
tabela quando tem metade dos elementos*/
void expandir_htnome();
void expandir_htordem();
void expandir_htdominio();

/*--------------|Procura nas tabelas|---------------*/

/*Os caracteres recebidos nestas funcoes relacionam se com os comando da funcao main*/

/*Esta funcao procura o nome recebido na tabela e cumpre um certo objetivo conforme
o caracter recebido. Se o nome existir na tabela, entao devolve o indicie da tabela 
onde esta o nome, senao, devolve um numero negativo*/
int procura_htnome(char *nome,char car);

/*Esta funcao procura o dominio recebido na tabela e cumpre um certo objetivo
conforme o caracter recebido. Se o dominio existir na tabela, devolve o numero
de ocorrencias do dominio ,senao, devolve 0*/
int procura_htdominio(char *dominio,char car);


/*-------------|Outras funcoes|----------*/

/*Esta funcao lista ordenadamente os contactos inseridos na tabela htordem conforme
a sua ordem*/
void listar_contactos();

/*Esta funcao remove o contacto inserido na posicao i da tabela htnome. Seguidamente,
remove este contacto na tabela htordem e diminui a ocorrencia do dominio do email
do contacto, alterando a tabela htdominio*/
void remover_ht(int i);

/*Esta funcao tem como objetivo alterar o email de um contacto, alterando as tabelas.
 Recebe o nome do contacto em se querem fazer alteracoes e recebe o novo email*/
void mudar_email(char *nome,char *email);

/*Liberta memoria associada as tabelas*/
void free_tables();

#endif