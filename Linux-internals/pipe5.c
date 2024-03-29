
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
   int status;
   int fd1[2];
   int fd2[2];
   pipe(fd1);
   pipe(fd2);


   if (fork() == 0){
      dup2(fd1[1], 1);
      close(fd1[0]);
      close(fd2[0]);
      close(fd2[1]);
      execlp("man","man", "ls", NULL);
   }

   else if (fork() == 0){
      dup2(fd1[0], 0);
      dup2(fd2[1], 1);
      close(fd1[1]);
      close(fd2[0]);
      execlp("grep","grep","ls", NULL);
   }

   else if (fork() == 0){
      dup2(fd2[0], 0);
      close(fd1[0]);
      close(fd1[1]);
      close(fd2[1]);
      execlp("wc","wc", NULL);
   }

   close(fd1[0]);
   close(fd1[1]);
   close(fd2[0]);
   close(fd2[1]);
   for(int i=0;i<3;i++)
      wait(NULL);
   printf("Parent is done with the three children...\n");
   return 0;
}
