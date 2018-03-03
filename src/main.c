#include <stdlib.h>
#include <stdio.h>

int main(int argc, char ** argv) {
    int ret;

    //check for shell
    ret = system(0);
    printf( "Shell is%s avalible\n", ret ? "" : " not");

    return  0;
}
