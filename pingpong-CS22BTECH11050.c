#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include <stddef.h>

int main()
{
  int parentPipe[2],childPipe[2];//arrays to record the descriptors of the pipes
  pipe(parentPipe);// pipe in which parent writes and child reads from this
  pipe(childPipe);//pipe in which child writes and parent reads from this

  int pid = fork();//Calling fork to create a child process
  
  if(pid==0)
  {
    //child process
    close(parentPipe[1]);//close writing end of parentPipe
    
    char ch[2];//to store what is read from the parentPipe
    //read from ParentPipe
    if(read(parentPipe[0],ch,1))//if something is written into the pipe
    {
        printf("%d : received ping\n",getpid()); 
    }
    //close read end of parent pipe
    close(parentPipe[0]);

    //close read end of childPipe
    close(childPipe[0]);
    //write into the childPipe
    write(childPipe[1],"a",1);
    //close writing end of childPipe
    close(childPipe[1]);

    //exit from child process
    exit(0);

  }
  else
  {
    //parent process

    //close reading end of parentPipe
    close(parentPipe[0]);
    //write into ParentPipe
    write(parentPipe[1],"a",1);
    //close writing end of parentPipe
    close(parentPipe[1]);

    //wait for child process to finish
    wait(NULL);

    //close writing end of child pipe
    close(childPipe[1]);

    //to store what is read from child pipe
    char ch[2];
    if(read(childPipe[0],ch,1))
    {
      printf("%d : received pong\n",getpid());
    }

    //close reading end of childPipe
    close(childPipe[0]);

    //exit from parent process
    exit(0);
  }
  
}
