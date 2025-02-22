#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filmes.h"
#include "utils.h"

void adicionarFilme(FILE *portfolio) {
    Filme *novoFilme = (Filme*)malloc(sizeof(Filme));
    if(novoFilme == NULL){
        printf("Erro ao alocar memória");
        return;
    }
    
    printf("Nome: ");
    scanf(" %[^\n]s", novoFilme->nome);
    printf("Duração: ");
    scanf(" %[^\n]s", novoFilme->duracao);
    printf("Gênero: ");
    scanf(" %[^\n]s", novoFilme->genero);
    printf("Ano de lançamento: ");
    scanf("%d", &novoFilme->ano);
    
    fprintf(portfolio, "%s | %s | %s | %d\n", novoFilme->nome, novoFilme->duracao, novoFilme->genero, novoFilme->ano);
    free(novoFilme);
    printf("Filme adicionado com sucesso!\n");
    limparBuffer();
}

void lerPortfolio(FILE *portfolio) {
    rewind(portfolio);
    char ch;
    while((ch = fgetc(portfolio)) != EOF) {
        putchar(ch);
    }
}

void filmeAssistido(FILE *portfolio) {
    char nomeFilme[50], linha[256];
    int encontrado = 0;
    
    printf("Nome do filme assistido: ");
    limparBuffer();
    scanf(" %[^\n]s", nomeFilme);

    rewind(portfolio);
    while(fgets(linha, sizeof(linha), portfolio)){
        if(strstr(linha, nomeFilme) != NULL){
            encontrado = 1;
            break;
        }
    }
    
    if(encontrado)
        printf("Filme encontrado e marcado como assistido!\n");
    else
        printf("Filme não encontrado.\n");
}
