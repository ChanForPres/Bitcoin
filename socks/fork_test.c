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
   printf("\n%c\n",argv[0][0]);

 }


 void  execute(char **argv)
 {
      pid_t  pid;
      int    status;

      if ((pid = fork()) < 0) {     /* fork a child process           */
           printf("*** ERROR: forking child process failed\n");
           exit(1);
      }
      else if (pid == 0) {          /* for the child process:         */
          // execvp expects arr of str ptrs terminated by NULL ptr
          if (execvp(*argv, argv) < 0) {     /* execute the command  */
                printf("*** ERROR: exec failed\n");
                exit(1);
           }
      }
      else {                                  /* for the parent:      */
           while (wait(&status) != pid);       /* wait for completion  */

      }
 }

int main() {
    char line[] = "a";
    char *argv[64]; // array of 64 char ptrs


    parse(line,argv);

    return 0;
}
