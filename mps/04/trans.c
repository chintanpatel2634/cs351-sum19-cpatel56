/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
	int size_of_block;  //indicates the size of the block
	
	if(N == 64 || N == 32) {//When we are computing the matrix 64 x 64 and 32 x 32
		if(N == 64){// when the length of the matrix is 64, then we will use the size of block as 4
			size_of_block = 4;
		}
		if(N == 32) {//when the size of the matrix is 32, then we will use the size of block as 8
			size_of_block = 8;
		}
	
		for(int i = 0; i < N; i += size_of_block) {//performing the transpose using the size of block depending on the matrix. Incrementing with the size of the block
			for(int j = 0; j < M; j += size_of_block) {//incrementing j along M  with size of the block 
				for(int k = i, d, temp, bit; k < i + size_of_block; k++) {//incrementing from i to i+size_of_block
					for(int l = j; l < j + size_of_block; l++) {//incrementing with j till j + size of block
						if(k != l) {//moving the values from horizontal to vertical array B. 
							B[l][k] = A[k][l];
						}	
						else {//moving the values of A to temp
							temp = A[k][l];
							d = k;
							bit = 1;
						}
					}
					if(bit){//storing the value of A in B
						B[d][d] = temp;
						bit = 0;
					}
				}
			}
		}

		return;
	}
	
	if (N == 67) {//when the matrix is 61x67, block size is 14
		size_of_block = 14;
		for(int i = 0; i < N; i += size_of_block){//incrementing i with size of block along N
			for(int j = 0; j < M; j += size_of_block) { // incrementing j with size of block with M
				for(int k = i; k < i + size_of_block && k < N; k++) {//incrementing along N with increase in k. 
					for(int l = j; l < j + size_of_block && l < M; l++) {//incrementing along M with l++ 
						B[l][k] = A[k][l];//transposing the matrix 
					}	
				}
			}
		}

		return;
	}
}


/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

