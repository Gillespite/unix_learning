#include<stdio.h>
#include<unistd.h>
#define BUFFSIZE 4096

int main(){
    int n;
    char buf[BUFFSIZE];
    while ((n=read(STDIN_FILENO,buf,BUFFSIZE))>0){
        if(write(STDOUT_FILENO,buf,n)!=n){
            printf("write failed\n");
        }
    }
    printf("read failed\n");

    return 0;
}