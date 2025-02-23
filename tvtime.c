#include <stdio.h>
#include <stdlib.h>
#include "menus.h"
#include "users.h"
#include "filmes.h"

int main(){
    FILE *estatisticas = fopen("./estatisticas.txt", "a+");
    FILE *portfolio = fopen("./portfolio.txt", "a+");
    FILE *usuarios = fopen("./usuarios.txt", "a+");
    
    if (usuarios == NULL || estatisticas == NULL || portfolio == NULL) {
        printf("Erro ao abrir os arquivos.\n");
        return 1;
    }
    
    while (opcaoMenu != 0) {
        opcaoMenu = menuPrincipal();
        if (opcaoMenu == 1) {
            // FILE *usuarios = fopen("usuarios.txt", "a+");
            cadastro(usuarios);
            // fclose(usuarios);
        } 
        else if(opcaoMenu == 2) {
            char *usuario = login(usuarios);
            int id = detectarAdm(usuario ,usuarios);
            if(usuario!= NULL){ //fazer aq
                printf("Bem-vindo, %s!\n", usuario);
                free(usuario);
                if(id == 0){
                    do{
                        opcaoMenuUsuario = menuUsuario(portfolio);
                    }while(opcaoMenuUsuario!=0);
                }
                else{
                    do{
                        opcaoMenuAdmin = menuAdmin(portfolio);
                        }while(opcaoMenuAdmin!=0);
                }
            }
            
            else if (opcaoMenu == 3) {
                lerPortfolio(portfolio);
                
            } else if (opcaoMenu == 4) {
                adicionarFilme(portfolio);
                
                // } else if (opcaoMenu == 5 && loginUsuario != NULL) {
                    //     filmeAssistido(portfolio, estatisticas, loginUsuario); // Passa o login do usuário
                    // }
                    
                }
            }
        }
fclose(estatisticas);
fclose(portfolio);
fclose(usuarios);
return 0;
}