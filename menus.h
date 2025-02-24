#ifndef MENUS_H
#define MENUS_H

#include <stdio.h>

int opcaoMenuAdmin = 6;
int opcaoMenuUsuario = 6;
int opcaoMenu = 6;

int menuPrincipal();
int menuAdmin(FILE *portfolio, FILE * estatisticas, char *login);
int menuUsuario();
#endif
