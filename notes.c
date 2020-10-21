// Class notes 10/7/20
/*
Open MP
Set of specifications
Technically not just a library
Requires compiler support
Look at website for documentation
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


int main(int argc, char** argv){
    #pragma omp parallel
    {
        printf("hello world\n");
    }
    return 0;
}