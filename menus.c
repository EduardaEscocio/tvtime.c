#include <stdio.h>
#include <stdlib.h>

#include "filmes.h"
#include "users.h"

int menuPrincipal() {
    int opcaoMenuPrincipal = 0;  

    printf("\n\033[0;36m");
    printf("===================================\n");
    printf("          MENU PRINCIPAL          \n");
    printf("===================================\n");
    printf("\t[1] - Cadastro\n");
    printf("\t[2] - Login\n");
    printf("\t[3] - Ler portfólio de filmes\n");
    printf("\t[0] - Sair\n");
    printf("===================================\n");
    printf("\033[0m");
    
    printf("Opção: ");
    
    if (scanf("%d", &opcaoMenuPrincipal) != 1) {
        while (getchar() != '\n');  
	    system("clear");
        return -1;  
    }
	return opcaoMenuPrincipal;
}
int menuUsuario(FILE *portfolio, FILE * estatisticas) {
    int opcaoMenuUsuario = 9;  

    printf("\n\033[0;36m");
    printf("===================================\n");
    printf("           MENU USUÁRIO             \n");
    printf("===================================\n");
    printf("\t[1] - Adicionar filme como assistido\n");
    printf("\t[2] - Visualizar estatísticas\n");
    printf("\t[3] - Listar filmes assistidos\n");
    printf("\t[0] - Sair\n");
    printf("===================================\n");
    printf("\033[0m");
    
    printf("Opção: ");
    
    if (scanf("%d", &opcaoMenuUsuario) != 1) {
        while (getchar() != '\n');
	    system("clear");
        return -1;
    }
    return opcaoMenuUsuario;
}

int menuAdmin(FILE *portfolio, FILE * estatisticas, char *login) {
    int opcaoMenuAdmin = 9;  

	do {
		printf("\n\033[0;36m");
		printf("===================================\n");
		printf("           MENU ADMIN             \n");
		printf("===================================\n");
		printf("\t[1] - Adicionar novo filme\n");
		printf("\t[2] - Adicionar filme como assistido\n");
		printf("\t[3] - Visualizar estatísticas\n");
		printf("\t[4] - Listar filmes assistidos\n");
		printf("\t[0] - Sair\n");
		printf("===================================\n");
		printf("\033[0m");
    
		printf("Opção: ");
    
    if (scanf("%d", &opcaoMenuAdmin) != 1) {
        while (getchar() != '\n');
		system("clear");
		printf("Error: Entrada Inválida! Digite um número valido. \n");
    }
	switch (opcaoMenuAdmin) {
        case 1:
            adicionarFilme(portfolio);
            break;
        case 2:
            filmeAssistido(portfolio, estatisticas, login);
            break;
        case 3:
            // mostrarEstatisticasDoUsuario(estatisticas, login);
            break;
        case 4:
            listarFilmesAssistidos(estatisticas, login);
            break;

        case 0:
            system("clear");
            return 0;
			break;

        }
    } while (opcaoMenuAdmin != 0); // Repete até o usuário escolher a opção 0

    return 0; // Retorna 0 para indicar que o menu foi finalizado
}


