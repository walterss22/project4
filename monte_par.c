/*
Author: Scott Walters
CSCI-320

This program is a parallel implementation
of the Monte Carlo estimation of pi.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h> //to use uint_64
#include <time.h> //to use clock
#include <math.h> //to use pow function
#include <omp.h> //to thread

int64_t SAMPLES = 1000000;
int THREADS = 10;
double* results;

void* estimate(int number){
    srand(time(NULL));
    uintptr_t rank = (uintptr_t) number;
    double x = 0;
    double y = 0;
    uint64_t hits = 0;
    for(uint64_t i = 0; i < SAMPLES; i++){
        x = ((double)rand()/(double)RAND_MAX); //cast to doubles, divide by RAND_MAX 
        y = ((double)rand()/(double)RAND_MAX);
        if(sqrt(pow(x,2) + pow(y,2) <= 1 )){
            hits +=1;
        }
    }
    printf("%f\n", ((double)hits / (double)(SAMPLES*THREADS)));
    results[rank] = ((double)hits/(double)(SAMPLES*THREADS));
    return NULL;
}

int main(int argc, char** argv){
    struct timespec start, end; //structs used for timing purposes, it has two memebers, a tv_sec which is the current second, and the tv_nsec which is the current nanosecond.
    double time_diff;
    double est = 0;

    if(argc >= 2){
        SAMPLES = strtoull(argv[1], NULL, 10);
        if(argc > 2){
            THREADS = strtoull(argv[2], NULL, 10);
        }
    }
    SAMPLES /= THREADS;
    //get time taken
    clock_gettime(CLOCK_MONOTONIC, &start); //Start the clock!
    results = malloc(sizeof(double) * THREADS);
    #pragma omp parallel num_threads(THREADS)
    {
        estimate(omp_get_thread_num());
    }
    //gather results
    for(int i = 0; i < THREADS; i++){
        est += results[i];
    }
    printf("collection of floats: %f", est);

    est*= 4;

    clock_gettime(CLOCK_MONOTONIC, &end);   //Stops the clock!
    time_diff = (end.tv_sec - start.tv_sec); //Difference in seconds
    time_diff += (end.tv_nsec - start.tv_nsec) / 1e9; //Difference in nanoseconds

    //print results
    printf("The time taken is %f \n", time_diff);
    printf("%lld terms used.\n", SAMPLES);
    printf("Pi is %.20f\n", est);
    return 0;
}   
