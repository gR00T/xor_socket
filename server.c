#include <netdb.h> 
#include <netinet/in.h> 
#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <sys/wait.h>
#include <unistd.h>
#include "xor.h"
#define MAX 80 
#define PORT 9000 
#define SA struct sockaddr 
  
void chat_loop(int client_fd){

	char buff[MAX];
	int n;
	int len;

	// Chat loop
	for (;;){
		bzero(buff,MAX);

		// Read data from the socket
		len = read(client_fd, buff, sizeof(buff));

		xor(buff,len);

		// Print data on server side
		printf("%s\n", buff);
		
		bzero(buff,MAX);
		n = 0;
		
		// Receive data from stdin to send to the client
		while ((buff[n++] = getchar()) != '\n');

		xor(buff,n);

		write(client_fd, buff, sizeof(buff));

		// Handle "exit" command
		if (strncmp("exit", buff, 4) == 0){
			printf("Server exiting.\n");
			break;
		}
	}
}

int create_server(){


	int sockfd, connfd, len;
	struct sockaddr_in servaddr, cli;

	// Create socket
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("Failed to start server\n");
		return 1;
	}

	// Assign the port and IP address for the server
	servaddr.sin_family = AF_INET;
	servaddr.sin_port   = htons(PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0){
		printf("Failed to bind server.\n");
		return 1;
	}

	if ((listen(sockfd,2)) != 0){
		printf("Failed to start listening.\n");
		return 1;
	}

	len = sizeof(cli);

	// Accept a new connection
	if ((connfd = accept(sockfd, (SA*)&cli, &len)) < 0){
		printf("Connection from client failed!");
	}else{
		if (fork() == 0){
			chat_loop(connfd);
		}else{
			wait(NULL);
			close(sockfd);
			create_server();
		}
	}

	return 0;
}

void main(){
	create_server();
}	
