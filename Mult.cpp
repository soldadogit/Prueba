#include <iostream>
#include <stdio.h>
#include <ctime>
#include <omp.h>
#define n 2048

using namespace std;

/*
void Transpose(int* A,int* B,int F,int C){
    for(int i=0;i<F;i++){
      for(int j=0;j<C;j++){
        B[j*F+i]=A[i*C+j];
      }
    }
}
*/


void MultO(int **A,int ** B,int **C){
int sum,j,k;
#pragma omp parallel for private(sum,j,k)
	for(int i=0;i<n;i++){
		sum=0;
		for(int j=0;j<n;j++){
			for(int k=0;k<n;k++){
				sum+=A[i][k]*B[j][k];
			}
			C[i][j]=sum;

		}


	}
}
//CG pechuga sonsa
void Mult(int **A,int ** B,int **C){
int sum;
#pragma omp parallel for
	for(int i=0;i<n;i++){
		sum=0;
		for(int j=0;j<n;j++){
			//#pragma omp parallel for reduction(+:sum)
			for(int k=0;k<n;k++){
				sum+=A[i][k]*B[k][j];
			}
			C[i][j]=sum;

		}


	}
}




int main () {


  int **A, **B, **C;
  A =new int *[n];
  B =new int *[n];
  C =new int *[n];

for(int i=0;i<n;i++){
	A[i]=new int [n];
	B[i]=new int [n];
	C[i]=new int [n];
}


MultO(A,B,C);


for (int i=0; i<n; i++){
    delete[] A[i];
		delete[] B[i];
		delete[] C[i];
}
delete[] A;
delete[] B;
delete[] C;

//LAS SUCIAS
	


  return 0;
}
