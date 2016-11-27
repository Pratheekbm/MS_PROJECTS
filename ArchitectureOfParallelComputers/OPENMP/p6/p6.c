#include <stdio.h>
#include <omp.h>
#define ITERATIONS 0x10000000

int main(int argc, char** argv) {
        int i, tid = 0, numThreads = 0;
        double j;
        double pi;
	double *temp;
        pi = 0;
	double start = omp_get_wtime();
	//#pragma omp parallel private(i, j, tid)
	{
		numThreads = omp_get_num_threads();
		//#pragma omp single
		temp = (double*)malloc(numThreads * sizeof(double));
		//#pragma omp for
        	for ( i = 0 ; i < ITERATIONS; i++) {
			tid = omp_get_thread_num();
			j = (double)(i);
                	if ( (i % 2) == 0 )
                	        temp [tid] += 1./(1.+j*2);
               		else
                        	temp[tid] += -1./(1.+j*2);
		}
	}

	//#pragma omp parallel for reduction (+:pi) 
	for (i = 0; i < numThreads; i ++) {
		pi += temp[i];
	}

        printf("%lf\n", pi*4);
	double end = omp_get_wtime();
	printf("Time = %lf\n", end - start);
        return 0;
}
