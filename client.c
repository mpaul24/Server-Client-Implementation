#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <netinet/in.h>

#include <string.h>

void error(char *msg)
{
	perror(msg);
	exit(1);
}

int main(int argc,char *argv[])
{
	int sockfd,portno;
	char  buffer[256];
	struct sockaddr_in serv_addr;
	struct hostent *server;
	int n;
	
	if(argc<3)
	{
		fprintf(stderr,"ERROR,no port provided\n");
		exit(1);
	}
	
	portno = atoi(argv[2]);//convert char array to integer
	
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	//AF_INET : ip address concept
	//SOCK_STREAM : tcp/ip concept
	if(sockfd < 0)
	{
		error("ERROR");
	}
	
	server = gethostbyname(argv[1]);
	if(server == NULL)
	{
		fprintf(stderr,"ERROR, no such host\n");
		exit(0);
	}
	
	bzero((char*)&serv_addr,sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	
	bcopy((char*)server->h_addr,(char*)&serv_addr.sin_addr.s_addr,server->h_length);
	serv_addr.sin_port = htons(portno);
	
	if(connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) < 0)
	 	error("ERROR connecting");
	while(1){
	bzero(buffer,256);
	fgets(buffer,255,stdin);
	n = write(sockfd,buffer,strlen(buffer));
	if(n<0)
		error("ERROR writing in socket");
	bzero(buffer,256);
	n = read(sockfd,buffer,255);
	if(n<0)
		error("ERROR reading from socket");
	
	printf("%s\n",buffer);
	}
	
	return 0;
	
	
	
}
