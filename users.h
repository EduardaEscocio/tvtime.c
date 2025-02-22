#ifndef USERS_H
#define USERS_H

#include <stdio.h>

typedef struct usuario{
    char login[50];
    char senha[50];
    char nome[50];
    int adminId; // 0 - comun - 1 admin
} User;

typedef struct estatisticas {
    char login[50];
    int horasTotais;
    int minutosTotais;
} Estatisticas;

void cadastro(FILE *usuarios);
char* login(FILE *usuarios);
void filmeAssistido(FILE *portfolio, FILE *estatisticas, char *login);
int loginExiste(FILE *usuarios, char *login);
int loginValido(char *login);
int converterParaInt(char *duracao);

#endif

