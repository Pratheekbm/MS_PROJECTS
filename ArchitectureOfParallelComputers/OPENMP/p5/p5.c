#include <stdio.h>
#include <omp.h>
int main(int argc, char** argv) {
        int a = 20, i, id;
        
		#pragma omp parallel for private(i, id) lastprivate(a)// FIXME: Use private, lastprivate, firstprivate
		for (i = 0; i < 3; i++){
			id = omp_get_thread_num();
			printf ("Value inside parallel region from Thread ID: %d, a = %d \n", id, a);
		}
		
		printf("Value outside parallel region, a = %d \n", a);
		
        return 0;
}
