#ifndef MENUS_H
#define MENUS_H

#include <stdio.h>
int menuPrincipal(FILE *portfolio, FILE *usuarios, FILE *estatisticas);
int menuAdmin(FILE *portfolio, FILE * estatisticas, char *login);
int menuUsuario();
#endif
