#include <stdio.h>
#include <stdlib.h>

extern int hello_in_asm();


int size;

int main(int argc, char* argv[]) {

    hello_in_asm();
    printf("ojbk\n");
    return 0;
}