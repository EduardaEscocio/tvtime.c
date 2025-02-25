#ifndef FILMES_H
#define FILMES_H

#include <stdio.h>
#define NAME_LENGTH 50
#define DURACAO_LENGTH 50
#define GENERO_LENGTH 50


typedef struct filme {
    char nome[NAME_LENGTH];
    char duracao[DURACAO_LENGTH];
    char genero[GENERO_LENGTH];
    int ano;
    struct filme *prox;   
}Filme;

void adicionarFilme(FILE *portfolio);
void lerPortfolio(FILE *portfolio);

#endif
