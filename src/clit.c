// clit.c
// THIS CODE IS LICENSED UNDER THE MIT LICENSE
// SEE License IN ROOT DIRECTORY FOR MORE INFORMATION

#include <stdio.h>
#include <string.h>

#define CLIT_VERISON "Clit verison 1.0.0"

void show_version(){
    printf("%s\n", CLIT_VERSION);
}

void show_help(){
    printf("usage:\n");
    printf("-h shows this help screen\n");
    printf("-v shows the current version\n");
}

int main(int argc, char *argv[]){
    if(argv >= 2){
        if(strcmp(argv[1], "-h") == 0){
            show_help();
            return 0;
        }else if(strcmp(argv[1], "-v") == 0){
            show_version();
            return 0;
        }else{
            printf("Invalid argument: %s\n", argv[1]);
            return 1;
        }
    } else {
        show_help();
        return 1;
    }
}
