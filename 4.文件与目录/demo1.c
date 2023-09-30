/*
 */

#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

const char* CREATE_RANDOM_FILE = "dd if=/dev/urandom of=./file1 bs=1k count=1";
const char* CLEAR_FILE = "rm -rf file1";

void checkStat(const char* path)
{
    struct stat buf;
    char* tmp;
    if (stat(path, &buf) < 0) {
        printf("get stat err, path%s\n", path);
    }

    if (S_ISREG(buf.st_mode)) {
        tmp = "regular";
    } else if (S_ISDIR(buf.st_mode)) {
        tmp = "directory";
    } else if (S_ISCHR(buf.st_mode)) {
        tmp = "character special";
    } else if (S_ISBLK(buf.st_mode)) {
        tmp = "block special";
    } else if (S_ISFIFO(buf.st_mode)) {
        tmp = "fifo";
    } else if (S_ISLNK(buf.st_mode)) {
        tmp = "symbolic link";
    } else if (S_ISSOCK(buf.st_mode)) {
        tmp = "socket";
    } else {
        tmp = "unknown";
    }

    printf("%s is %s\n", path, tmp);
    return;
}

int main()
{
    system(CLEAR_FILE);
    system(CREATE_RANDOM_FILE);

    checkStat("./file1");
    checkStat("/etc/passwd");
    checkStat("/etc");
    checkStat("/dev/log");
    checkStat("/dev/tty");
    checkStat("/dev/sr0");
    checkStat("/dev/cdrom");
    
    system(CLEAR_FILE);
    return 0;
}