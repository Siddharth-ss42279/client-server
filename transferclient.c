#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>

#define BUFFSIZE 6

#define USAGE                                                                 \
"usage:\n"                                                                    \
"  transferclient [options]\n"                                                \
"options:\n"                                                                  \
"  -s                  Server (Default: localhost)\n"                         \
"  -p                  Port (Default: 8888)\n"                                \
"  -o                  Output file (Default foo.txt)\n"                       \
"  -h                  Show this help message\n"

/* Main ========================================================= */
int main(int argc, char **argv) {
    int option_char = 0;
    char *hostname = "localhost";
    unsigned short portno = 8888;
    char *filename = "foo.txt";

    // Parse and set command line arguments
    while ((option_char = getopt(argc, argv, "s:p:o:h")) != -1) {
        switch (option_char) {
            case 's': // server
	        hostname = optarg;
                break;
            case 'p': // listen-port
                portno = atoi(optarg);
                break;
            case 'o': // filename
                filename = optarg;
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

    /* Socket Code Here */
    int sockfd = 0;
    int bytesReceived = 0;
    char recvBuff[BUFFSIZE];
    memset(recvBuff, '0', sizeof(recvBuff));
    struct sockaddr_in serv_addr;

    // Creating a socket 
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0))< 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    }

    // Initialize sockaddr_in data structure 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portno); // port
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Attempt a connection 
    if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
    {
        printf("\n Error : Connect Failed \n");
        return 1;
    }

    // Create file where data will be stored 
    FILE *fp;
    fp = fopen("output_file.txt", "w");
    if(NULL == fp)
    {
        printf("Error opening file");
        return 1;
    }

    // Receive data in chunks of 6 bytes 
    while((bytesReceived = read(sockfd, recvBuff, BUFFSIZE)) > 0)
    {
        printf("Bytes received %d\n",bytesReceived);    
        // recvBuff[n] = 0;
        fwrite(recvBuff, 1,bytesReceived,fp);
    }

    if(bytesReceived < 0)
    {
        printf("\n Read Error \n");
    }    

    return 0;
}
