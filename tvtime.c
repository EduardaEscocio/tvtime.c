#include <stdio.h>
#include <stdlib.h>
#include "menus.h"
#include "users.h"
#include "filmes.h"

int opcaoMenu = 9;

int main() {
    FILE *estatisticas = fopen("estatisticas.txt", "a+");
    FILE *portfolio = fopen("portfolio.txt", "a+");

    if (estatisticas == NULL || portfolio == NULL) {
        printf("Erro ao abrir os arquivos.\n");
        return 1;
    }

    char *loginUsuario = NULL; // Armazena o login do usuário logado

    while (opcaoMenu != 0) {
        opcaoMenu = menuPrincipal();
        if (opcaoMenu == 1) {
            FILE *usuarios = fopen("usuarios.txt", "a+");
            cadastro(usuarios);
            fclose(usuarios);
        } else if (opcaoMenu == 2) {
            FILE *usuarios = fopen("usuarios.txt", "a+");
            loginUsuario = login(usuarios); // Captura o login do usuário
            if (loginUsuario != NULL) {
                printf("Bem-vindo, %s!\n", loginUsuario);
            }
            fclose(usuarios);

        } else if (opcaoMenu == 3) {
            lerPortfolio(portfolio);
        } else if (opcaoMenu == 4) {
            adicionarFilme(portfolio);
        } else if (opcaoMenu == 5 && loginUsuario != NULL) {
            filmeAssistido(portfolio, estatisticas, loginUsuario); // Passa o login do usuário
        }
    }

    // Libera a memória alocada para o login
    if (loginUsuario != NULL) {
        free(loginUsuario);
    }

    fclose(estatisticas);
    fclose(portfolio);
    return 0;
}