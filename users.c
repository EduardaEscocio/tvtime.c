#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "users.h"
#include "filmes.h"

int cadastroExiste(FILE *usuarios, char *login) {
    
	if(!usuarios){
		printf("Erro: Arquivo de usuários não está aberto. \n");
		return -1;
	}

	if(!login){
		printf("Usuário Login não encontrado!");
		return -2;
	}

	char linha[LINE_LENGTH];
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

	char nome[NAME_LENGTH];
    char login[LOGIN_LENGTH];
    char senha[PASSWORD_LENGTH];

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
    
    printf("Usuário registrado com sucesso!\n");
    // fclose(usuarios);
}


char *login(FILE *usuarios) {
	
	if(!usuarios){
		printf("Error: Arquivo de usuários não está aberto.");
		return NULL;
	}

    char linha[LINE_LENGTH];
    char login_atual[LOGIN_LENGTH];
    char senha_atual[PASSWORD_LENGTH];
    int encontrado = 0;

    printf("Digite seu login: ");
    scanf(" %[^\n]", login_atual);

    printf("Digite sua senha: ");
    scanf(" %[^\n]", senha_atual);

    rewind(usuarios); // Volta ao início do arquivo

    while (fgets(linha, sizeof(linha), usuarios)) {
        char nomeArquivo[LOGIN_LENGTH];
        char loginArquivo[LOGIN_LENGTH];
        char senhaArquivo[PASSWORD_LENGTH];
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
    char linha[LINE_LENGTH];
    rewind(usuarios);

    while (fgets(linha, sizeof(linha), usuarios)) {
        char nomeArquivo[LOGIN_LENGTH];
        char loginArquivo[LOGIN_LENGTH];
        char senhaArquivo[PASSWORD_LENGTH];
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

void filmeAssistido(FILE *portfolio, FILE *estatisticas, char *login) {
    
	if (!portfolio || !estatisticas || !login) {
        printf("Erro: Arquivos ou login inválidos.\n");
        return;
    }
	rewind(estatisticas);
	rewind(portfolio);

    char linha[LINE_LENGTH];
    char procuraFilme[NAME_LENGTH];
    char nomeFilme[NAME_LENGTH];
	char duration[10], gender[50];
	int found = 0;
    int year;

    char *plataformas[PLATFORM_NUMBER] = {"Netflix", "Disney+", "Globoplay", "HBO", "Amazon Prime", "Mercado Play"};
    int plataformaEscolha;
    
	printf("Qual o nome do filme que você quer adicionar como assistido? ");
    scanf(" %[^\n]", nomeFilme);
    
	printf("Qual plataforma você utilizou? \n");
	for (int count = 0; count < PLATFORM_NUMBER; count++){
		printf("[%d] %s \n", count + 1, plataformas[count]);
	}

    scanf("%d", &plataformaEscolha);

	if (plataformaEscolha < 1 || plataformaEscolha > sizeof(plataformas)){
		printf("Opção inválida! \n");
		return;
	}
	char *plataforma = plataformas[plataformaEscolha - 1];

    while (fgets(linha, sizeof(linha), portfolio)) {
        
        if (sscanf(linha, "%[^|]|%[^|]|%[^|]|%d|", procuraFilme, duration, gender, &year) == 4) {
            if (strcmp(procuraFilme, nomeFilme) == 0) {
                found = 1;
                fprintf(estatisticas, "%s|%s|%s|%s|%d|%s|\n", login, procuraFilme, duration, gender, year, plataforma);
                printf("Filme '%s' adicionado como assistido.\n", procuraFilme);
                break;
            }
        }
    }
    
    if (!found) {
        printf("Erro: Filme '%s' não existe no catálogo atual.\n", nomeFilme);
    }
}

void listarFilmesAssistidos(FILE* estatisticas, char *login){
    int encontrado;
    char linha[LINE_LENGTH];
    rewind(estatisticas);
    while(fgets(linha, sizeof(linha), estatisticas)){
        if(strstr(linha, login)){

         // Divide a linha em campos usando o delimitador "|"
        char *usuario = strtok(linha, "|");
        char *filme = strtok(NULL, "|");
        char *duracao = strtok(NULL, "|");
        char *genero = strtok(NULL, "|");
        char *ano_str = strtok(NULL, "|");
        char *plataforma = strtok(NULL, "|");

 
         // Verifica se todos os campos foram lidos corretamente
         if (filme && duracao && genero && ano_str && plataforma) {
             int ano = atoi(ano_str); // Converte o ano para inteiro
             printf("\nNome do filme: %s\n", filme);
             printf("Duração: %s\n", duracao);
             printf("Gênero: %s\n", genero);
             printf("Ano de lançamento: %d\n", ano);
             printf("Plataforma: %s\n", plataforma);
         }
    }
    }
}


void mostrarEstatisticasDoUsuario(FILE *estatisticas, char *login) {
    if (!estatisticas || !login) {
        printf("Erro: Arquivos ou login inválidos.\n");
        return;
    }

    char linha[LINE_LENGTH];
    int totalSeconds = 0; // Tempo total em segundos
    char mostUsedGenre[50] = ""; // Gênero mais assistido
    int maxGenreCount = 0;       // Contagem máxima de um gênero

    // Reinicia o ponteiro do arquivo para o início
    rewind(estatisticas);

    while (fgets(linha, sizeof(linha), estatisticas)) {
        char usuario[50], filme[50], tempo[50], genero[50], ano[50];

        // Extrai os campos da linha
        sscanf(linha, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]", usuario, filme, tempo, genero, ano);

        // Verifica se a linha pertence ao usuário
        if (strcmp(usuario, login) == 0) {
            // Extrai horas, minutos e segundos do tempo
            int hours, minutes, seconds;
            sscanf(tempo, "%d:%d:%d", &hours, &minutes, &seconds);

            // Converte o tempo para segundos e soma ao total
            totalSeconds += hours * 3600 + minutes * 60 + seconds;

            // Conta a frequência do gênero
            int genreCount = 1; // Inicia a contagem do gênero atual
            for (int i = 0; i < strlen(linha); i++) {
                if (strstr(linha + i, genero) == linha + i) {
                    genreCount++;
                    i += strlen(genero) - 1;
                }
            }

            // Atualiza o gênero mais assistido
            if (genreCount > maxGenreCount) {
                maxGenreCount = genreCount;
                strcpy(mostUsedGenre, genero);
            }
        }
    }

    // Converte o tempo total de segundos para HH:MM:SS
    int totalHours = totalSeconds / 3600;
    int remainingSeconds = totalSeconds % 3600;
    int totalMinutes = remainingSeconds / 60;
    int finalSeconds = remainingSeconds % 60;

    // Exibe as estatísticas
    printf("Estatisticas do Usuario: %s\n", login);
    printf("Tempo total de uso: %02d:%02d:%02d\n", totalHours, totalMinutes, finalSeconds);
    if (maxGenreCount > 0) {
        printf("Genero mais assistido: %s\n", mostUsedGenre);
    } else {
        printf("Nenhum genero registrado.\n");
    }
}

// void sugerirFilme(FILE *portfolio, char *login){
//     char linha[LINE_LENGHT];
//     char filmeSugeridoNome[NAME_LENGHT];
//     Filme *filmeSugerido = malloc(sizeof(Filme));
//     printf("Qual filme você quer sugerir?\n");
//     scanf("%s", filmeSugerido);
//     while (fgets(linha, sizeof(linha), portfolio)) {
//         if(strstr(linha, filmeSugerido) > 0){
//             printf("Filme já existente no portfólio: \n");
//             lerPortfolio(portfolio);
//         }
//     }else{
//         filmeSugerido->nome
//     }
// }
