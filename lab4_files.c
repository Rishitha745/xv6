#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"
#include "kernel/syscall.h"
#include "kernel/memlayout.h"
#include "kernel/riscv.h"


#define ROLL_NUMBER "CS22BTECH11050" 
int main(int argc, char *argv[])
{

    //If number of arguments is less than 2 then display error
    if(argc < 3){
        fprintf(2, "Usage:  %s <filename> <filesize>\n",argv[0]);
        exit(1);
    }

    char * filename=argv[1];
    uint64 filesize = string_uint64(argv[2]); 
    struct stat st;
  
    int fd = open(filename, O_CREATE|O_WRONLY);
    if(fd < 0){
        printf("%s: open failed\n", filename);
        exit(1);
    }
    else{
        //printf("file opened\n");
        fstat(fd,&st);
    }
    uint64 current_size = st.size;

    while (current_size < filesize) {
        if(current_size+BSIZE<=filesize){
            int n = write(fd, "CS22BTECH11050", BSIZE);
            if (n < 0) {
                printf("Error writing to file\n");
                close(fd);
                exit(1);
            } 
        }
        else{
            int n = write(fd, "CS22BTECH11050", filesize-current_size);
            if (n < 0) {
                printf("Error writing to file\n");
                close(fd);
                exit(1);
            }
        }

        current_size += BSIZE;
    }
    close(fd);
    fd = open(filename, O_RDWR);
    if (fd < 0) {
        fprintf(1, "Error: Unable to open file\n");
        exit(0);
    }

    struct stat st2;
    if(fstat(fd,&st2)<0){
        fprintf(1, "Error: Unable to get file information\n");
        exit(0);
    }

    int inode_num=st.ino;
    printf("Properties:inode number %d dev %d type %d nlink %d size %d",inode_num,st2.dev,st2.type,st2.nlink,st2.size);
    for (int i = 0; i*BSIZE < filesize; i++)
    {
        printf("\nBlock number %d \n",i);
        char buff[BSIZE];
        memset(buff,'\0',BSIZE);
        printf("Block content\n");
        read(fd,buff,BSIZE);
        printf("%s",buff);
    }
    printf("\n");
    

}