#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUF 4096

#define USAGE                                                                 \
"usage:\n"                                                                    \
"  echoserver [options]\n"                                                    \
"options:\n"                                                                  \
"  -p                  Port (Default: 8888)\n"                                \
"  -h                  Show this help message\n"                              \
"  -n                  Maximum pending connections (Default:5)\n"             \

int main(int argc, char **argv) {
    int option_char;
    int portno = 8888; /* port to listen on */
    int maxConnections = 5;

    // Parse and set command line arguments
    while ((option_char = getopt(argc, argv, "p:n:h")) != -1){
        switch (option_char) {
            case 'p': // listen-port
                portno = atoi(optarg);
                break;
            case 'n': // Maximum allowed pending connections
                maxConnections = atoi(optarg);
                break;
            case 'h': // help
                fprintf(stdout, "%s", USAGE);
                exit(0);
                break;
            default:
                fprintf(stderr, "%s", USAGE);
                exit(1);
        }
    }

    int welcomeSocket, newSocket;
    char buffer[BUF];
    
    struct sockaddr_in serverAddr;
    struct sockaddr_storage serverStorage;
      
    socklen_t addr_size;


    welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(portno);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  
      
    bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

    if(listen(welcomeSocket,5) == -1)
        printf("ERROR");
    else
        printf("LISTENING\n");

    addr_size = sizeof serverStorage;
    newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);
    
    if(read(newSocket, buffer, BUF)<0)
          	return 0;
               //strcpy(buffer,"Hello World\n");
        printf("received file = %s\n",buffer);
          //write(newSocket, buffer, strlen(buffer)+1);

        bzero(buffer,BUF);
                 //send(newSocket,buffer,5,0);
                       //      close(newSocket);
      
                     //     if(newSocket)
                           //       printf("still there");
        close(newSocket);                 
    return 0;
}
