#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

char* executar(int fe,char* linha,char* resultado){
	int p[2], p2[2];
	pipe(p);
	pipe(p2);
	char buf[2000]=" ";

	printf(">>>\n");

	char** comando = agrupaComando(linha);

	if(fork()==0){
		dup2(p[1],1);
		close(p[1]);
		close(p[0]);
		execvp(comando[0],comando);
		_exit(-1);
	}
	
	close(p[1]);
	read(p[0],buf,sizeof(buf));
	printf("%s\n", buf);
	wait(NULL);

	printf("<<<\n");

	resultado = strdup(buf);
	return resultado;
}

void lerFicheiro(int fe, int fs) {
	int i;
	char buffer[6][200];
	char* resultado=malloc(sizeof(resultado));

	for(i=0;i<6;i++) {
		fazEcho(fe,i,buffer[i]);
	}

	dup2(fs,1);
	close(fs);

	for(i=0;i<6;i++) {
		printf("%s\n", buffer[i]);
		if(buffer[i][0] == '$') {
			resultado=strdup(executar(fe,buffer[i],resultado));
		}
	}
}

int main(int argc, char const *argv[]){
	int fo, fe, fs;
	fo=open("DocumentoTeste",O_RDONLY);
	fs=open("DocumentodeSaida",O_CREAT | O_WRONLY | O_TRUNC, 0666);
	fe=open("Erros.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666);
	
	if (fe==-1) {
		perror("Erro na criação do ficheiro error.txt\n");
		_exit(-1);
	}
	dup2(fe,2);
	close(fe);

	if (fo==-1) {
		perror("Erro ao abrir ficheiro leitura");
		_exit(-1);
	}

	if (fs==-1) {
		perror("Erro ao abrir ficheiro escrita");
		_exit(-1);
	}

	lerFicheiro(fo,fs);

}