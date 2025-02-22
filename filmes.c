#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filmes.h"
#include "utils.h"
char ch;

void adicionarFilme(FILE *portfolio){
    Filme * novoFilme = (Filme*)malloc(sizeof(Filme));
    if(novoFilme == NULL){
        printf("Erro ao alocar memória");
        return;
    }
    printf("Nome: ");
    scanf(" %[^\n]s", novoFilme->nome);
    printf("Duração: ");
    //Validar para adicionar apenas numeros;
    scanf(" %[^\n]s", novoFilme->duracao); // dar um jeito de adicionar o : caso o usuário digite apenas numeros, formato ideal = HM:SmS
    printf("Gênero: ");
    scanf(" %[^\n]s", novoFilme->genero);
    printf("Ano de lançamento: ");
    scanf("%d", &novoFilme->ano);
    if(portfolio == NULL){
        printf("Erro ao abrir o arquivo");
        free(novoFilme);
        return;
    }
    fprintf(portfolio, "%s | %s | %s | %d |\n", novoFilme->nome, novoFilme->duracao, novoFilme->genero, novoFilme->ano);
    free(novoFilme);
    printf("O filme foi adicionado com sucesso no catálogo!\n");
    limparBuffer();
}

void lerPortfolio(FILE *portfolio){
    rewind(portfolio); // Volta ao início do arquivo para garantir que ele seja lido desde o começo
    while(1){
        ch = fgetc(portfolio);
        if(ch == EOF){
            break;
        }
        printf("%c",ch);
    }
}

