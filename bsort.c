/*
Author: Scott Walters
CSCI-320

This program uses omp to parallelize the bubble sort
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <time.h>



/*
This function returns a pointer to an array with all the numbers in the file as int64_t
Sets *size to be the number of numbers
*/
int64_t* Populate(char* fname, uint64_t* size){
    FILE* input = fopen(fname, "r"); //open file
    fscanf(input, "%lld", size); //scan for size **set at address of n**
    //printf("size: %lld\n", *size);
    int64_t* array = malloc((*size) * sizeof(int64_t)); //malloc for array
    //printf("size: %lld\n", *size);
    for(uint64_t ndx = 0; ndx < *size; ndx++){ //populate array
        fscanf(input, "%lld", &array[ndx]);
        //printf("%llu: %lld\n", ndx, array[ndx]);
    }
    
    fclose(input);
    return array;
}

int my_sort(int64_t* input, uint64_t size){
    //I don't know how to sort so just return 0
    for(uint64_t i = 0; i < size; i ++){
        for(uint64_t ndx = 0; ndx < size-1; ndx++){
            //printf("Is %lld > %lld?\n", input[ndx], input[ndx+1]);
            if(input[ndx] > input[ndx + 1]){
                //printf("yes!\n");
                int64_t temp = input[ndx];
                input[ndx] = input[ndx + 1];
                input[ndx + 1] = temp;
                //printf("New order: %lld, %lld\n", input[ndx], input[ndx+1]);
            } 
        }
        //printf("%lld\n", i);
    }
    return 0; 
}

/*
Suggested function to write, to check whether the array is sorted
Returns 0 if not sorted, returns 1 if sorted
*/
int is_sorted(int64_t* input, uint64_t size){
    for(uint64_t ndx = 0; ndx < size-1; ndx ++){
        if(input[ndx] > input[ndx + 1]){
            return 0;
        }

    }
    return 1;
}

int main(int argc, char** argv){
    uint64_t n; //The input size
    //printf("n address: %d\n", &n);
    int64_t* input = Populate("./numbers.txt", &n); //gets the array
    //printf("n: %d\n", n);

    struct timespec start, end;
    double time_diff;

    clock_gettime(CLOCK_MONOTONIC, &start); 

    my_sort(input, n);

    clock_gettime(CLOCK_MONOTONIC, &end);
    
    //check if it's sorted.
    int sorted = is_sorted(input, n);

    time_diff = (end.tv_sec - start.tv_sec); //Difference in seconds
    time_diff += (end.tv_nsec - start.tv_nsec) / 1e9; 

    printf("Are the numbers sorted? %s \n", sorted ? "true" : "false");
   
    printf("Time elapsed: %lf \n", time_diff);
    free(input);
}