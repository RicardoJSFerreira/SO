#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>

char* fazEcho(int fe, int i,char* buf){
	int n, jalidos=0;
	char c;
	while((n=read(fe,&c,1))>0 && c!='\n'){
		buf[jalidos]=c;
		jalidos++;
	}
	buf[jalidos]='\0';
}
