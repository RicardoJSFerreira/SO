#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int escreveFicheiro(int fe, char* buf){
	if (fe==-1) {
		perror("Erro ao abrir ficheiro escrita");
		_exit(-1);
	}

	dup2(fe,1);

	close(fe);

	execlp(buf,"wpojrgirewjgoi",NULL);
	_exit(-1);
}
