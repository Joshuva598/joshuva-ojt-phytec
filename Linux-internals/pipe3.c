
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define SIZE 1024
int main(){
   int fd1[2];
   int fd2[2];
   pipe(fd1);
   pipe(fd2);

   pid_t cpid = fork();

   if (cpid == 0) {
      close(fd1[0]);
      close(fd2[1]);
      char childbuff[SIZE];
      memset(childbuff, '\0',SIZE);
      const char *msgfromchild = "Child Name";

      int n = read(fd2[0],childbuff,SIZE);
      printf("\nI am child.");
      printf("\nParent asked: "); 
      fflush(stdout);
      write(1,childbuff,n);    

      write(fd1[1],msgfromchild,strlen(msgfromchild));
      exit(0);
   }

   else {
      close(fd1[1]);
      close(fd2[0]);
      char parentbuff[SIZE];
      memset(parentbuff, '\0',SIZE);
      const char * msgfromparent = "What is your name child?";

      write(fd2[1], msgfromparent,strlen(msgfromparent));

      int n = read(fd1[0],parentbuff,SIZE); 
      printf("\n\nI am parent, and have received my child's name.");
      printf("\nWelcome Mr. ");
      fflush(stdout);
      write(1,parentbuff,n);
      printf("\n");
	   exit(0);
   }
}
