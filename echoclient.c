#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <getopt.h>

/* Be prepared accept a response of this length */
#define BUF 16

#define USAGE                                                                 \
"usage:\n"                                                                    \
"  echoclient [options]\n"                                                    \
"options:\n"                                                                  \
"  -s                  Server (Default: localhost)\n"                         \
"  -p                  Port (Default: 8888)\n"                                \
"  -m                  Message to send to server\n"                           \
"  -n                  Maximum pending connections\n"                         \
"  -h                  Show this help message\n"                              \

/* error ======================================================== */
void error(char *s)
{
    perror(s);
    exit(1);
}

/* Main ========================================================= */
int main(int argc, char **argv) {
    int option_char = 0;
    char *hostname = "localhost";
    unsigned short portno = 8888;
    char *message = "Hello World!";
    int maxnpending = 5;

    // Parse and set command line arguments
    while ((option_char = getopt(argc, argv, "s:p:m:n:h")) != -1) {
        switch (option_char) {
            case 's': // server
                hostname = optarg;
                break;
            case 'p': // listen-port
                portno = atoi(optarg);
                break;
            case 'm': // server
                message = optarg;
                break;
            case 'n': // server
                maxnpending = atoi(optarg);
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
      int clientSocket;
      char buffer[BUF];
      
      struct sockaddr_in serverAddr;
      socklen_t addr_size;

      clientSocket = socket(PF_INET, SOCK_STREAM, 0);
      serverAddr.sin_family = AF_INET;
      serverAddr.sin_port = htons(portno);
      serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
      memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

      addr_size = sizeof serverAddr;
      connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);
         
          //fgets(buffer, BUF, stdin);
      write(clientSocket, message, strlen(message)+1);
         // bzero(message,BUF);       
         // read(clientSocket, message, BUF);
         // printf("Data received: %s",message);
         // bzero(buffer,BUF);

    return 0;
}
