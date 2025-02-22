#include <stdio.h>

#include "menus.h"
#include "users.h"
#include "filmes.h"

char ch;
int opcaoMenu = 9;

int main(){
    FILE *usuarios = fopen("usuarios.txt", "a+");
    FILE *portfolio = fopen("portfolio.txt", "a+"); // Abre o arquivo para leitura e escrita
    
	if (portfolio == NULL) {
        printf("Erro ao abrir o arquivo portfolio.txt\n");
        return 1;
    }

//menus
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
