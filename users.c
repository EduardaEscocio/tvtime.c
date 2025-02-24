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

	char linha[LINE_LENGHT];
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
	
	if(!usuarios){
		printf("Error: Arquivo de usuários não está aberto.");
		return NULL;
	}

    char linha[LINE_LENGHT];
    char login_atual[LOGIN_LENGHT];
    char senha_atual[PASSWORD_LENGHT];
    int encontrado = 0;

    printf("Digite seu login: ");
    scanf(" %[^\n]", login_atual);

    printf("Digite sua senha: ");
    scanf(" %[^\n]", senha_atual);

    rewind(usuarios); // Volta ao início do arquivo

    while (fgets(linha, sizeof(linha), usuarios)) {
        char nomeArquivo[LOGIN_LENGHT];
        char loginArquivo[LOGIN_LENGHT];
        char senhaArquivo[PASSWORD_LENGHT];
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
    char linha[LINE_LENGHT];
    rewind(usuarios);

    while (fgets(linha, sizeof(linha), usuarios)) {
        char nomeArquivo[LOGIN_LENGHT];
        char loginArquivo[LOGIN_LENGHT];
        char senhaArquivo[PASSWORD_LENGHT];
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
    int horas, minutos, segundos; 
    if (sscanf(duracao, "%d:%d:%d", &horas, &minutos, &segundos) == 3){
		return horas * 60 + minutos;
	}
	return 0;
}


void filmeAssistido(FILE *portfolio, FILE *estatisticas, char *login) {
    if (!portfolio || !estatisticas || !login) {
        printf("Erro: Arquivos ou login inválidos.\n");
        return;
    }

    char linha[LINE_LENGHT];
    char nomeFilme[NAME_LENGHT];
    char procuraFilme[NAME_LENGHT];
    char duracao[10];
    char genero[50];
    int ano;
    int encontrado = 0;

    // Solicita o nome do filme
    printf("Qual o nome do filme que você quer adicionar como assistido? ");
    scanf(" %[^\n]", nomeFilme);

    nomeFilme[strcspn(nomeFilme, "\n")] = '\0';  // Remove a nova linha deixada pelo fgets

    // Procura o filme no portfólio
    rewind(portfolio);
    while (fgets(linha, sizeof(linha), portfolio)) {
        // Remove o caractere de nova linha no final da linha (se houver)
        linha[strcspn(linha, "\n")] = '\0';

        // Extrai os campos da linha
        if (sscanf(linha, "%[^|]|%[^|]|%[^|]|%d|", procuraFilme, duracao, genero, &ano) == 4) {
            if (strcmp(procuraFilme, nomeFilme) == 0) {  // Comparação exata do nome do filme
                encontrado = 1;
                break;
            }
        }
    }

    if (encontrado) {
        // Escreve no arquivo de estatísticas
        if (fprintf(estatisticas, "%s|%s|%s|%s|%d|\n", login, procuraFilme, duracao, genero, ano) < 0) {
            printf("Erro: Falha ao escrever no arquivo de estatísticas.\n");
        } else {
            printf("Filme '%s' adicionado como assistido.\n", procuraFilme);
        }
    } else {
        printf("Erro: Filme '%s' não existe no catálogo atual.\n", nomeFilme);
    }
}
