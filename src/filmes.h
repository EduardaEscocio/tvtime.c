#ifndef FILMES_H
#define FILMES_H

#include <stdio.h>

typedef struct filme {
    char nome[50];
    char duracao[50];
    char genero[50];
    int ano;
} Filme;

void adicionarFilme(FILE *portfolio);
void lerPortfolio(FILE *portfolio);
void filmeAssistido(FILE *portfolio);

#endif
