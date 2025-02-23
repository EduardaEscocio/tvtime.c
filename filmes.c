#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "filmes.h"

bool validarAno(int ano) {
    return ano > 0 && ano < 2026;
}

void adicionarFilme(FILE *portfolio){

	if(!portfolio){
		printf("Error: Arquivo portfolio não está aberto. \n");
		return;
	}

	Filme *novoFilme = (Filme*)malloc(sizeof(Filme));
    if(!novoFilme){
        printf("Erro ao alocar memória");
        return;
    }

    printf("Nome: ");
    scanf(" %[^\n]", novoFilme->nome);
	
	int horas, minutos, segundos;
	do {
		printf("Duração (HH:MM:SS): ");
		scanf(" %[^\n]", novoFilme->duracao);
		getchar();
	} while (sscanf(novoFilme->duracao, "%d:%d:%d", &horas, &minutos, &segundos) != 3);
    
	printf("Gênero: ");
    scanf(" %[^\n]", novoFilme->genero);
	
    do {
        printf("Ano de lançamento: ");
		if (scanf("%d", &novoFilme->ano) != 1 || !validarAno(novoFilme->ano)){
			printf("Entrada inválida! Digite um número válido \n");
			while (getchar() != '\n');
		} 
		else
			break;
	} while (true);

    // Posiciona o cursor no final do arquivo
    fseek(portfolio, 0, SEEK_END);

    if (fprintf(portfolio, "%s|%s|%s|%d|\n", novoFilme->nome, novoFilme->duracao, novoFilme->genero, novoFilme->ano) < 0) {
        printf("Erro: Falha ao escrever no arquivo.\n");
    } else {
        printf("O filme foi adicionado com sucesso no catálogo!\n");
    }

	fflush(portfolio);
	free(novoFilme);
}

void lerPortfolio(FILE *portfolio){

	if(!portfolio){
		printf("Error: Arquivo portfolio não está aberto. \n");
		return;
	}

	char linha[256];
    rewind(portfolio); // Volta ao início do arquivo para garantir que ele seja lido desde o começo

	printf("\n--- Catálogo de Filmes ---\n");

    while (fgets(linha, sizeof(linha), portfolio) != NULL) {

        // Divide a linha em campos usando o delimitador "|"
        char *nome = strtok(linha, "|");
        char *duracao = strtok(NULL, "|");
        char *genero = strtok(NULL, "|");
        char *ano_str = strtok(NULL, "|");

        // Verifica se todos os campos foram lidos corretamente
        if (nome && duracao && genero && ano_str) {
            int ano = atoi(ano_str); // Converte o ano para inteiro
            printf("\nNome: %s\n", nome);
            printf("Duração: %s\n", duracao);
            printf("Gênero: %s\n", genero);
            printf("Ano de lançamento: %d\n", ano);
        } else {
            printf("Erro: Formato inválido no arquivo.\n");
        }
    }
    printf("\n--- Fim do Catálogo ---\n");
}

