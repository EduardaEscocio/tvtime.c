#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
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
} Filme;

// typedef struct filmesAssistidos{
//     usuario
//     Filme *filme;
// }filmesAssistidos;

char ch;
int opcaoMenu = 9;
//N funfa
int loginValido(char *login){
    for(int i = 0; i < strlen(login); i++){
        if(isspace(login[i])==0){//tem espaços?
            printf("Login inválido! Tente novamente.\n");
            return 1;
            break;

        }
        else{
            return 0;
        }
    }
}


void cadastro(FILE *usuarios){
    char nome[50];
    char *login = malloc(50 *sizeof(char));
    char senha[50];
    int ch;
    //validação de dados de login e senha necessario;
    User * novoUsuario = (User*)malloc(sizeof(User));
    if(novoUsuario == NULL){
        printf("Erro ao alocar memória");
        return;
    }
    //SE CERTIFICAR DE QUE O USUÁRIO NÃO VAI TENTAR CADASTRAR COM UM LOGIN QUE JA EXISTE (GUSTAVO)
    do {
        printf("login: \n");
        scanf(" %[^\n]s", login);
    } while(loginValido(login)==1);
    
    strcpy(novoUsuario->login, login);
    printf("Nome: \n");
    scanf(" %[^\n]s", nome);
    strcpy(novoUsuario->nome, nome);
    printf("Senha: \n");
    scanf(" %[^\n]s", senha);
    strcpy(novoUsuario->senha, senha);
    if(usuarios == NULL){
        printf("Erro ao abrir o arquivo");
        free(novoUsuario);
        return;
    }
    if(ch = fgetc(usuarios) == EOF){
        //Se o arquivo estava vazio, então estamos adicionando o primeiro usuário, que é adm
        novoUsuario->adminId = 1;
    }
    fprintf(usuarios, "%s | %s | %s \n", novoUsuario->nome, novoUsuario->login, novoUsuario->senha);
    fclose(usuarios);
    free(novoUsuario);
    printf("O usuario foi registrado com sucesso!\n");
    limparBuffer();
}

void login(){
    //Essa função precisa buscar o usuário para logar e buscar suas estatísticas ou adicionar novos filmes assistidos;
    char login_atual[50];
    char senha_atual[50];
    printf("Digite seu login: \n");
    scanf("%[^\n]s", login_atual);
    printf("Digite sua senha: \n");
    scanf("%[^\n]s", senha_atual);
    //validar nome e senha quando encontrados
    //detectar se é adm ou não

}

int menuPrincipal(){
    printf("\033[0;36m");
    printf("Menu: \n");
    printf("[1] - Cadastro \n");
    printf("[2] - Login \n");
    printf("[3] - Ler portfolio de filmes\n");
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
    
    scanf("%d", &opcaoMenuAdmin);
    return opcaoMenuAdmin;
}

//Função para adicionar um filme ao catálogo (ADMIN)
void adicionarFilme(FILE *portfolio){
    Filme * novoFilme = (Filme*)malloc(sizeof(Filme));
    if(novoFilme == NULL){
        printf("Erro ao alocar memória");
        return;
    }
    printf("Nome: ");
    scanf(" %[^\n]s", novoFilme->nome);
    printf("Duração: ");
    scanf(" %[^\n]s", novoFilme->duracao); // dar um jeito de adicionar o : caso o usuário digite apenas numeros, formato ideal = HM:SmS
    printf("Gênero: ");
    scanf(" %[^\n]s", novoFilme->genero);
    printf("Ano de lançamento: ");
    scanf("%d", &novoFilme->ano);
    if(portfolio == NULL){
        printf("Erro ao abrir o arquivo");
        free(novoFilme);
        return;
    }
    fprintf(portfolio, "%s | %s | %s | %d |\n", novoFilme->nome, novoFilme->duracao, novoFilme->genero, novoFilme->ano);
    free(novoFilme);
    printf("O filme foi adicionado com sucesso no catálogo!\n");
    limparBuffer();
}

// Função para ler o catálogo de filmes (QUALQUER USUÁRIO)
void lerPortfolio(FILE *portfolio){
    rewind(portfolio); // Volta ao início do arquivo para garantir que ele seja lido desde o começo
    while(1){
        ch = fgetc(portfolio);
        if(ch == EOF){
            break;
        }
        printf("%c",ch);
    }
}

// ADICIONAR FILME COMO ASSISTIDO E NAS ESTATISTICAS (USUÁRIO COMUM) FUNCIONANDO COLOCAR PRA ADICONAR NUM ARQUIVO
// FAZER A SOMA DE MINUTOS
void filmeAssistido(FILE *portfolio){
    int encontrado = 0;
    char linha[256];
    char nomeFilme[50];
    char procuraFilme[50];
    printf("Qual o nome do filme que você quer adicionar como assistido? ");
    limparBuffer();
    scanf(" %[^\n]s", nomeFilme); // de novo o %s
    rewind(portfolio); // Volta ao início do arquivo para garantir que ele seja lido desde o começo
    while(fgets(linha, sizeof(linha), portfolio)){
        if(strstr(linha, nomeFilme) != NULL){
            encontrado+=1;
            break;
        }
    }
    if(encontrado >= 1){
        printf("Filme encontrado\n");
    }
}

int main(){
    FILE *usuarios = fopen("usuarios.txt", "a+");
    FILE *portfolio = fopen("portfolio.txt", "a+"); // Abre o arquivo para leitura e escrita
    if (portfolio == NULL) {
        printf("Erro ao abrir o arquivo portfolio.txt\n");
        return 1;
    }

    while(opcaoMenu != 0){
        menuPrincipal();
        if(opcaoMenu == 1){
            cadastro(usuarios);
        }
        // else if(opcaoMenu == 2){
        //     login();
        // }
        else if(opcaoMenu == 3){
            lerPortfolio(portfolio);
        }
        else if(opcaoMenu == 4){
            adicionarFilme(portfolio);
        }
    }
    fclose(portfolio); // Fecha o arquivo apenas no final do programa
    fclose(usuarios);
    return 0;
}