#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{

  //If number of arguments is less than 2 then display error
  if(argc < 2){
    fprintf(2, "Usage: sleep num_ticks\n");
    exit(1);
  }

  //argv[1] is the number of ticks given by the user given by the user
  int n=atoi(argv[1]);  //Convert string to integer

  sleep(n);//Sleep for n number of ticks
  

  exit(0);//Exit the program
}
