#include <stdio.h>

#include "utils.h"


int converterParaInt(char *duracao){
    int horas, minutos, segundos; 
    if (sscanf(duracao, "%d:%d:%d", &horas, &minutos, &segundos) == 3){
		return horas * 60 + minutos;
	}
	return 0;
}
