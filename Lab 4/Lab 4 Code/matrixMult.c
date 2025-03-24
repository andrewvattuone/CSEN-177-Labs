//Name: Andrew Vattuone
//Date: 1/29/25  
//Title: Lab4 – Developing multi-threaded applications - Step 3
/*Description: 
    Generates 2 matrices, and then computes their product. Matrix A is an NxM matrix and matrix B is an MxL matrix. The 
    entries in matrix A and matrix b are all randomly generated integers between 0 and 9. The product wil be an NxL 
    matrix, called matrix C. Separate threads are created to calculate each row of C, which theoretically would allow for the 
    parallel computation of each row since each row thread would run at the same time, which would speed up runtime 
    (we only have single-core CPUs though so it won't have much of an impact). The individual entries of C are calculated
    using conventional matrix multiplication rules. Since the directions said to make each matrix 256x256 I did it, but
    the output is too large to see on the terminal window, so change all matrices to 2x2 matrices if you want to see all
    the values of A and B and the product matrix C.
*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>

// change all these values to 2 if you want to see a smaller output
#define N 256
#define M 256
#define L 256

int matrixA[N][M];
int matrixB[M][L];
int matrixC[N][L];

// calculates one row of the product matrix C based on the inputted row number, and stores it in the corresponding row of matrixC
void *rowThreads(void *arg) 
{
    pthread_t colThreads[L];

    // goes through each of the columns of B and uses each element inside these columns to calculate the specified row of the product matrix C
    for (int j = 0; j < L; j++)
    {
        int temp = 0;
        // calculates the value of one column of the specified row of the product matrix C using the values from the corresponding column of B
        for (int k = 0; k < M; k++)
        {
            temp += matrixA[(int)(size_t)arg][k] * matrixB[k][j];
        }
        matrixC[(int)(size_t)arg][j] = temp;
    }
    return (NULL);
}


int main() {
    pthread_t threads[N];

    srand(time(NULL)); // initializes seed for random number generation

    // generates an NxM matrix A, with each entry being a random number between 0 and 9. Prints out the matrix as it generates it
    printf("Matrix A:\n");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            matrixA[i][j] = rand() % 10; // generates a random number between 0 and 9 and assigns it to the current matrix cell
            printf("%d   ", matrixA[i][j]);
        }
        printf("\n");
    }

    // generates an MxL matrix B, with each entry being a random number between 0 and 9. Prints out the matrix as it generates it
    printf("\n\nMatrix B:\n");
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < L; j++)
        {
             matrixB[i][j] = rand() % 10;
             printf("%d   ", matrixB[i][j]); // generates a random number between 0 and 9 and assigns it to the current matrix cell
        }
        printf("\n");
    }
    
    // creates a separate thread for calculating each row of the new matrix so that computations can be done in parallel (would need a multi-core CPU to properly do this though)
    int x;
    for (x = 0; x < N; x++)
    {  
        pthread_create(&threads[x], NULL, rowThreads, (void*)(size_t)x);
    }

    // joins all threads back together so that all calculations can be completed before printing out the product matrix C
    for (int i = 0; i < N; i++) 
    {
        pthread_join(threads[i],NULL);
    }

    // prints out each entry of the product matrix C
    printf("\n\nMatrix C:\n");
    for (int i = 0; i < N; i++)
    {
        for(int j = 0; j < L; j++)
        {
            printf("%d   ", matrixC[i][j]);
        }
        printf("\n");
    }
}