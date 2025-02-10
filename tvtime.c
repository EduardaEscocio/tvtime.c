#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct usuario{
    char login[50];
    char senha[50];
    char nome[50];
    int adminId; // 0 - comun - 1 admin
} User;

typedef struct filme{
    char nome[50];
    char duracao[50];
    char genero[50];
    int ano;
}Filme;

FILE *portfolio;
char ch;
char adicionarFilme(){
    char nomeFilmeAtual[50];
    Filme * novoFilme = (Filme*)malloc(sizeof(Filme));
    printf("Nome: ");
    scanf(" %s", nomeFilmeAtual);
    strcpy(novoFilme->nome, nomeFilmeAtual);
    // printf("Duração: ");
    // scanf(" %s", novoFilme->duracao);
    // printf("Gênero: ");
    // scanf("%s", novoFilme->genero);
    // printf("Ano de lançamento: ");
    // scanf("%d", &novoFilme->ano);
    // portfolio = fopen("portfolio.txt", "w");
    while( (ch = getchar()) != EOF) {
        putc(ch,portfolio);
      }
      fclose(portfolio);
}

char lerPortfolio(){
    portfolio = fopen("portfolio.txt", "r");

      while((ch = getc(portfolio) != EOF))
        printf("%c",ch);
        
      fclose(portfolio);
      }

int main(){
    adicionarFilme();
    lerPortfolio();
}

// TV Time
// O usuário pode fazer as seguintes funcionalidades:
// 1) Cadastro e Login: Os dados requisitados para o usuário devem ser pelo
// menos um login e uma senha, mas podem ser requisitadas outras
// informações adicionais. Ex:
// Cadastro:
// Login: rafaelivo
// Senha: *****
// Nome: Rafael
// 2) Cadastro de filmes: Um usuário especial (administrador) pode cadastrar filmes novos. Cada filme deve conter
// diversas informações, mas o mínimo deve ser: nome, tempo de duração, gênero. Ex:
// Cadastro de filme:
// Nome: The Matrix
// Duração: 2:16
// Gênero: Ficcção científica
// Ano de lançamento: 1999
// 3) Assistiu filme: Um usuário comum pode inserir que assistiu um dos filmes cadastrado na aplicação. Ex:
// Eu assisti o filme:
// Nome: Esqueceram de Mim
// Onde: Netflix
// Quando: 25/12/2024
// 4) Listar meus filmes assistidos: Um usuário comum pode exibir todos os filmes que ele cadastrou. Ex:
// Filmes que assisti:
// Esqueceram de Mim (Ano de lançamento: 1990, Duração: 1h43min, Assistido: 25/12/2024 em Netflix)
// Homem de Ferro (Ano de lançamento: 2008, Duração: 2h6min, Assistido: 25/01/2025 em Disney+)
// The Matrix (Ano de lançamento: 1999, Duração: 2h16min, Assistido: 01/02/2025 em HBO Max)
// 5) Estatísticas: O usuário pode visualizar estatísticas sobre os filmes que assistiu. Uma delas deve ser o tempo total dos
// filmes assistidos