#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "users.h"
#include "utils.h"

void cadastro(FILE *usuarios) {
    char nome[50];
    char login[50];
    char senha[50];

    User *novoUsuario = (User*)malloc(sizeof(User));
    if(novoUsuario == NULL){
        printf("Erro ao alocar memória");
        return;
    }

    do {
        printf("Login: ");
        scanf(" %[^\n]s", login);
    } while(strlen(login) < 3); // Validação simples

    strcpy(novoUsuario->login, login);
    printf("Nome: ");
    scanf(" %[^\n]s", nome);
    strcpy(novoUsuario->nome, nome);
    printf("Senha: ");
    scanf(" %[^\n]s", senha);
    strcpy(novoUsuario->senha, senha);

    if(usuarios == NULL){
        printf("Erro ao abrir o arquivo\n");
        free(novoUsuario);
        return;
    }

    if(fgetc(usuarios) == EOF){
        novoUsuario->adminId = 1; // Primeiro usuário é admin
    } else {
        novoUsuario->adminId = 0;
    }

    fprintf(usuarios, "%s | %s | %s | %d\n", novoUsuario->nome, novoUsuario->login, novoUsuario->senha, novoUsuario->adminId);
    fclose(usuarios);
    free(novoUsuario);
    printf("Usuário registrado com sucesso!\n");
    limparBuffer();
}

void login() {
    char login_atual[50];
    char senha_atual[50];
    
    printf("Digite seu login: ");
    scanf(" %[^\n]s", login_atual);
    printf("Digite sua senha: ");
    scanf(" %[^\n]s", senha_atual);
    
    // Aqui, você pode implementar a lógica para verificar os usuários no arquivo
}
