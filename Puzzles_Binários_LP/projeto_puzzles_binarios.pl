%----------------------------NOME------------------------------------------

%     Numero: 92546          Nome:Rita Teresa Marmelo Castro Oliveira

%--------------------------------------------------------------------------


%--------------------------codigo_comum-----------------------------------------------------------------------------------------

:- consult(codigo_comum).


%--------------------------Representacao de posicoes e puzzle-----------------------------------------------------------------------------

% Posicao---> representada por um par (L,C), em que L e a linha e C e a coluna
% Puzzle----> Dimensao N, uma matriz, e representado por uma lista de N lista (cada uma representa uma linha do puzzle) de N elementos
% Elementos-> variavel se a posicao correspondente nao estiver preenchida
%             um valor (0 ou 1) se a posicao correspondente estiver preenchida

%-------------------------predicados necessarios------------------------------------------------------------------------------------------

junta([],L,L).
junta([P|R],L1,[P|L2]):-
    junta(R,L1,L2).

%-------
% conta_variaveis(List,Cont): conta quantas variaveis existem numa lista. List e a lista e Cont e o numero de variaveis na lista
%-------

conta_variaveis(List,Conta):-
    include(var,List,L_var),
    length(L_var,Conta).

%------
% conta_zeros_uns(Conta_0,Conta_1,List): Este predicado conta quantos zeros e uns existem numa lista.
% List e a lista , Conta_0 e numero de zeros que existem na lista e Conta_1 e numero de uns que existem na lista
%------
conta_zeros_uns(Conta_0,Conta_1,List):-
    include(zero,List,Lis_zero),
    length(Lis_zero,Conta_0),
    include(um,List,Lis_um),
    length(Lis_um,Conta_1).

%------
% zero(E): verifica se o elemento E e zero.
%------
zero(E):-
    E==0.
%------
% um(E): verifica se o elemento E e um.
%------
um(E):-
    E==1.


%-------------------------predicados para a inicializao de puzzles---------------------------------------------------------------------


%------------------aplica_R1_triplo/2-----------------------------------------------
%             aplica_R1_triplo(Triplo,N_Triplo)
% descricao: este predicado permite aplicar a regra 1 num triplo.
% Triplo e uma lista de 3 elementos,cujos elementos sao 0,1, ou uma variavel
% N_Triplo e a lista resultante de aplicar a regra 1 ao Triplo
% REGRA 1 --> Nao existem tres zeros ou tres uns seguidos em nenhuma linha ou coluna 
%-----------------------------------------------------------------------------------


aplica_R1_triplo(Triplo,N_Triplo):-
    conta_variaveis(Triplo,Num_var),
    (Num_var=:=0,!,verificar_R1(Triplo,N_Triplo)
        ;
     Num_var=:=1,!, apli_R1_triplo_aux(Triplo,N_Triplo)
        ;
     Num_var>1,N_Triplo=Triplo).

%-------
% verificar_R1(Triplo,N_Triplo): este predicado verifica se o Triplo tem tres zeros ou tres uns. Se nao tem, devolve o Triplo
% com nome N_Triplo, ou seja se nao estiver a violar a regra 1
% O Triplo nao tem variaveis. Se houver dois elementos com mesmo numero binario, outro elemento tem de ter um numero binario diferente
%-------

verificar_R1(Triplo,N_Triplo):-
    conta_zeros_uns(Cont0,Cont1,Triplo),
    (Cont0=:=2,!,N_Triplo=Triplo
        ;
     Cont1=:=2,N_Triplo=Triplo).

%-------
% apli_R1_triplo_aux(Triplo,N_Triplo): Caso no triplo (Triplo) se dois elementos forem iguais e existir uma variaval, este predicado
% permite substituir a variavel por outro numero binario, transformando o triplo (N_Triplo), caso contrario, devolve o triplo
%-------

apli_R1_triplo_aux(Triplo,N_Triplo):-
    conta_zeros_uns(Cont0,Cont1,Triplo),
    (Cont0=:=2,!,preencher_variavel(Triplo,1,N_Triplo)
        ;
     Cont1=:=2,!,preencher_variavel(Triplo,0,N_Triplo)
        ;
     Cont0=:=1,Cont1=:=1,N_Triplo=Triplo).

%-----
% preencher_variavel(Triplo,Bin,N_Triplo): se existir uma variavel no Triplo, e substituida pelo valor Bin. N_Triplo e o triplo resultante
% do predicado
%-----

preencher_variavel(Triplo,Bin,N_Triplo):-
    preencher_variavel(Triplo,Bin,N_Triplo,[]).

preencher_variavel([],_,Aux,Aux).

preencher_variavel([P|R],Bin,N_Triplo,Aux):-
    (var(P),!,junta(Aux,[Bin],N_Aux),preencher_variavel(R,Bin,N_Triplo,N_Aux)
        ;
    nonvar(P), junta(Aux,[P],N_Aux),preencher_variavel(R,Bin,N_Triplo,N_Aux)).  

%------------------aplica_R1_fila_aux/2---------------------------------------------
%             aplica_R1_fila_aux(Fila,N_Fila)
% descricao: este predicado permite aplicar a regra 1 a cada sub fila de 3 elementos
% Fila e uma lista de um dado numero de elementos (0,1,variavel)
% N_Fila e a lista resultante de aplicar a regra 1 a Fila
%----------------------------------------------------------------------------------

aplica_R1_fila_aux([A,B,C],N_Fila):-
    aplica_R1_triplo([A,B,C],N_Fila).

aplica_R1_fila_aux([A,B,C|R],N_Fila):-
    aplica_R1_triplo([A,B,C],[N_A,N_B,N_C]),
    aplica_R1_fila_aux([N_B,N_C|R],Temp),
    N_Fila=[N_A|Temp].


%------------------aplica_R1_fila/2----------------------------------------
%             aplica_R1_fila(Fila,N_Fila)
% descricao: este predicado permite aplicar repetidamente a regra 1
% (aplica_R1_fila_aux) a uma fila de um puzzle (coluna ou linha) ate que 
% nao sejam prenchidas novas posicoes
% Fila e uma lista de um dado numero de elementos (0,1,variavel)
% N_Fila e a lista resultante de aplicar a regra 1 a Fila
%----------------------------------------------------------------------------

aplica_R1_fila(Fila,N_Fila):-
    aplica_R1_fila_aux(Fila,Temp),
    (Fila==Temp, N_Fila=Temp
        ;
     aplica_R1_fila(Temp,N_Fila)).


%------------------aplica_R2_fila/2------------------------------------------
%             aplica_R2_fila(Fila,N_Fila)
% descricao: este predicado permite aplicar a regra 2 a uma fila de um puzzle
% (coluna ou linha)
% Fila e uma lista de um dado numero de elementos (0,1,variavel)
% N_Fila e a lista resultante de aplicar a regra 2 a Fila
% REGRA 2 ---> Todas as linhas e colunas tem o mesmo numero de zeros e uns.
% Este numero (N) sera metade da dimensao do puzzle.
%-----------------------------------------------------------------------------

%------
% N e metade do numero de elementos da Fila. Compri e o numero de elementos da Fila
%------

aplica_R2_fila(Fila,N_Fila):-
    conta_zeros_uns(Num_0,Num_1,Fila),
    length(Fila,Compri),
    N is Compri//2,
    ( Num_0=:=N,!,apli_R2_aux(Fila,N_Fila,1)
        ;
     Num_1=:=N,!,apli_R2_aux(Fila,N_Fila,0)
        ;
     Num_0<N, Num_1<N ,N_Fila=Fila).

%-------
% apli_R2_aux(Fila,N_Fila,Bin): Quando a fila tem N de um numero binario(0 ou 1), as posicoes vazias(que contem variavel) da fila tem de ser 
% preenchida pelo outro numero binario. 
% Fila e uma lista(fila) com N de um numero binario.
% N_Fila e uma lista resultante de aplicar o predicado
% Bin e o numero binario a preencher
%-------

apli_R2_aux(Fila,N_Fila,Bin):-
    apli_R2_aux(Fila,N_Fila,[],Bin).

apli_R2_aux([],Aux,Aux,_).

apli_R2_aux([P|R],N_Fila,Aux,Bin):-
   (var(P),!, junta(Aux,[Bin],N_Aux), apli_R2_aux(R,N_Fila,N_Aux,Bin)
        ;
    nonvar(P), junta(Aux,[P],N_Aux),apli_R2_aux(R,N_Fila,N_Aux,Bin)).



%------------------aplica_R1_R2_fila/2-------------------------------------------------
%             aplica_R1_R2_fila(Fila,N_Fila)
% descricao: este predicado permite aplicar a regra 1 e a regra 2, seguidamente, a uma 
% fila de um puzzle (coluna ou linha)
% Fila e uma lista de um dado numero de elementos (0,1,variavel)
% N_Fila e a lista resultante de aplicar a regra 1 e a regra 2 a Fila por esta ordem
%-------------------------------------------------------------------------------------

aplica_R1_R2_fila(Fila,N_Fila):-
    aplica_R1_fila(Fila,Tem_Fila),!,
    aplica_R2_fila(Tem_Fila,N_Fila).


%------------------aplica_R1_R2_puzzle/2-----------------------------------------------------
%             aplica_R1_R2_puzzle(Puzzle,N_Puzzle)
% descricao: este predicado permite aplicar a regra 1 e regra2 ao uma puzzle (linha e coluna)
% Puz e um puzzle de dimensao par.
% N_Puz e o puzzle resultante de aplica_R1_R2_fila as linhas e as colunas por esta ordem
%-------------------------------------------------------------------------------------------

aplica_R1_R2_puzzle(Puz,N_Puz):-
    aplica_R1_R2_linha(Puz,Tem_Puz),
    mat_transposta(Tem_Puz,Transposta),
    aplica_R1_R2_linha(Transposta,N_Transposta),
    mat_transposta(N_Transposta,N_Puz).

%------
% aplica_R1_R2_linha(Puz,N_Puz): este predicado aplica a regra 1 e a regra 2 a cada linha do puzzle(Puz), utilizando o predicado
% aplica_R1_R2_fila.
% N_Puz e o puzzle resultante do predicado
%------
aplica_R1_R2_linha(Puz,N_Puz):-
    aplica_R1_R2_linha(Puz,N_Puz,1,Puz).

aplica_R1_R2_linha(Aux,Aux,_,[]).

aplica_R1_R2_linha(Puz,N_Puz,L,[P|R]):-
    aplica_R1_R2_fila(P,N_Linha_L),
    % Verifica se se alterou a linha. Se alterou, muda o puzzle, senao passa se para a proxima linha
    (P\==N_Linha_L,!, mat_muda_linha(Puz, L, N_Linha_L, Aux),L_N is L+1,aplica_R1_R2_linha(Aux,N_Puz,L_N,R)
        ;
     P==N_Linha_L, Aux=Puz,L_N is L+1,aplica_R1_R2_linha(Aux,N_Puz,L_N,R)).


%------------------inicializa/2------------------------------------------------------------
%             inicializa(Puz,N_Puz)
% descricao: este predicado permite aplicar a regra 1 e a regra 2 a linha e a coluna do puzzle
% ate nao serem preenchidas novas posicoes
% Puz e uma puzzle de dimensao par.
% N_Puz e puzzle resultante de inicializar o puzzle Puz
%-------------------------------------------------------------------------------------------

inicializa(Puz,N_Puz):-
    aplica_R1_R2_puzzle(Puz,Puz_Temp),
    (Puz==Puz_Temp,N_Puz=Puz_Temp;
    inicializa(Puz_Temp,N_Puz)).

%-------------------------predicados para a verificacao da regra 3--------------------------------------------------------------------

%------------------verifica_R3/1---------------------------------------------------
%             verifica_R3(Puz)
% descricao: este predicado permite aplicar a regra 3 a linha e a coluna do puzzle
% Puz e um puzzle de dimensao par.
% REGRA 3 ---> Nao existem linhas nem colunas repetidas
%-----------------------------------------------------------------------------------

verifica_R3(Puz):-
    mat_dimensoes(Puz,Num_Linhas, Num_Colunas),
    verificar_linhas(Puz,Num_Linhas),!,                    
    verificar_colunas(Puz,Num_Colunas).

%-------
% verificar_linhas(Puz,Num_Linhas): verifica se a regra 3 nas linhas do puzzle(Puz). Num_Linhas e o numero da linha no puzzle
%-------
verificar_linhas(_,1).

verificar_linhas([P|R],Num_Linhas):-
    conta_variaveis(P,N_vars), % uma linha com variaveis nunca e igual a outra
    (N_vars=:=0,!,verificar_linhas_aux(P,R), N_Num_Linhas is Num_Linhas-1,verificar_linhas(R,N_Num_Linhas)
        ;
    N_vars=\=0, N_Num_Linhas is Num_Linhas-1,verificar_linhas(R,N_Num_Linhas)).
%-------
% verificar_linhas_aux(Linha,Segui): este predicado compara a linha (Linha) com as linhas seguintes no puzzle (Segui)
%-------
verificar_linhas_aux(_,[]).

verificar_linhas_aux(Linha,[P|R]):-
    conta_variaveis(P,N_vars), % uma linha com variaveis nunca e igual a outra
    (N_vars=:=0,!,Linha\==P, verificar_linhas_aux(Linha,R)
        ;
     N_vars=\=0, verificar_linhas_aux(Linha,R)).



%-------
% verificar_colunas(Puz,Num): verifica se a regra 3 nas colunas do puzzle(Puz). Num_Colunas e o numero das colunas no puzzle
%-------
verificar_colunas(Puz,Num_Colunas):-
    verificar_colunas(Puz,Num_Colunas,1).

verificar_colunas(_,Num_Colunas,Num_Colunas).

verificar_colunas(Puz,Num_Colunas,C):-
    mat_elementos_coluna(Puz, C, Elem),
    conta_variaveis(Elem,N_vars) ,% uma coluna com variaveis nunca e igual a outra
    (N_vars=:=0,!, verificar_colunas_aux(Puz,Num_Colunas,C,Elem), N_C is C+1,verificar_colunas(Puz,Num_Colunas,N_C)
        ;
    N_vars=\=0, N_C is C+1,verificar_colunas(Puz,Num_Colunas,N_C)).
%-------
% verificar_colunas_aux(Puz,Num_Colunas,C,Elem): este predicado compara a coluna (Elem) com as colunas seguintes no puzzle(Puz).
% C e o numero da coluna Elem e Num_Colunas e numero de colunas existentes no puzzle
%-------
verificar_colunas_aux(_,C,C,_).

verificar_colunas_aux(Puz,Num_Colunas,C,Elem):-
    mat_elementos_coluna(Puz, Num_Colunas, Colu),
    conta_variaveis(Colu,N_vars),
    (N_vars=:=0,!, Colu \==Elem , N_Num_Colunas is Num_Colunas-1, verificar_colunas_aux(Puz,N_Num_Colunas,C,Elem)
        ;
    N_vars=\=0, N_Num_Colunas is Num_Colunas-1, verificar_colunas_aux(Puz,N_Num_Colunas,C,Elem)).


%-------------------------predicados para propagacao de mudancas---------------------------------------------------------------

%------------------propaga_posicoes/2----------------------------------------------
%               propaga_posicoes(Posicao,Puz,N_Puz)
% descricao: Posicao e uma lista de posicoes, Puz e um puzzle e N_Puz e um puzzle 
% resultante de propagar, recursivamente, as posicoes de Posicoes
%-----------------------------------------------------------------------------------

propaga_posicoes([],N_Puz,N_Puz).

propaga_posicoes([P|R],Puz,N_Puz):-
    P=(L,C), % Linha L e Coluna C
    % Calcula se a dimensao do puzzle
    mat_dimensoes(Puz, Dim, _),
%--------aplica se a linha L do puzzle a regra 1 e 2---------
    mat_elementos_linha(Puz,L,Linha),
    aplica_R1_R2_fila(Linha,N_Linha),
    mat_muda_linha(Puz,L,N_Linha,Tem_Puz_1),
%--------aplica se a linha C do puzzle a regra 1 e 2---------
    mat_elementos_coluna(Tem_Puz_1,C,Coluna),
    aplica_R1_R2_fila(Coluna,N_Coluna),
    mat_muda_coluna(Tem_Puz_1,C,N_Coluna,Tem_Puz_2),
%--------compara se o puzzle inicial (Puz) e o puzzle transformado(Tem_Puz_2)-------
    comparacao(Puz,Tem_Puz_2,Dim,Posi),
    junta(Posi,R,L_Posicoes),
    propaga_posicoes(L_Posicoes,Tem_Puz_2,N_Puz).

%----
% mat_elementos_linha(Puz,L,Els): obtem se a linha L do puzzle Puz
%----

mat_elementos_linha(Puz,L,Els):-
    nth1(L,Puz,Els).
   
%------
% comparacao(Matr1,Matr2,Dim,Posicoes): comparam se duas matrizes da mesma dimensao e obtem se as posicoes em que se diferenciam
% Matr1,Matr2 sao as matrizes, Dim e dimensao das matrizes e Posicoes e a lista
%------
comparacao(Matr1,Matr2,Dim,Posicoes):-
    comparacao(Matr1,Matr2,(1,1),Dim,[],Posicoes). % este predicado incluiu a posicao onde se estao a comparar as matrizes - (L,C)

comparacao(_,_,(L,_),Dim,Aux,Aux):-
    L is Dim+1.

comparacao(Matr1,Matr2,(L,C),Dim,Aux,Posicoes):-
    mat_ref(Matr1, (L,C), Cont1),
    mat_ref(Matr2, (L,C), Cont2),
    (C=\=Dim,!,N_C is C+1 ,(Cont1==Cont2,!,comparacao(Matr1,Matr2,(L,N_C),Dim,Aux,Posicoes);
                           Cont1\==Cont2,nonvar(Cont2),junta(Aux,[(L,C)],N_Aux),comparacao(Matr1,Matr2,(L,N_C),Dim,N_Aux,Posicoes);
                           Cont1\==Cont2,var(Cont2),comparacao(Matr1,Matr2,(L,N_C),Dim,Aux,Posicoes));
        
    C=:=Dim,!,N_L is L+1 ,( Cont1==Cont2,!,comparacao(Matr1,Matr2,(N_L,1),Dim,Aux,Posicoes);
                           Cont1\==Cont2,nonvar(Cont2),junta(Aux,[(L,C)],N_Aux),comparacao(Matr1,Matr2,(N_L,1),Dim,N_Aux,Posicoes);
                           Cont1\==Cont2,var(Cont2),comparacao(Matr1,Matr2,(N_L,1),Dim,Aux,Posicoes))).





%-------------------------------predicado para resolver o puzzle-------------------------------------------------------------------------

%------------------resolve/2---------------------------------------------------------
%               resolve(Puz,Sol)
% descricao: com este predicado obtem se um puzzle (Sol) que e a solucao do puzzle Puz
%-------------------------------------------------------------------------------------

resolve(Puz,Sol):-
    inicializa(Puz,N_Puz),!,
    resolve_aux(N_Puz,Sol).

%------
% resolve_aux(Puz,Sol): este predicado tem como objetivo preencher as posicoes que restaram apos a inicializao do puzzle
% Puz e o puzzle e Sol e a solucao do puzzle. Aplica se este predicado ate nao haver posicoes vazias (sem variaveis)
%------
resolve_aux(Puz,Sol):-
    mat_dimensoes(Puz,Dim,_),
    variaveis_puzzle(Puz,Dim,Posi,Num_var),
    (Num_var=:=0,!,Sol=Puz
        ;
     Num_var=\=0,Posi=[P|_],teste_propagar([P],Puz,N_Puz),resolve_aux(N_Puz,Sol)).
     

%-------
% teste_propagar(Posicao,Puz,N_Puz):-este predicado tem como objetivo testar a posicao com valor 0 ou 1 e propagar esta mudanca
% a linha L e a coluna C, aplicando a regra 1 e a regra 2. No final verifica se se nao se viola a regra 3, devolve o puzzle transformado.
% Posicao e a lista com uma posicao do puzzle, Puz e o puzzle e N_Puz e o puzzle resultante
%-------
teste_propagar([(L,C)],Puz,N_Puz):-
    mat_muda_posicao(Puz, (L,C), 0, Tem_Puz_1),
    propaga_posicoes([(L,C)],Tem_Puz_1,Tem_Puz_2),
    verifica_R3(Tem_Puz_2),
    N_Puz=Tem_Puz_2.

teste_propagar([(L,C)],Puz,N_Puz):-
    mat_muda_posicao(Puz, (L,C), 1, Tem_Puz_1),
    propaga_posicoes([(L,C)],Tem_Puz_1,Tem_Puz_2),
    verifica_R3(Tem_Puz_2),
    N_Puz=Tem_Puz_2.


%------
% variaveis_puzzle(Puz,Dim,Posi,Num_var): este predicado tem como objetivo obter uma lista de posicoes onde existem variaveis e 
% tambem o numero de variaveis que existem no puzzle
% Puz e o puzzle, Dim e a dimensao do puzzle, Posi e a lista e Num_var e o numero de variaveis
%------
variaveis_puzzle(Puz,Dim,Posi,Num_var):-
    variaveis_puzzle(Puz,Dim,(1,1),Posi,[],Num_var,0).

variaveis_puzzle(_,Dim,(L,_),Aux,Aux,N,N):-
    L is Dim+1.

variaveis_puzzle(Puz,Dim,(L,C),Posi,Aux,Num_var,N):-
    mat_ref(Puz, (L,C), Cont),
    (C=\=Dim ,!,N_C is C+1 ,(var(Cont),!,N_N is N+1 , junta(Aux,[(L,C)],N_Aux),variaveis_puzzle(Puz,Dim,(L,N_C),Posi,N_Aux,Num_var,N_N);
                            nonvar(Cont), variaveis_puzzle(Puz,Dim,(L,N_C),Posi,Aux,Num_var,N));
        
    C=:=Dim,N_L is L+1 ,(var(Cont),!,N_N is N+1 ,junta(Aux,[(L,C)],N_Aux),variaveis_puzzle(Puz,Dim,(N_L,1),Posi,N_Aux,Num_var,N_N);
                         nonvar(Cont),variaveis_puzzle(Puz,Dim,(N_L,1),Posi,Aux,Num_var,N))).

















    


    


        


  






    
    

             
             
    

    
            


    