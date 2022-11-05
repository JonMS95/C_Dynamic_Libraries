#include "main.h"

/*
@brief Takes the two numbers that have been passed by command line and the path
to the library that's meant to be dynamically loaded.
@param x First number.
@param y Second number.
@param DL_path Path to the dynamic library.
@return Void.
*/
void manageAndPrint(int x, int y, char* DL_path)
{
    void* libHandle;

    int  (*arithPtr) (int, int);
    void (*printPtr) (void);

    libHandle = dlopen(DL_path, RTLD_LAZY);

    if (libHandle == NULL)
    {
        perror("dlopen");
    }

    arithPtr = dlsym(libHandle, "function");
    printPtr = dlsym(libHandle, "printOp");

    int z = arithPtr(x, y);

    printPtr();
    printf("%d, %d ---> %d\r\n", x, y, z);

    dlclose(libHandle);
}

/*
@brief Main function. Program's entry point.
*/
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

    char* mult_DL_Path = MULT_SO_PATH;
    char* div_DL_Path = DIV_SO_PATH;

    manageAndPrint(x, y, mult_DL_Path);
    manageAndPrint(x, y, div_DL_Path);
}