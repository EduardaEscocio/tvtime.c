#include <stdio.h>

int menuPrincipal() {
    int opcaoMenu = 0;  

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
    
    if (scanf("%d", &opcaoMenu) != 1) {
        while (getchar() != '\n');  
        return -1;  
    }
    return opcaoMenu;
}

int menuAdmin() {
    int opcaoMenuAdmin = 9;  

    printf("\n\033[0;36m");
    printf("===================================\n");
    printf("           MENU ADMIN             \n");
    printf("===================================\n");
    printf("\t[1] - Adicionar novo filme\n");
    printf("\t[0] - Sair\n");
    printf("===================================\n");
    printf("\033[0m");
    
    printf("Opção: ");
    
    if (scanf("%d", &opcaoMenuAdmin) != 1) {
        while (getchar() != '\n');
        return -1;
    }
    return opcaoMenuAdmin;
}


