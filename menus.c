#include <stdio.h>

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
        return -1;  
    }
    return opcaoMenuPrincipal;
}
int menuUsuario() {
    int opcaoMenuUsuario = 9;  

    printf("\n\033[0;36m");
    printf("===================================\n");
    printf("           MENU USUÁRIO             \n");
    printf("===================================\n");
    printf("\t[1] - Adicionar novo filme\n");
    printf("\t[2] - Adicionar filme como assistido\n");
    printf("\t[3] - Visualizar estatísticas\n");
    printf("\t[4] - Listar filmes assistidos\n");
    printf("\t[0] - Sair\n");
    printf("===================================\n");
    printf("\033[0m");
    
    printf("Opção: ");
    
    if (scanf("%d", &opcaoMenuUsuario) != 1) {
        while (getchar() != '\n');
        return -1;
    }
    return opcaoMenuUsuario;
}

int menuAdmin() {
    int opcaoMenuAdmin = 9;  

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
        return -1;
    }
    return opcaoMenuAdmin;
}


