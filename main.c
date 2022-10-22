#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

#define CORRECT_ARGC_VALUE      3
#define ARGUMENT_NUMBER_MESSAGE "Only two arguments should be passed on the command line!\r\n"
#define NON_ZERO_MESSAGE        "Both arguments should be non-zero integers!\r\n"

void manageAndPrint(int x, int y, char* DL_path)
{
    void* libHandle;

    int  (*arithPtr) (int, int);
    void (*printPtr) (void);

    libHandle = dlopen(DL_path, RTLD_LAZY);

    if (libHandle == NULL)
    {
        perror("dlopen:");
    }

    arithPtr = dlsym(libHandle, "function");
    printPtr = dlsym(libHandle, "printOp");

    int z = arithPtr(x, y);

    printPtr();
    printf("%d, %d ---> %d\r\n", x, y, z);

    dlclose(libHandle);
}

int main(int argc, char** argv)
{
    if (argc != CORRECT_ARGC_VALUE)
    {
        printf(ARGUMENT_NUMBER_MESSAGE);
        exit(1);
    }

    int x = atoi(argv[1]);
    int y = atoi(argv[2]);

    if((x == 0) || (y == 0))
    {
        printf(NON_ZERO_MESSAGE);
    }

    char* mult_DL_Path = "../Dynamic_libraries/libmult.so";
    char* div_DL_Path = "../Dynamic_libraries/libdiv.so";

    manageAndPrint(x, y, mult_DL_Path);
    manageAndPrint(x, y, div_DL_Path);
}