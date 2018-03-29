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
 
 #define SERV_PORT 5432
 
 int main(int argc, char *argv[]) {

     if (argc < 2) {
         fprintf(stderr, "NO PORT PROVIDED\n"); // too few args
         exit(1); // exit error, user must pass port # 
     } 
     int cli_add, cli_len, portno; // address of client, size of client address, server port connection
     int buff_ct; // store amt read/write 

     struct sockaddr_in serv_addr,cli_addr; // server address , client address
     memset(&serv_addr,0 ,sizeof(serv_addr) );
     /*

      *
      struct sockaddr_in
      sa_family_t    sin_family
    in_port_t      sin_port
    struct in_addr sin_addr -> contains ulong s_addr 
    unsigned char  sin_zero[8]
          */

     portno = atoi(argv[1]); //2nd arg stdin 

     int sock_fd = socket(AF_INET,SOCK_STREAM  ,0); // create socket: address domain(AF_INET) , socket type
     serv_addr.sin_family = AF_INET; // address family code
    
     // IP address is "lower level" : identify system in network, port identifies service in system
     serv_addr.sin_addr.s_addr = htons(INADDR_ANY); // IP Address of host , machine where server is running  
     serv_addr.sin_port = htons(portno); //htons converts from host byte order to port # in network byte order
     
     // bind socket to requested address 
     // remember to cast address to correct type
     // last arg - size of address to bind to 
     bind(sock_fd,(struct sockaddr *)&serv_addr ,sizeof(serv_addr) );

     // start socket listening to bound address
     int ilisten = listen(sock_fd, 10); // queue size = 10
     //accept connection, block process until client connected
     if (ilisten < 0) {
         fprintf(stderr, "SOCKET_LISTEN ERR "); // listen failed 
        }
     
     // block process until accept incoming request from client
     // returns new file descriptor, further communication on new fd  
     int new_sockfd = accept(sock_fd,(struct sockaddr*)&cli_add ,sizeof(&cli_add) );
     if (new_sockfd < 0)
         fprintf(stderr, "UNABLE TO ACCPT CLI");

     // after accepted, write the output
     // read from socket using buffer 
     char buff[11];
     memset((void*)buff, 0, sizeof(buff));
     int iread = read(new_sockfd ,(void*)buff, 10 ); //read from client max 10 bytes 
     // read blocks until write() from client 
     // after reading finished, check if success
     if (iread < 0) 
         fprintf(stderr, "BUFFER READ ERR!");
     printf("CLIENT MSG: %s\n",buff);
     iread = write("MSG RCVD SUCCESS"); // write msg to client
     if (iread < 0)
         fprintf(stderr, "UNABLE WRITE->CLIENT");

     close(sock_fd);

     return 0;



 }
