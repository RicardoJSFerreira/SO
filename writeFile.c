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

char* fazEcho(int fe, int i,char* buf){
	int n, jalidos=0;
	char c;
	while((n=read(fe,&c,1))>0 && c!='\n'){
		buf[jalidos]=c;
		jalidos++;
	}
	buf[jalidos]='\0';
}


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

int escreveFicheiro(){
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



int main(int argc, char const *argv[])
{
	int i;
	i=escreveFicheiro();
	return 0;
}
