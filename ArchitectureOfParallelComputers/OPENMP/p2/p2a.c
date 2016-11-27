#include <stdio.h>
#include <omp.h>

int main(int argc, char** argv) {
    printf("\n");

    #pragma omp parallel num_threads(10)
    {
        int id = omp_get_thread_num(); /* FIXME: Insert the id of the current thread */
        int numThreads = omp_get_num_threads(); /* FIXME: Insert total number of threads */
        printf("Hello from thread %d of %d\n", id, numThreads);
    }

    printf("\n");
    return 0;
}

