#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>



/*
This function returns a pointer to an array with all the numbers in the file as int64_t
Sets *size to be the number of numbers
*/
int64_t* Populate(char* fname, uint64_t* size){
    FILE* input = fopen(fname, "r");

    size = malloc(sizeof(uint64_t));
    fscanf(input, "%d", &size);
    printf("File name: %s\n", fname);
    printf("size: %d\n", size);
    int64_t* array = malloc(sizeof(int));
    printf("malloc done\n");
    for(uint64_t ndx = 0; ndx < *size; ndx++){
        fscanf(input, "%d", &array[ndx]);
        printf("scanned %d\n", ndx);
        //printf("%llu : %lld", ndx, array[ndx]);
    }
    
    fclose(input);
    return array;
}

int my_sort(int64_t* input, uint64_t size){
    //I don't know how to sort so just return 0
    return 0;
}

/*
Suggested function to write, to check whether the array is sorted
Returns 0 if not sorted, returns 1 if sorted
*/
int is_sorted(int64_t* input, uint64_t size){
    //Probably not sorted so...
    return 0;
}

int main(int argc, char** argv){
    uint64_t n; //The input size
    int64_t* input = Populate("./numbers.txt", &n); //gets the array

    my_sort(input, n);
    
    //check if it's sorted.
    int sorted = is_sorted(input, n);
    printf("Are the numbers sorted? %s \n", sorted ? "true" : "false");
   
    printf("Time elapsed: %lf \n", 0.0);
    free(input);
}