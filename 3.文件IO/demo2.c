/*
*/

#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const char* CREATE_RANDOM_FILE = "dd if=/dev/urandom of=./file1 bs=1k count=1";
const char* CLEAR_FILE = "rm -rf file1";

int main()
{
    system(CLEAR_FILE);
    system(CREATE_RANDOM_FILE);

    

    system(CLEAR_FILE);
    return 0;
}