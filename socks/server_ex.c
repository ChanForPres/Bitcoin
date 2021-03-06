/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdlib.h>
 #include <stdio.h>
 #include <unistd.h>
 #include <sys/types.h>
 #include <sys/socket.h>
 #include <netinet/in.h>
 #include<sys/types.h>
 #include<sys/stat.h>
 #include <fcntl.h>    
 #include <errno.h>
 #include <string.h>

void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno, clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        perror("ERROR opening socket");

     int optval = 1;
     int error = setsockopt( sockfd, SOL_SOCKET, SO_REUSEADDR ,&optval,sizeof(optval) );
     if (error < 0) {
        perror("SETSOCKOPT FAIL: ");
     }
     
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
              perror("ERROR on binding");
     
     
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    
     if (newsockfd < 0) 
          perror("ERROR on accept");
     bzero(buffer,256);
     n = read(newsockfd,buffer,255);
     if (n < 0) 
         perror("ERROR reading from socket");
     printf("Here is the message: %s\n",buffer);
     n = write(newsockfd,"I got your message",18);
     if (n < 0)
         perror("ERROR writing to socket");
     return 0; 
}
