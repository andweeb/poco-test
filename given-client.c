#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

#define BUFFER_SIZE     256

void error(const char *message){
    perror(message);
    exit(0);
}

int main(int argc, char *argv[]){
    int SocketFileDescriptor, PortNumber, Result;
    struct sockaddr_in ServerAddress;
    struct hostent *Server;
    char Buffer[BUFFER_SIZE];
    
    if(3 > argc){
        fprintf(stderr,"usage %s hostname port\n", argv[0]);
        exit(0);
    }
    PortNumber = atoi(argv[2]);
    if((1 > PortNumber)||(65535 < PortNumber)){
        fprintf(stderr,"Port %d is an invalid port number\n",PortNumber);
        exit(0);
    }
    // Create TCP/IP socket
    printf("Creating socket\n");
    SocketFileDescriptor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(0 > SocketFileDescriptor){
        error("ERROR opening socket");
    }
    // Convert/resolve host name 
    Server = gethostbyname(argv[1]);
    if(NULL == Server){
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    // Setup ServerAddress data structure
    bzero((char *) &ServerAddress, sizeof(ServerAddress));
    ServerAddress.sin_family = AF_INET;
    bcopy((char *)Server->h_addr, (char *)&ServerAddress.sin_addr.s_addr, Server->h_length);
    ServerAddress.sin_port = htons(PortNumber);
    // Connect to server
    if(0 > connect(SocketFileDescriptor, (struct sockaddr *)&ServerAddress, sizeof(ServerAddress))){
        error("ERROR connecting");
    }
	while(1) { // Is this not the way to go? ):
	    printf("Please enter the message: ");
	    bzero(Buffer, BUFFER_SIZE);
	    fgets(Buffer, BUFFER_SIZE-1, stdin);
	    // Write data to server
	    Result = write(SocketFileDescriptor, Buffer, strlen(Buffer));
	    if(0 > Result){ 
	        error("ERROR writing to socket");
	    }
	    bzero(Buffer, BUFFER_SIZE);
	    // Read data from server
	    Result = read(SocketFileDescriptor, Buffer, BUFFER_SIZE-1);
	    if(0 > Result){ 
	        error("ERROR reading from socket");
	    }
	    printf("%s\n",Buffer);
	}
    close(SocketFileDescriptor);
    return 0;
}
