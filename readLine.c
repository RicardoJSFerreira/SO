#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>

void readLine(int fe, char* buf, long size){
	char c;
	int n,jalidos=0;
	n=read(fe,&c,1);
	if (c=='$') {
	while((n=read(fe,&c,1))>0 && c!='\n'){
		buf[jalidos]=c;
		jalidos++;
		}
	}
	buf[jalidos]='\0';
	printf("%s\n", buf);
}