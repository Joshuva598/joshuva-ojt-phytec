#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
extern int etext, edata, end;
int I = 54;
int J;      
int main(int argc, char *argv[]){
  int i = 10;     
  int *ii = NULL; 
  printf("Page size: %d\n\n", getpagesize());

  printf("main   = %p\n",  main);
  printf("&etext = %p\n\n",   &etext);

  printf("&I(initialized var)     = %p\n",  &I);
  printf("&edata = %p\n",   &edata);
  printf("&J(uninitialized var)     = %p\n",  &J);
  printf("&end   = %p\n\n", &end);
  
  ii = (int *) malloc(sizeof(int));
  printf("ii (addr of heap)     = %p\n\n",  ii);
  
  
  printf("&argc  = %p\n",  &argc);
  printf("&i     = %p\n",  &i);
  printf("&ii    = %p\n",  &ii);
  return 0;
}
