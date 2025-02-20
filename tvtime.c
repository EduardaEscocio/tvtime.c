#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função para limpar o buffer do teclado
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
} 

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
    struct filme *ant;
    struct filme *prox;
}Filme;

typedef struct filmesAssistidos{
    Filme *filme;
}filmesAssistidos;

FILE *portfolio;
char ch;
int opcaoMenu = 9;
//COPIEI A FUNÇÃO DE ADD FILME AQUI, TEM QUE ARRUMAR
// void login(){
//     User * novoUsuario = (User*)malloc(sizeof(User));
//     if(novoFilme == NULL){
//         printf("Erro ao alocar memória");
//         return;
//     }
//     printf("Nome: ");
//     scanf(" %[^\n]", nomeFilmeAtual);
//     strcpy(novoFilme->nome, nomeFilmeAtual);
//     printf("Duração: ");
//     scanf(" %[^\n]", novoFilme->duracao);
//     printf("Gênero: ");
//     scanf(" %[^\n]", novoFilme->genero);
//     printf("Ano de lançamento: ");
//     scanf("%d", &novoFilme->ano);
//     FILE *portfolio = fopen("portfolio.txt", "a");
//     if(portfolio == NULL){
//         printf("Erro ao abrir o arquivo");
//         free(novoFilme);
//         return;
//     }
//     fprintf(portfolio, "%s | %s | %s | %d |\n", novoFilme->nome, novoFilme->duracao, novoFilme->genero, novoFilme->ano);
//     fclose(portfolio);
//     free(novoFilme);
//     printf("O filme foi adicionado com sucesso no catálogo!\n");
//     limparBuffer();

// }

int menuPrincipal(){
    printf("\033[0;36m");
    printf("Menu: \n");
    printf("[1] - Adicionar filme \n");
    printf("[2] - Ler portfolio de filmes \n");
    printf("[3] - Adicionar filme como assistido\n");
    printf("[4] - Login\n");
    printf("[5] - Cadastro\n");
    printf("[0] - Sair\n");
    printf("\033[0m");
    printf("Opção: ");
    
    scanf("%d", &opcaoMenu);
    return opcaoMenu;
}

int menuAdmin(){
    int opcaoMenuAdmin = 9;
    printf("\033[0;36m");
    printf("Menu: \n");
    printf("[1] - Adicionar novo filme \n");
    printf("[0] - Sair\n");
    printf("\033[0m");
    printf("Opção: ");
    
    scanf("%d", &opcaoMenu);
    return opcaoMenu;
}
//Função para adicionar um filme ao catálogo (ADMIN)
void adicionarFilme(){
    char nomeFilmeAtual[50];
    Filme * novoFilme = (Filme*)malloc(sizeof(Filme));
    if(novoFilme == NULL){
        printf("Erro ao alocar memória");
        return;
    }
    printf("Nome: ");
    scanf(" %[^\n]", nomeFilmeAtual);
    strcpy(novoFilme->nome, nomeFilmeAtual);
    printf("Duração: ");
    scanf(" %[^\n]", novoFilme->duracao);
    printf("Gênero: ");
    scanf(" %[^\n]", novoFilme->genero);
    printf("Ano de lançamento: ");
    scanf("%d", &novoFilme->ano);
    FILE *portfolio = fopen("portfolio.txt", "a");
    if(portfolio == NULL){
        printf("Erro ao abrir o arquivo");
        free(novoFilme);
        return;
    }
    fprintf(portfolio, "%s | %s | %s | %d |\n", novoFilme->nome, novoFilme->duracao, novoFilme->genero, novoFilme->ano);
    fclose(portfolio);
    free(novoFilme);
    printf("O filme foi adicionado com sucesso no catálogo!\n");
    limparBuffer();
}
// Função para ler o catálogo de filmes (QUALQUER USUÁRIO)
void lerPortfolio(){
    portfolio = fopen("portfolio.txt", "r");

      while(1){
        ch = fgetc(portfolio);
        if(ch == EOF){
          break;
        }
        printf("%c",ch);
      }
      fclose(portfolio);
      }

// ADICIONAR FILME COMO ASSISTIDO E NAS ESTATISTICAS (USUÁRIO COMUM)
void filmeAssistido(){
    char nomeFilme[50];
    char procuraFilme[50];
    printf("Qual o nome do filme que você quer adicionar como assistido? ");
    scanf(" %[^\n]", nomeFilme);
    portfolio = fopen("portfolio.txt", "r");
    //Função que percorre com 2 for para encontrar o filme e adicionar na lista de filmes assistidos, comparando letra a letra e atualizando a letra sempre.
    while(fgets(linha, sizeof(linha), arquivo)){

    }
        
        }
        fclose(portfolio);
        limparBuffer();
    

    //     strcpy(procuraFilme, fgets(procuraFilme, 50, portfolio));
    //     if(strcmp(nomeFilme, procuraFilme) == 0){
    //         printf("Filme encontrado e registrado");
    //         break;
    //     }
    //     if(ch == EOF){
    //         printf("Filme não disponível no catálogo");
    //         break;
    //     }
    // }
    // limparBuffer();
      
int main(){
while(opcaoMenu != 0){
        menuPrincipal();
    if(opcaoMenu == 1){
        adicionarFilme();
    }
    else if(opcaoMenu == 2){
        lerPortfolio();
    }
    else if(opcaoMenu == 3){
        filmeAssistido();
    }
    else if(opcaoMenu == 4){
        // login();
    }
}
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