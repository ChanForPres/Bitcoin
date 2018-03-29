#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <errno.h>
#include <sys/types.h>

int main() {

    int sockid  = socket(AF_INET,SOCK_STREAM,0); //failure as -1 
    // errno is thread local
    if (sockid < 0) 
        perror("socket not in!");
    printf("sock_id: %i",sockid );

    // char* is read only, use char[] to edit
    char const *cptr = "get wrkced";
    char **dcptr = NULL;
    char *cptr2 = NULL;
    char carr[] = "abc"; // a+b+c = 97 + 98 + 99 
    
    unsigned long int uli = strtoul(carr,&cptr2 ,10); // convert string to int
    printf("strtoul result:%lu\n", uli);

    // socket Internet address is IP address
    

    return 0;
}
