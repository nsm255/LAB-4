#include<unistd.h>
#include<arpa/inet.h>
#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 

// Function designed for chat between client and server. 
void func(int sockfd) 
{ 
	char buff[80]; 
	int n; 
	
	// infinite loop for chat 
	for (;;) { 
		bzero(buff, 80); 

		// read the messtruct sockaddrge from client and copy it in buffer 
		read(sockfd, buff, sizeof(buff)); 
		// print buffer which contains the client contents 
		printf("\nClient: %sYOU   : ", buff); 
		bzero(buff, 80); 
		n = 0; 
		// copy server messtruct sockaddrge in the buffer 
		while ((buff[n++] = getchar()) != '\n') 
			; 

		// and send that buffer to client 
		write(sockfd, buff, sizeof(buff)); 

		// if msg contains "Exit" then server exit and chat ended. 
		if (strncmp("exit", buff, 4) == 0) { 
			printf("\nServer Exiting...\n"); 
			printf("**********WHATSAPP CHATING ROOM**********\n\n"); 
			break; 
		} 
	} 
} 

// Driver function 
int main() 
{ 
	int sockfd, connfd, len; 
	struct sockaddr_in servaddr, cli; 

	// socket create and verification 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) { 
		printf("Socket creation failed.\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully created.\n"); 
	bzero(&servaddr, sizeof(servaddr)); 

	// assign IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	servaddr.sin_port = htons(8888); 

	// Binding newly created socket to given IP and verification 
	if ((bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr))) != 0) { 
		printf("Socket bind failed.\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully binded.\n"); 
	
		/* About socket binding: 
		This program may be having a hard time performing this process.
		Just leave it for a few seconds and try again, then it will work. Reasons unknown. */
	

	// Now server is ready to listen and verification 
	if ((listen(sockfd, 5)) != 0) { 
		printf("Listen failed.\n"); 
		exit(0); 
	} 
	else
		printf("Server listening...\n"); 
	len = sizeof(cli); 

	// Accept the data packet from client and verification 
	connfd = accept(sockfd, (struct sockaddr*)&cli, &len); 
	if (connfd < 0) { 
		printf("Server acccept failed.\n"); 
		exit(0); 
	} 
	else {
		printf("Server acccepted a client. Send a response message to start a chat.\n");
		printf("Type [exit] to close the server and chat. \n\n**********WHATSAPP CHATING ROOM**********\n"); 
	}

	// Function for chatting between client and server 
	func(connfd); 

	// After chatting close the socket 
	close(sockfd); 
}
