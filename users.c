#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "users.h"

int cadastroExiste(FILE *usuarios, char *login) {
    
	if(!usuarios){
		printf("Erro: Arquivo de usuários não está aberto. \n");
		return -1;
	}

	if(!login){
		printf("Usuário Login não encontrado!");
		return -2;
	}

	char linha[256];
    rewind(usuarios);
    
	while (fgets(linha, sizeof(linha), usuarios) != NULL) {
		char *loginUsuario = strtok(linha, "|");

		if(loginUsuario && strcmp(loginUsuario, login) == 0){
			return 1;
		}
	}
	return 0;
}

int loginValido(char *login) {

	if(!login){
		printf("Login inválido!");
		return 0;
	}
	
	size_t tamanho = strlen(login);

    // Verifica cada caractere do login
    for (size_t i = 0; i < tamanho; i++) {
        if (isspace((unsigned char)login[i])) {
            return 0; // Retorna 0 para indicar que o login é inválido
        }
    }
    return 1; // Retorna 1 para indicar que o login é válido
}

void cadastro(FILE *usuarios) {

	if(!usuarios){
        printf("Erro: Arquivo de usuários não está aberto.\n");
        return;
	}

    User *novoUsuario = malloc(sizeof(User));
    if (!novoUsuario) {
        printf("Error, Alocation Memory fault.\n");
        return;
    } 

	char nome[NAME_LENGHT];
    char login[LOGIN_LENGHT];
    char senha[PASSWORD_LENGHT];

    // Validação do login
    do {
        printf("Nome de usuário: ");
        scanf(" %[^\n]", login);
		
		if(!loginValido(login)){
			printf("Erro: O login não pode conter espaços. \n");
		} else if (cadastroExiste(usuarios, login)){
			printf("Erro: O Usuario com esse login, já existe. \n");
		}

    } while (!loginValido(login) || cadastroExiste(usuarios, login));

    strcpy(novoUsuario->login, login);

    printf("Nome: ");
    scanf(" %[^\n]", nome);
    strcpy(novoUsuario->nome, nome);

    printf("Senha: ");
    scanf(" %[^\n]", senha);
    strcpy(novoUsuario->senha, senha);

    // Verifica se o arquivo está vazio para definir o admin
    rewind(usuarios);
	novoUsuario->adminId = (fgetc(usuarios) == EOF) ? 1 : 0;

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

//ARRUMAR ESSA BOMBA AQUI
void filmeAssistido(FILE *portfolio, FILE *estatisticas, char *login) {
    //Adicionar plataformas
    int encontrado = 0;
    char linha[256];
    char nomeFilme[50];
    char procuraFilme[50];
    char genero[50];
    int ano;
    char duracao[10];
    printf("Qual o nome do filme que você quer adicionar como assistido? ");
    scanf(" %[^\n]", nomeFilme); // de novo o %s

    rewind(portfolio); // Volta ao início do arquivo para garantir que ele seja lido desde o começo
    while(fgets(linha, sizeof(linha), portfolio)){
        if(strstr(linha, nomeFilme) != NULL){ //vê se o filme existe no portfolio
            encontrado=1;//encontrado!
            sscanf(linha, "%[^|]|%[^|]|%[^|]|%d", procuraFilme, duracao, genero, &ano); //pegar a duração do filme
            break;
        }
    }
    if(encontrado >= 1){
        printf("Filme encontrado\n");
        //segmentation fault
        int minutos = converterParaInt(duracao);//char para int
        Estatisticas stats;//cria a struct que armazena as estatisticas 
        rewind(estatisticas);
        while(fgets(linha, sizeof(linha), portfolio)) {
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
