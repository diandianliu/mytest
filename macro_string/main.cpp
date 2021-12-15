
#include <stdio.h>
// demoConfig.h文件是cmake生成的
#include "macroConfig.h"

int main(int argc, char* argv[]){

    printf("%s version: %d.%d \n", argv[0], demo_VERSION_MAJOR, demo_VERSION_MINOR);
    printf("%s version: %s \n", argv[0], demo_VERSION_STR);
}
