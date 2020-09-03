:- use_module(library(clpfd)).

%-----------------------------------------------------------------------------
%                              MATRIZES
%-----------------------------------------------------------------------------
%-----------------------------------------------------------------------------
% mat_dimensoes(Mat, Num_Lins, Num_Cols)
%-----------------------------------------------------------------------------

mat_dimensoes(Mat, Num_Lins, Num_Cols) :-
    nth1(1, Mat, Linha1),
    length(Mat, Num_Lins),
    length(Linha1, Num_Cols).

%-----------------------------------------------------------------------------
% mat_ref(Mat, Pos, Cont): O conteudo da posicao Pos de Mat e' Cont
%-----------------------------------------------------------------------------

mat_ref(Mat, (L, C), Cont) :-
    nth1(L,Mat,Linha),
    nth1(C,Linha,Cont).

%-----------------------------------------------------------------------------
% mat_muda_posicao(Mat, Pos, Cont, N_Mat):
% N_Mat e' o resultado de substituir o conteudo da posicao Pos
% de Mat por Cont.
%-----------------------------------------------------------------------------

mat_muda_posicao(Mat, (L,C), Cont, N_Mat) :-
    nth1(L,Mat,Linha),
    mat_muda_linha(Linha,C,Cont, N_Linha),
    mat_muda_linha(Mat,L,N_Linha, N_Mat),!.

%-----------------------------------------------------------------------------
% mat_muda_posicoes(Mat, Lst_Posicoes, Lst_Cont, N_Mat):
% N_Mat e' o resultado de substituir o conteudo das posicoes de
% Lst_Posicoes de Mat pelo elemento correpondente de Lst_Cont.
%-----------------------------------------------------------------------------
mat_muda_posicoes(Mat, [], _, Mat) :- !.

mat_muda_posicoes(Mat, [Pos | R_Pos], [Cont | R_Cont], N_Mat) :-
    mat_muda_posicao(Mat, Pos, Cont, Temp),
    mat_muda_posicoes(Temp, R_Pos, R_Cont, N_Mat).

%-----------------------------------------------------------------------------
% mat_muda_linha(Mat, L, N_Linha_L, N_Mat):
% N_Mat e' o resultado de substituir a linha L de Mat
% por N_Linha_L.
%-----------------------------------------------------------------------------
mat_muda_linha([_|T], 1, N_Linha_L, [N_Linha_L|T]) :- !.

mat_muda_linha([H|T], L, N_Linha_L, [H|R]):-
    L > 0,
    NL is L-1,
    mat_muda_linha(T, NL, N_Linha_L, R), !.

%-----------------------------------------------------------------------------
% mat_muda_coluna(Mat, C, N_Coluna_C, N_Mat):
% N_Mat e' o resultado de substituir a coluna C de Mat
% por N_Coluna_C.
%-----------------------------------------------------------------------------
mat_muda_coluna(Mat, C, N_Coluna_C, N_Mat) :-
    length(Mat, Num_Lins),
    findall((L, C), between(1, Num_Lins, L), Posicoes_coluna),
    mat_muda_posicoes(Mat, Posicoes_coluna, N_Coluna_C, N_Mat).

%-----------------------------------------------------------------------------
% mat_transposta(Mat, Transp):
% Transp e' a transposta da matriz Mat
%-----------------------------------------------------------------------------
mat_transposta(Mat, Transp) :-
    transpose(Mat, Transp).

%-----------------------------------------------------------------------------
% mat_elementos_coluna(Mat, Col, Els):
% Els e' a coluna Col da matriz Mat
%-----------------------------------------------------------------------------
mat_elementos_coluna(Mat, Col, Els) :-
    mat_dimensoes(Mat, Num_Lins, _),
    findall(L, between(1, Num_Lins, L), Lst_Lins),
    mat_elementos_coluna(Mat, Col, Lst_Lins, Els).

mat_elementos_coluna(Mat, Col, Lst_Lins, Els) :-
    findall((L, Col), member(L, Lst_Lins), Posicoes_Col),
    findall(E, (member(Pos, Posicoes_Col), mat_ref(Mat, Pos, E)), Els).

%-----------------------------------------------------------------------------
%                escreve_Puzzle(Puz)
%-----------------------------------------------------------------------------
escreve_Puzzle(Puz) :-
    maplist(escreve_Linha, Puz).

escreve_Linha([]) :- nl, !.

escreve_Linha([P | R]) :-
    (var(P) -> write('- ')
            ;
     write(P), write(' ')),
     escreve_Linha(R).




