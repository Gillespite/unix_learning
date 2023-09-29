#include<stdio.h>
#include<unistd.h>
#define BUFFSIZE 4096

int main(){
    int n;
    char buf[BUFFSIZE];
    //read的返回值是读到的字节数
    //write的返回值是写入的字节数
    while ((n=read(STDIN_FILENO,buf,BUFFSIZE))>0){
        if(write(STDOUT_FILENO,buf,n)!=n){
            printf("write failed\n");
        }
    }
    printf("read failed\n");
    return 0;
}