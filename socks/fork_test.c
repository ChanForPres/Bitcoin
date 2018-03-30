 #include  <stdio.h>
 #include  <sys/types.h>
 #include <unistd.h>
 #include <fcntl.h> // O_CREAT, O_APPEND etc. defined here
 #include <stdlib.h>
 #include <string.h>
 
 
 void parse(char *line, char **argv){
     
   printf("a"); 
   argv[0] = line; // pass by value check  
   printf("\n%s\n",argv[0]);
   **argv = '\0'; // segfault here?

 }

int main() {
    char line[] = "a";
    char *argv[64]; // array of 64 char ptrs 
    

    parse(line,argv);

    return 0;
}
