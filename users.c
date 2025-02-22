#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "users.h"
#include "utils.h"
//NAO FUNCIONA
int loginExiste(FILE *usuarios, char *login) {
    char linha[256];
    rewind(usuarios); // Volta ao início do arquivo
    while (fgets(linha, sizeof(linha), usuarios)) {
        char loginArquivo[50];
        scanf(linha, "%[^|]", loginArquivo); // Extrai o login do arquivo
        if (strcmp(loginArquivo, login) == 0) {
            return 1; // Login já existe
        }
    }
    return 0; // Login não existe
}
//FUNCIONA MAS PRINTA MUITO
int loginValido(char *login) {
    for (int i = 0; i < strlen(login); i++) {
        if (isspace(login[i])) { // Se encontrar espaço, login é inválido
            return 1; // Retorna 1 para indicar que o login é inválido
        }
    }
    return 0; // Retorna 0 para indicar que o login é válido
}

void cadastro(FILE *usuarios) {
    // FILE *usuarios = fopen("usuarios.txt", "a+");
    User *novoUsuario = malloc(sizeof(User));
    char nome[50];
    char login[50];
    char senha[50];

    // Validação do login
    do {
        printf("Login: ");
        scanf(" %[^\n]", login);
        if (loginValido(login)) {
            printf("Login inválido! O login não pode conter espaços.\n");
        } else if (loginExiste(usuarios, login)) {
            printf("Login já existe. Tente outro.\n");
        }
    } while (loginValido(login) || loginExiste(usuarios, login));

    strcpy(novoUsuario->login, login);

    printf("Nome: ");
    scanf(" %[^\n]", nome);
    strcpy(novoUsuario->nome, nome);

    printf("Senha: ");
    scanf(" %[^\n]", senha);
    strcpy(novoUsuario->senha, senha);

    // Verifica se o arquivo está vazio para definir o admin
    rewind(usuarios);
    if (fgetc(usuarios) == EOF) {
        novoUsuario->adminId = 1; // Primeiro usuário é admin
    } else {
        novoUsuario->adminId = 0; // Usuário comum
    }

    // Escreve o novo usuário no arquivo
    fprintf(usuarios, "%s|%s|%s|%d\n", novoUsuario->nome, novoUsuario->login, novoUsuario->senha, novoUsuario->adminId);
    printf("Usuário registrado com sucesso!\n");
    free(novoUsuario);
    // fclose(usuarios);
}

char* login(FILE *usuarios) {

    char linha[256];
    char login_atual[50];
    char senha_atual[50];
    int encontrado = 0;

    printf("Digite seu login: ");
    // limparBuffer(); // Limpa o buffer do teclado
    scanf(" %[^\n]", login_atual);

    printf("Digite sua senha: ");
    // limparBuffer(); // Limpa o buffer do teclado
    scanf(" %[^\n]", senha_atual);
    rewind(usuarios); // Volta ao início do arquivo
    
    while (fgets(linha, sizeof(linha), usuarios)) {
        char nomeArquivo[50];
        char loginArquivo[50];
        char senhaArquivo[50];
        int adminId;

        // Extrai o nome, login, senha e adminId do arquivo
        
        if (sscanf(linha, "%[^|]| %[^|] | %[^|] %d", nomeArquivo, loginArquivo, senhaArquivo, &adminId) == 4) {
            // Compara login e senha
            if (strcmp(loginArquivo, login_atual) == 0 && strcmp(senhaArquivo, senha_atual) == 0) {
                encontrado = 1;
                int adminIdUser = adminId;
                break;
            }
        }
    }
    
    if (encontrado) {
        printf("Login realizado com sucesso!\n");

        // Retorna o login do usuário (aloca memória para o retorno)
        char *loginRetorno = malloc(50 * sizeof(char));
        if (loginRetorno == NULL) {
            printf("Erro ao alocar memória.\n");
            return NULL;
        }
        
        strcpy(loginRetorno, login_atual);
        return loginRetorno; // Usar para estatísticas
    } else {
        printf("Login ou senha incorretos! Tente novamente.\n");
        return NULL; // Retorna NULL em caso de falha
    }
}

int converterParaInt(char *duracao){
    int horas, minutos; 
    sscanf(duracao, "%d:%d", &horas, &minutos);
    return horas * 60 + minutos;
}
void filmeAssistido(FILE *portfolio, FILE *estatisticas, char *login) {
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