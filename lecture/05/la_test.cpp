#include <climits>
#include <iostream>
#include <omp.h>
#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include "la.h"


// #define RANDTOP INT_MAX
#define RANDTOP 10

int main(int argc, char *argv[])
{
	int n;
	double *A;
	double *B;
	double *C;
	double *a;
	double *b;
	double *c;
	double result;
	int resultloc;

	std::cout << "Running with OMP max threads = " << omp_get_max_threads() << std::endl;

	if(argc == 1){
		n = 4;
		printf("Running with n = %d\n", n);

		A =(double *) malloc(sizeof(double)*n*n);
		B =(double *) malloc(sizeof(double)*n*n);
		C = (double *) malloc(sizeof(double)*n*n);

		for(int i=0; i < n; i++)
			for(int j=0; j < n; j++)
			{
				A[loc(i,j,n)] = i + j;
				B[loc(i,j,n)] = (i == j) ? 1 : 0;
				C[loc(i,j,n)] = 9;
			}

		printf("A = \n");
		printMatrix(A, n);
		printf("B = \n");
		printMatrix(B, n);
		printf("C = \n");
		printMatrix(C, n);
		printf("A * B = \n");
		matmul(A, B, C, n);
		printMatrix(C, n);

	} else if(argc == 2) {
		n = 10;
		int testnumber = atoi(argv[1]);
		n = testnumber;
		A = (double*) malloc(sizeof(double)*n*n);
		B = (double*) malloc(sizeof(double)*n*n);
		C = (double*) malloc(sizeof(double)*n*n);
		a = (double*) malloc(sizeof(double)*n);
		b = (double*) malloc(sizeof(double)*n);
		c = (double*) malloc(sizeof(double)*n);
		
		std::random_device rd;  // a seed source for the random number engine
		std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
		std::uniform_int_distribution<> randint(1, RANDTOP);


		for(int i=0; i < n; i++)
		{
		for(int j=0; j < n; j++)
			{
				A[loc(i,j,n)] = B[loc(i,i,n)] = i + 2 * j;
				C[loc(i,j,n)] = 9;
			}
			a[i] = randint(gen);
			b[i] = randint(gen);
			c[i] = randint(gen);
		}

		std::cout << "n = " << n << std::endl;
		// test here
		 // get starting time using chrono
		auto start = std::chrono::high_resolution_clock::now();
		auto end = std::chrono::high_resolution_clock::now();

		start = std::chrono::high_resolution_clock::now();
		// prefix(a, b, n);
		matmul(A, B, C, n);
		end = std::chrono::high_resolution_clock::now();
		std::cout << "Parallel Mat Mul time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " ns" << std::endl;

		start = std::chrono::high_resolution_clock::now();
		serialmatmul(A, B, C, n);
		end = std::chrono::high_resolution_clock::now();
		std::cout << "Serial Mat Mul time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " ns" << std::endl;

		// printVector(a, n);
		// printVector(b, n);

	} else {
		std::cout << "This only takes the n dimension as an argument" << std::endl;
		return 1;
	}

	return 0;
}
