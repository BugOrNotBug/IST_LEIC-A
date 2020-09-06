#ifndef CONTACTO_H
#define CONTACTO_H

/*------
A estatura conexao contem os itens proprios de um contacto: o nome,o email e o telefone. Ainda contem a ordem em que
foi introduzido no sistema
---------*/
struct conexao {
    char *nome;
    char *email;
    char *telefone;
    int ordem;
};
/*------
O ponteiro para a estratura conexao
--------*/
typedef struct conexao* contacto;


/*-------
A estrutura domi contem o dominio de um email e o numero de ocorrencias deste dominio
--------*/
struct domi {
    char *dominio;
    int ocorrencia;
};
/*-------
O ponteiro para estrutura domi
--------*/
typedef struct domi* dominio;

/*------
Esta funcao permite criar um novo contacto com o nome, email e o telefone recebidos. Ainda coloca a ordem que foi
introduzido. Aloca se memoria para o contacto, nome, o email e numero de telefone. Devolve este mesmo contacto
--------*/
contacto novo_contacto(char *nome, char *email, char*telefone);
/*------
Esta funcao liberta a memoria associada ao contacto
-------*/
void freecontacto(contacto con);
/*------
Esta funcao permite obter o dominio de um email. O email pode ser dividido entre a parte local e o dominio 
separados pelo caracter @. Recebe um email de um contacto e devolve o dominio do email
--------*/
char *obter_dominio(char *email);
/*-------
Esta funcao escreve no terminal o nome, o email e o numero de telefone do contacto recebido
--------*/
void printf_contacto(contacto con);

#endif