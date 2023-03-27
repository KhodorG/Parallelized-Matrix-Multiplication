#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define M 1000
#define N 500

int A[M][N], B[N][M], C[M][M];

struct thread_arg {
    int thread_id;
    int num_threads;
};

void *matrix_multiply(void *arg) {
    struct thread_arg *targ = (struct thread_arg *) arg;
    int tid = targ->thread_id;
    int num_threads = targ->num_threads;
    int start = tid * M / num_threads;
    int end = (tid + 1) * M / num_threads;

    for (int i = start; i < end; i++) {
        for (int j = 0; j < M; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    pthread_exit(NULL);
}

int main() {
    int num_threads = 4;
    pthread_t threads[num_threads];
    struct thread_arg thread_args[num_threads];

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

    // Multiply matrices A and B using pthreads
    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);
    for (int i = 0; i < num_threads; i++) {
        thread_args[i].thread_id = i;
        thread_args[i].num_threads = num_threads;
        pthread_create(&threads[i], NULL, matrix_multiply, &thread_args[i]);
    }
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
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
