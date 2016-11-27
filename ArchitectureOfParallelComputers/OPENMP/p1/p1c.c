#include <stdio.h>
#include <omp.h>

int main(int argc, char** argv) {
    omp_set_num_threads(2);
    #pragma omp parallel
    printf("part1\n");

    #pragma omp parallel num_threads(3)
    printf("part2\n");

    #pragma omp parallel
    printf("part3\n");

    return 0;
}

