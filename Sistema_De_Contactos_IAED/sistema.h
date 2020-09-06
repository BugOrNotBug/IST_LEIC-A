#ifndef SISTEMA_H
#define SISTEMA_H

/*---
Esta funcao tem como objetivo inicializar as tabelas de dispersao 
---*/
void iniciar_sistema();
/*---
Esta funcao tem como objetivo verificar se o nome do novo contacto ja existe no sistema.
Se nao existe, entao insere o contacto e o dominio do email do novo contacto nas tabelas
---*/
void inserir_no_sistema(char *nome,char *email,char *telefone);
/*---
Esta funcao, utilizando a funcao procura_htnome, tem como objetivo encontrar o nome na tabela htnome
Recebe o nome do contacto que se quer procurar
---*/
void procura_nome(char *nome);
/*---
Esta funcao, utilizando a funcao remover_ht, tem  como objetivo remover um contacto e dominio do email do
contacto nas tabelas. Recebe o nome do contacto que se quer remover
---*/
void remover_contacto(char *nome);
/*---
Esta funcao tem como objetivo referir o numero de ocorrencias de um dominio de email
Recebe como argumento o dominio em se quer contar as ocorrencias
---*/
void ocorrencia_dominio(char *dominio);
/*---
Esta funcao utilizando a funcao free_tables liberta a memoria associada as tabelas
---*/
void free_sistema();


#endif