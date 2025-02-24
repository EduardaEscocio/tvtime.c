#include <stdio.h>
#include <stdlib.h>

#include "menus.h"
#include "users.h"
#include "filmes.h"

int main() {
    int opcaoMenu = -1;  // Inicializa com um valor diferente de 0 para entrar no loop
    int opcaoMenuUsuario, opcaoMenuAdmin;

    // Abre os arquivos uma única vez
    FILE *estatisticas = fopen("./estatisticas.txt", "a+");
    FILE *portfolio = fopen("./portfolio.txt", "a+");
    FILE *usuarios = fopen("./usuarios.txt", "a+");

    // Verifica se a abertura dos arquivos foi bem-sucedida
    if (usuarios == NULL || estatisticas == NULL || portfolio == NULL) {
        printf("Erro ao abrir os arquivos.\n");
        return 1;
    }

    while (opcaoMenu != 0) {
        opcaoMenu = menuPrincipal(portfolio, usuarios, estatisticas);

        switch (opcaoMenu) {
            case 1:
                cadastro(usuarios);
                break;

            case 2: {
                char *usuario = login(usuarios);
                
                // Verifica se o login foi bem-sucedido
                if (usuario != NULL) { 
                    printf("Bem-vindo, %s!\n", usuario);

                    int id = detectarAdm(usuario, usuarios);

                    if (id == 0) {
                            opcaoMenuUsuario = menuUsuario(portfolio);
                    } else {
                        
                        opcaoMenuAdmin = menuAdmin(portfolio, estatisticas, usuario);
                      
                    }
                } else {
                    printf("Falha no login. Tente novamente.\n");
                }
                break;
            }

            case 3:
                lerPortfolio(portfolio);
                break;

            case 0:
                printf("Saindo do programa...\n");
                break;

            default:
                printf("Opção inválida! Escolha uma opção do menu.\n");
                break;
        }
    }

    // Fecha os arquivos antes de sair
    fclose(estatisticas);
    fclose(portfolio);
    fclose(usuarios);

    return 0;
}
