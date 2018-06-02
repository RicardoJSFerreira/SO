#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

char** agrupaComando(char* linha){
	char* var = strdup(linha);
	int j;
	char* token;
	const char separador[5] = "$| \n";
	char** resultado = malloc(sizeof(char*)*2048);
	int i = 0;
	token = strtok(var,separador);
	while(token!=NULL){
		resultado[i] = token;
		token = strtok (NULL, separador);
		i++;
	}

	char** final = malloc(sizeof(char*)*(i+1));
	for(j=0;j<i;j++){
		final[j] = resultado[j];
	}
	final[j] = NULL;
	return final;

}