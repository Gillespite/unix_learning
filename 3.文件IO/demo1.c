/*
学习接口 open close lseek read write
*/

#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const char* CLEAR_FILE = "rm -rf inFile outFile";
const char* CREATE_RANDOM_FILE = "dd if=/dev/urandom of=./inFile bs=1k count=1";
const char* CMP_FILE = "md5sum inFile && md5sum outFile";

const int32_t BUFFSIZE = 30;

void closeFile(int32_t fd)
{
    if (fd > 0) {
        close(fd);
    }
    return;
}

void openFile(int32_t* fd, const char* fileName)
{
    if ((*fd = open(fileName, O_RDWR)) > 0) {
        printf("open file %s success, fd=%d\n", fileName, *fd);
        return;
    } else if ((*fd = open(fileName, O_RDWR | O_CREAT)) > 0) {
        printf("create file %s success, fd=%d\n", fileName, *fd);
        return;
    }
    return;
}

void checkCurOffset(const int32_t fd)
{
    off_t curOffset = lseek(fd, 0, SEEK_CUR);
    printf("fd:%d offset:%ld\n", fd, curOffset);
    return;
}

void copyFile(const int32_t in, const int32_t out)
{
    char* buf[BUFFSIZE];
    int32_t curSize;
    while ((curSize = read(in, buf, BUFFSIZE)) > 0) {
        if (write(out, buf, curSize) != curSize) {
            printf("copy file failed\n");
            return;
        }
        checkCurOffset(in);// read 和 write 会改变offset
        checkCurOffset(out);
    }
    printf("copy file success\n");
}

void msleep(const int32_t time)
{
    usleep(1000 * time);
}

int main()
{
    int32_t in;
    int32_t out;
    int32_t ret;
    system(CLEAR_FILE);
    system(CREATE_RANDOM_FILE);

    openFile(&in, "./inFile");
    openFile(&out, "./outFile");

    copyFile(in, out);

    closeFile(in);
    closeFile(out);

    system("ls -l");
    // TODO 概率性permission denied 后续解决
    system(CMP_FILE);
    system(CLEAR_FILE);
    return 0;
}
/*
permission denied 时
-rwxrwxr-x 1 jill jill 16688 Sep 30 04:23 demo1
-rw-rw-r-- 1 jill jill  1802 Sep 30 04:23 demo1.c
-rw-rw-r-- 1 jill jill  1024 Sep 30 04:23 inFile
-rw-rw-r-- 1 jill jill   405 Sep 30 02:25 ls.c
---x-wSr-T 1 jill jill  1024 Sep 30 04:23 outFile

正常时
-rwxrwxr-x 1 jill jill 16688 Sep 30 04:24 demo1
-rw-rw-r-- 1 jill jill  2086 Sep 30 04:24 demo1.c
-rw-rw-r-- 1 jill jill  1024 Sep 30 04:24 inFile
-rw-rw-r-- 1 jill jill   405 Sep 30 02:25 ls.c
-rw--w-r-T 1 jill jill  1024 Sep 30 04:24 outFile
*/