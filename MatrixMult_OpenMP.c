#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <sys/time.h>

#define M 1000
#define N 500

int A[M][N], B[N][M], C[M][M];

int main() {
    int num_threads = 4;
    omp_set_num_threads(num_threads);

    // Initialize matrices A and B with random values
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() % 100;
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            B[i][j] = rand() % 100;
        }
    }

    // Multiply matrices A and B using OpenMP
    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);
    #pragma omp parallel for
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    gettimeofday(&end_time, NULL);

    // Print the resulting matrix C
    printf("Matrix C:\n");
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    // Print the execution time
    double total_time = (end_time.tv_sec - start_time.tv_sec) * 1000.0 +
                        (end_time.tv_usec - start_time.tv_usec) / 1000.0;
    printf("Execution time: %f milliseconds\n", total_time);

    return 0;
}

