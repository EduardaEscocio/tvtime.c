#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "users.h"
#include "utils.h"
//NAO FUNCIONA
int cadastroExiste(FILE *usuarios, char *login) {
    char linha[256];
    rewind(usuarios); // Volta ao início do arquivo
    while (fgets(linha, sizeof(linha), usuarios)) {
        char loginArquivo[50];
        sscanf(linha, "%[^|]", loginArquivo); // Extrai o login do arquivo
        if (strcmp(loginArquivo, login) == 0) {
            return 0; // Login já existe
        }
    }
    return 1; // Login não existe
}

//FUNCIONA MAS PRINTA MUITO
int loginValido(char *login) {
    for (int i = 0; i < strlen(login); i++) {
        if (isspace(login[i])) { // Se encontrar espaço, login é inválido
            return 0; // Retorna 0 para indicar que o login é inválido
        }
    }
    return 1; // Retorna 1 para indicar que o login é válido
}

void cadastro(FILE *usuarios) {
    // FILE *usuarios = fopen("usuarios.txt", "a+");
    User *novoUsuario = malloc(sizeof(User));
    char nome[50];
    char login[50];
    char senha[50];

    // Validação do login
    do {
        printf("Nome de usuário: ");
        scanf(" %[^\n]", login);
    } while (loginValido(login)==0 || cadastroExiste(usuarios, login)==0);

    strcpy(novoUsuario->login, login);

    printf("Nome: ");
    scanf(" %[^\n]", nome);
    strcpy(novoUsuario->nome, nome);

    printf("Senha: ");
    scanf(" %[^\n]", senha);
    strcpy(novoUsuario->senha, senha);

    rewind(usuarios);
    // Verifica se o arquivo está vazio para definir o admin
    if (fgetc(usuarios) == EOF) {
        novoUsuario->adminId = 1; // Primeiro usuário é admin
    } else {
        novoUsuario->adminId = 0; // Usuário comum
    }

    // Escreve o novo usuário no arquivo
    if(fprintf(usuarios, "%s|%s|%s|%d\n", novoUsuario->login, novoUsuario->nome, novoUsuario->senha, novoUsuario->adminId) < 0){
        printf("Falha ao escrever no banco de dados");
    }
    
    printf("%s|%s|%s|%d\n", novoUsuario->login, novoUsuario->nome, novoUsuario->senha, novoUsuario->adminId);
    printf("Usuário registrado com sucesso!\n");
    // fclose(usuarios);
}
char *login(FILE *usuarios) {
    char linha[256];
    char login_atual[50];
    char senha_atual[50];
    int encontrado = 0;

    printf("Digite seu login: ");
    scanf(" %[^\n]", login_atual);

    printf("Digite sua senha: ");
    scanf(" %[^\n]", senha_atual);

    rewind(usuarios); // Volta ao início do arquivo

    while (fgets(linha, sizeof(linha), usuarios)) {
        char nomeArquivo[50];
        char loginArquivo[50];
        char senhaArquivo[50];
        int adminId;
        
        // Extrai o nome, login, senha e adminId do arquivo
        if (sscanf(linha, " %[^|]|%[^|]|%[^|]|%d", loginArquivo, nomeArquivo, senhaArquivo, &adminId) == 4) {
            // Compara login e senha
            if (strcmp(loginArquivo, login_atual) == 0 && strcmp(senhaArquivo, senha_atual) == 0) {
                encontrado = 1;
                break;
            }
        }
    }

    if (encontrado) {
        printf("Login realizado com sucesso!\n");

        // Aloca memória dinamicamente para o login de retorno
        char *loginRetorno = malloc(50 * sizeof(char));
        if (loginRetorno == NULL) {
            printf("Erro ao alocar memória.\n");
            return NULL;
        }

        strcpy(loginRetorno, login_atual);
        return loginRetorno; // Retorna o ponteiro alocado dinamicamente
    } else {
        printf("Login ou senha incorretos! Tente novamente.\n");
        return NULL; // Retorna NULL em caso de falha
    }
}
int detectarAdm(char *login, FILE *usuarios){
    char linha[256];
    rewind(usuarios);

    while (fgets(linha, sizeof(linha), usuarios)) {
        char nomeArquivo[50];
        char loginArquivo[50];
        char senhaArquivo[50];
        int adminId;
        // Extrai o nome, login, senha e adminId do arquivo
        if (sscanf(linha, " %[^|]|%[^|]|%[^|]|%d", loginArquivo, nomeArquivo, senhaArquivo, &adminId) == 4) {
            // Compara login e senha
            if (strcmp(loginArquivo, login) == 0){
                return adminId;
            }
        }
    }
}

int converterParaInt(char *duracao){
    int horas, minutos; 
    sscanf(duracao, "%d:%d", &horas, &minutos);
    return horas * 60 + minutos;
}
void filmeAssistido(FILE *portfolio, FILE *estatisticas, char *login) {
    //Adicionar plataformas
    int encontrado = 0;
    char linha[256];
    char nomeFilme[50];
    char procuraFilme[50];
    char duracao[10];
    printf("Qual o nome do filme que você quer adicionar como assistido? ");
    limparBuffer();
    scanf(" %[^\n]s", nomeFilme); // de novo o %s

    rewind(portfolio); // Volta ao início do arquivo para garantir que ele seja lido desde o começo
    while(fgets(linha, sizeof(linha), portfolio)){
        if(strstr(linha, nomeFilme) != NULL){ //vê se o filme existe no portfolio
            sscanf(linha, "%[^|]| %[^|] |%[^|]|%*[^|]|", duracao); //pegar a duração do filme
            encontrado=1;//encontrado!
            break;
        }
    }
    if(encontrado >= 1){
        printf("Filme encontrado\n");
        int minutos = converterParaInt(duracao);//char para int
        Estatisticas stats;//cria a struct que armazena as estatisticas 
        rewind(estatisticas);
        while(fgets(linha, sizeof(linha), estatisticas)) {
            sscanf(linha, "%[^|]| %d %d", stats.login, &stats.horasTotais, &stats.minutosTotais);
            if(strcmp(stats.login, login) == 0) {
                stats.minutosTotais += minutos;
                stats.horasTotais += stats.minutosTotais / 60;
                stats.minutosTotais %= 60;
                break;
            }
        }
        fprintf(estatisticas, "%s | %d %d\n", login, stats.horasTotais, stats.minutosTotais);
    }
    else{
        printf("Filme não disponível no catálogo");
    }
    
}