#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
int main(int argc,char *argv[]){
    DIR *dp;
    struct dirent *dirp;
    if(argc!=2){
        printf("format error\n");
        return 1;
    }
    if((dp=opendir(argv[1]))==NULL){
        printf("cannot open %s\n",argv[1]);
        return 1;
    }
    while((dirp=readdir(dp))!=NULL){
        printf("%s\n",dirp->d_name);
    }
    return 0;
}