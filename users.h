#ifndef USERS_H
#define USERS_H

#include <stdio.h>

typedef struct usuario{
    char login[50];
    char senha[50];
    char nome[50];
    int adminId; // 0 - comun - 1 admin
} User;

void cadastro(FILE *usuarios);
void login();

#endif

