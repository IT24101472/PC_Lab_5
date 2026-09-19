#include <stdio.h>
#include <omp.h>

#define N 1000000
#define STRIP_SIZE 8

float A[N];
float B[N];
float C[N];

int main()
{
    // Initialize arrays
    for (int i = 0; i < N; i++)
    {
        A[i] = 2.0f;
        B[i] = 3.0f;
    }

    double start = omp_get_wtime();

    #pragma omp parallel for
    for (int ii = 0; ii < N; ii += STRIP_SIZE)
    {
        int end = ii + STRIP_SIZE;

        if (end > N)
            end = N;

        #pragma omp simd
        for (int i = ii; i < end; i++)
        {
            C[i] = A[i] * B[i];
        }
    }

    double stop = omp_get_wtime();

    printf("C[0] = %.2f\n", C[0]);
    printf("C[999999] = %.2f\n", C[N - 1]);

    printf("Execution Time = %f seconds\n", stop - start);

    return 0;
}
