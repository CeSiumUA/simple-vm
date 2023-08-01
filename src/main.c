#include "main.h"

int main(int argc, char **argv){
    printf("Welcome to LC-3 vm!\r\n");

    printf("Provided arguments:\r\n");
    for(int i = 0; i < argc; i++){
        printf("\t%s\r\n", argv[i]);
    }
}