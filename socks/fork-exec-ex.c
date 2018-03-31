#include  <stdio.h>
#include  <sys/types.h>
#include <unistd.h>
#include <fcntl.h> // O_CREAT, O_APPEND etc. defined here
#include <stdlib.h>
#include <string.h>


void  parse(char *line, char **argv)
{
     while (*line != '\0') {       /* if not the end of line ....... */
          while (*line == ' ' || *line == '\t' || *line == '\n')
               *line++ = '\0';     /* replace white spaces with 0    */
          *argv++ = line;          /* save the argument position     */
          while (*line != '\0' && *line != ' ' &&
                 *line != '\t' && *line != '\n')
               line++;             /* skip the argument until ...    */
     }
    **argv = '\0';                 /* mark the end of argument list  */
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
         // 1st arg: filename, 2nd: ptr to str pts 
         if (execvp(*argv, argv) < 0) {     /* execute the command  */
               printf("*** ERROR: exec failed\n");
               exit(1);
          }
     }
     else {                                  /* for the parent:      */
          while (wait(&status) != pid);       /* wait for completion  */

     }
}

int  main(void)
{

     char  line[] = "bbb";             /* the input line                 */
     //array of pointers
     char  *argv[64];
      memset(&argv  , 0,64* sizeof(char*) );              /* the command line argument      */

     while (1) {                   /* repeat until done ....         */
          printf("Shell -> ");     /*   display a prompt             */

          // fgets(line, 5 ,stdin );              /*   read in the command line     */
          line[strcspn(line, "\r\n")] = 0;

          printf("\n");
          parse(line, argv);       /*   parse the line               */
          if (strcmp(argv[0], "exit") == 0)  /* is it an "exit"?     */
               exit(0);            /*   exit if it is                */
          execute(argv);           /* otherwise, execute the command */
     }
     return 0;
}
