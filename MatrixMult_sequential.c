#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M 1000 // Number of rows and columns in A and C
#define N 500 // Number of columns in A and rows in B

int main() {
    int A[M][N], B[N][M], C[M][M]; // Define matrices A, B, and C
    srand(time(NULL)); // Initialize random seed
    
    // Generate random values for matrix A
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() % 10;
        }
    }
    
    // Generate random values for matrix B
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            B[i][j] = rand() % 10;
        }
    }
    
    // Perform matrix multiplication
    clock_t start = clock(); // Start timer
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            int sum = 0;
            for (int k = 0; k < N; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
    clock_t end = clock(); // End timer
    
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC; // Calculate execution time in seconds
    double time_ms = time_spent * 1000; // Convert to milliseconds
    
    // Print the execution time
    printf("Execution time: %f ms\n", time_ms);
    
    return 0;
}
