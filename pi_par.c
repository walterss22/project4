/*
Author: Scott Walters
CSCI-320

This program parallelizes the estimation of pi using open mp.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h> //to use uint_64
#include <time.h> //to use clock
#include <math.h> //to use pow function
#include <omp.h> //to use openmp

uint64_t TERMS = 1000000;
int THREADS = 10;

long double* multiplier;

void* find_pi(long double* number ){
    //C doesn't actually have Pi as a constant, but...
    //Most modern CPUs actually have an instruction to just load Pi into a register!
    //Some inline assembly here. This should work for all versions of GCC...
    uintptr_t rank = omp_get_thread_num();
    THREADS = omp_get_num_threads();
    //long double Pi = 4; //initialize Pi
    long double mult = 0; //initialize multiplier
    int block = TERMS/THREADS; //get block size
    uint64_t start = block * rank;
    uint64_t end = block * (rank + 1);
    if(rank == THREADS -1){
        end = TERMS;
    }

    for (int i = start; i < end; i++){
        mult += pow(-1, i) * (1.0 / ((2 * i) + 1)); //use estimation algo
    }
    
    #pragma omp critical
    {
        *multiplier = *multiplier + mult;
    }
    return NULL; //return NULL
}

int main(int argc, char** argv){
    struct timespec start, end; //structs used for timing purposes, it has two memebers, a tv_sec which is the current second, and the tv_nsec which is the current nanosecond.
    double time_diff;
    long double pi = 0;
    *multiplier = 0;

    //gather command line arg
    if(argc >= 2){
        TERMS = strtoull(argv[1], NULL, 10);
        if(argc > 2){
            THREADS = strtoull(argv[2], NULL, 10);
        }
    }
    
    //get time taken
    clock_gettime(CLOCK_MONOTONIC, &start); //Start the clock!
    #pragma omp parallel num_threads(THREADS)
    {
        find_pi(&multiplier);
    }

    pi *= *multiplier;

    clock_gettime(CLOCK_MONOTONIC, &end);   //Stops the clock!

    time_diff = (end.tv_sec - start.tv_sec); //Difference in seconds
    time_diff += (end.tv_nsec - start.tv_nsec) / 1e9; //Difference in nanoseconds

    //print results
    printf("The time taken is %f \n", time_diff);
    printf("%lld terms used.\n", TERMS);
    printf("Pi is %.20Lf\n", pi);
    return 0;
}