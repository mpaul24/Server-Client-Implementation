

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
	int sockfd,newsockfd,portno,clilen;
	char  buffer[256];
	struct sockaddr_in serv_addr,cli_addr;
	int n;
	
	if(argc<2)
	{
		fprintf(stderr,"ERROR,no port provided\n");
		exit(1);
	}
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	//AF_INET : ip address concept
	//SOCK_STREAM : tcp/ip concept
	if(sockfd < 0)
	{
		error("ERROR");
	}
	
	bzero((char*) &serv_addr,sizeof(serv_addr));//clearing the server address
	portno = atoi(argv[1]);//convert char array to integer
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);//integer to network format
	
	if(bind(sockfd,(struct sockaddr*) &serv_addr,sizeof(serv_addr)) < 0)
	{
		error("ERROR in binding");
	}
	
	listen(sockfd,5);//server can connect to 5 client
	
	clilen = sizeof(cli_addr);
	
	newsockfd = accept(sockfd,(struct sockaddr*) &cli_addr,&clilen);
	
	
	while(1){
	if(newsockfd < 0 )
		error("ERROR on accept");
	
	bzero(buffer,256);
	
	n = read(newsockfd,buffer,255);
	
	if(n < 0)
		error("ERROR reading from socket");
		
	printf("Client: %s\n",buffer);
	bzero(buffer,256);
	fgets(buffer,255,stdin);
	n = write(newsockfd,buffer,strlen(buffer));
	
	if(n < 0)
		error("ERROR writing to socket");
	}
	
	return 0;
	
	
	
	
	
	
	 
	
}
