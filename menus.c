#include <stdio.h>
#include <stdlib.h>

#include "filmes.h"
#include "users.h"

int menuPrincipal(FILE *portfolio, FILE *usuarios, FILE *estatisticas) {
    int opcaoMenuPrincipal = -1;  

    while (opcaoMenuPrincipal < 0 || opcaoMenuPrincipal > 3) {
        printf("\n\033[0;36m");
        printf("===================================\n");
        printf("          MENU PRINCIPAL          \n");
        printf("===================================\n");
        printf("\t[1] - Cadastro\n");
        printf("\t[2] - Login\n");
        printf("\t[3] - Filmes\n");
        printf("\t[0] - Sair\n");
        printf("===================================\n");
        printf("\033[0m");
        
        printf("Opção: ");
        scanf("%d", &opcaoMenuPrincipal);
        
        }if (opcaoMenuPrincipal < 0 || opcaoMenuPrincipal > 3) {
            system("clear");
            printf("Error: Opção inválida! Digite um número entre 0 e 3. \n");
        }
        return opcaoMenuPrincipal;
    }

int menuUsuario(FILE *portfolio, FILE *estatisticas, char *login) {
    int opcaoMenuUsuario = -1;  
    
    while (opcaoMenuUsuario != 0) {
        printf("\n\033[0;36m");
        printf("===================================\n");
        printf("           MENU USUÁRIO             \n");
        printf("===================================\n");
        printf("\t[1] - Adicionar filme como assistido\n");
        printf("\t[2] - Estatísticas\n");
        printf("\t[3] - Filmes assistidos\n");
        printf("\t[4] - Sugerir filmes\n");
        printf("\t[0] - Sair\n");
        printf("===================================\n");
        printf("\033[0m");
        
        printf("Opção: ");
        
       
            
            if (opcaoMenuUsuario < 0 || opcaoMenuUsuario > 3) {
            system("clear");
            printf("Error: Opção inválida! Digite um número entre 0 e 3. \n");
        } else {
            switch (opcaoMenuUsuario) {
                case 1:
                    filmeAssistido(portfolio, estatisticas, login);
                    break;
                case 2:
                    mostrarEstatisticasDoUsuario(estatisticas, login);
                    break;
                case 3:
                    listarFilmesAssistidos(estatisticas, login);
                    break;
                case 4:
                    sugerirFilme(portfolio, login);
                    break;
                case 0:
                    break;
                default:
                    printf("Error: Opção inválida! \n");
            }
        }
    }
    return opcaoMenuUsuario;
}

int menuAdmin(FILE *portfolio, FILE *estatisticas, char *login) {
    int opcaoMenuAdmin = -1;  

    while (opcaoMenuAdmin != 0) {
        printf("\n\033[0;36m");
        printf("===================================\n");
        printf("           MENU ADMINISTRADOR            \n");
        printf("===================================\n");
        printf("\t[1] - Adicionar novo filme\n");
        printf("\t[2] - Adicionar filme como assistido\n");
        printf("\t[3] - Estatísticas\n");
        printf("\t[4] - Filmes assistidos\n");
        printf("\t[5] - Filmes sugeridos pelos usuários\n");
        printf("\t[0] - Sair\n");
        printf("===================================\n");
        printf("\033[0m");
        
        printf("Opção: ");
        
        if (scanf("%d", &opcaoMenuAdmin) != 1) {
            
            opcaoMenuAdmin = -1;
        } else if (opcaoMenuAdmin < 0 || opcaoMenuAdmin > 5) {
            system("clear");
            printf("Error: Opção inválida! Digite um número entre 0 e 5. \n");
        } else {
            switch (opcaoMenuAdmin) {
                case 1:
                    adicionarFilme(portfolio);
                    break;
                case 2:
                    filmeAssistido(portfolio, estatisticas, login);
                    break;
                case 3:
                    mostrarEstatisticasDoUsuario(estatisticas, login);
                    break;
                case 4:
                    listarFilmesAssistidos(estatisticas, login);
                    break;
                case 5:
                    verFilmesSugeridos(login);
                    break;
                case 0:
                    break;
                default:
                    printf("Error: Opção inválida! \n");
            }
        }
    }
    return 0; // Retorna 0 para indicar que o menu foi finalizado
}