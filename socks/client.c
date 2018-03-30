#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>

#ifndef   NI_MAXHOST
#define   NI_MAXHOST 1025
#endif

int main(int argc, char *argv[]) {

    if (argc < 3) {
        fprintf(strerror, "ERR: ARG TOO FEW");
        exit(0);
    }
    struct host_ent *server; //contains host info

    // defined in netdb.h

    // client has to a) create socket b) connect to server c) send/rcv data
    int sock_fd = socket(AF_INET, SOCK_STREAM,0); //sock create
    if (sock_fd < 0)
        strerror(errno);
    else
        printf("socket created...\n");

      int portno, n;
      portno = atoi(argv[2]); //string -> int

      // argv[] = client cheerios 51717
       struct addrinfo *server_info, *info_iter;
    int addrinfo = getaddrinfo(argv[1],argv[2],NULL ,server_info); // replace gethostbyname
    if (addrinfo != 0) {
      fprintf(stderr, "error in getaddrinfo: %s\n", gai_strerror(addrinfo));
      exit(EXIT_FAILURE);
    }
    // loop over and get name info
    for (info_iter = addrinfo; info_iter!= null; info_iter->ai_next) {
      char hostname[NI_MAXHOST];
      error = getnameinfo(info_iter->ai_addr, info_iter->ai_addrlen,
              hostname, NI_MAXHOST, NULL, 0, 0);
          if (error != 0) {
                 fprintf(stderr, "error in getnameinfo: %s\n", gai_strerror(error));
                   continue;
          }
          // test host name print
          if (*hostname != '\0')
          printf("hostname: %s\n", hostname);

    }
    /*
           int getaddrinfo(const char *node, const char *service,
                           const struct addrinfo *hints,
                           struct addrinfo **res);
    */



    struct sockaddr_in  sock_addr;
    /* sockaddr has these fields:
     sa_family_t    sin_family
    in_port_t      sin_port
    struct in_addr sin_addr
    unsigned char  sin_zero[8]
     */
     memset((void*)&sock_addr , 0,sizeof(sock_addr) );//void *memset(void *s, int c, size_t n);

    memcpy((void*) sock_addr, (void*) addrinfo,sizeof(addrinfo) ); //dest, src, size to copy in bytes
    sock_addr.sin_family=  AF_INET;
    sock_addr.sin_port = htons(22000) ; //port number = allows any port to connect


    // client doesn't bind to a port, only server does
    // use connect instead
    int connect_id = connect(sock_fd,(struct sockaddr*)&sock_addr,sizeof(sock_addr) ); // connect to address of server, connect(socket_id, sockaddr, addr_len)
    if (connect_id < 0)
        strerror(errno);
    else
        printf("connection established...\n");
    // send/rcv data
    // read/write syscalls

    char cbuff[] = "fg";
    int fd = open("./a.txt", O_RDWR|O_EXCL); // read/write + don't replicate existing file
    read(fd, (void*)cbuff, sizeof(cbuff) ); // read from buffer to fd

    freeaddrinfo(server_info);

    if ( close(sock_fd) < 0 )
        printf("error: not closed\n");


    return 0;
}
