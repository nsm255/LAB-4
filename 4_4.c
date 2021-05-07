#include<unistd.h>
#include<arpa/inet.h>
#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <signal.h>

// function for chat
void func(int sockfd) 
{ 
	char buff[80]; 
	int n; 
	for (;;) { 
		bzero(buff, sizeof(buff)); 
		printf("YOU   : "); 
		n = 0; 
		while ((buff[n++] = getchar()) != '\n'); 
		write(sockfd, buff, sizeof(buff)); 
		bzero(buff, sizeof(buff)); 
		read(sockfd, buff, sizeof(buff)); 
		printf("\nServer: %s", buff); 
		if ((strncmp(buff, "exit", 4)) == 0) { 
			printf("\nClient Exiting...\n"); 
			printf("**********WHATSAPP CHATING ROOM**********\n\n"); 
			break; 
		} 
		
	} 
} 

int main() 
{ 
	int sockfd, connfd; 
	struct sockaddr_in servaddr, cli; 

	// socket create and varification 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) { 
		printf("Socket creation failed.\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully created.\n"); 
	bzero(&servaddr, sizeof(servaddr)); 

	// assign IP, PORT 
	printf("Please insert IP address of server: \n>>> ");
	char ipserver[20];
	scanf("%s", ipserver);
	servaddr.sin_family = AF_INET;  
	servaddr.sin_addr.s_addr = inet_addr(ipserver); 
	servaddr.sin_port = htons(8888); 

	// connect the client socket to server socket 
	if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0) { 
		printf("Connection with the server failed.\n"); 
		exit(0); 
	} 
	else {
		printf("Connected to the server. Waiting for a response...\nPress [CTRL + C] to quit anytime\n\n**********WHATSAPP CHATING ROOM**********\n"); 
	}
	
	// function for chat 
	func(sockfd); 

	// close the socket 
	close(sockfd); 

} 
