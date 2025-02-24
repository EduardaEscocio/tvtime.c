#ifndef USERS_H
#define USERS_H

#include <stdio.h>

#define LOGIN_LENGHT 50
#define PASSWORD_LENGHT 50
#define NAME_LENGHT 50
#define LINE_LENGHT 256

typedef struct usuario{
    char login[LOGIN_LENGHT];
    char senha[PASSWORD_LENGHT];
    char nome[NAME_LENGHT];
    int adminId; // 0 - comun - 1 admin
} User;

typedef struct estatisticas {
    char login[LOGIN_LENGHT];
    int horasTotais;
    int minutosTotais;
} Estatisticas;

void cadastro(FILE *usuarios); //
char *login(FILE *usuarios); //
void filmeAssistido(FILE *portfolio, FILE *estatisticas, char *login); //
int loginValido(char *login); //
int converterParaInt(char *duracao); //
int detectarAdm(char *login, FILE *usuarios); //
int cadastroExiste(FILE *usuarios, char *login); //

#endif

