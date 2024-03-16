//------------------------------------------------------------------------------
// Victor Maher - CSE 101 pa4
// CruzID - Vmaher
//------------------------------------------------------------------------------
#include <stdio.h>
#include "Matrix.h"

int main (int argc, char* argv[]) {
    int n = 100;
    Matrix V = newMatrix(n);
    Matrix M = newMatrix(n);

   changeEntry(V, 1,1,1); changeEntry(M, 1,1,1);
   changeEntry(V, 1,2,2); changeEntry(M, 1,2,0);
   changeEntry(V, 1,3,3); changeEntry(M, 1,3,1);
   changeEntry(V, 2,1,4); changeEntry(M, 2,1,0);
   changeEntry(V, 2,2,5); changeEntry(M, 2,2,1);
   changeEntry(V, 2,3,6); changeEntry(M, 2,3,0);
   changeEntry(V, 3,1,7); changeEntry(M, 3,1,1);
   changeEntry(V, 3,2,8); changeEntry(M, 3,2,1);
   changeEntry(V, 3,3,9); changeEntry(M, 3,3,1);

   //print Matrices
   printf("Matrix V =\n");
   printMatrix(stdout, V);
   printf("\n");

   printf("Matrix M =\n");
   printMatrix(stdout, M);
   printf("\n");

   //print size of matrices
   printf("Size of Matrix V: %d, Size of Matrix M: %d\n", size(V), size(M));
   printf("\n");

   //print non-zero elements
   printf("NNZ in Matrix V: %d, NNZ in Matrix M: %d\n", NNZ(V), NNZ(M));
   printf("\n");

   //check if the matrices are equal
   printf("Are matrices equal?\n");
   printf("1 == true, 2 == false\n");
   int eq = equals(V, M);
   printf("%d\n", eq);
   printf("\n");

   //run operations
   Matrix C = copy(V);
   printf("Copy(V) =\n");
   printMatrix(stdout, C);
   printf("\n");

   Matrix T = transpose(V);
   printf("transpose(V) =\n");
   printMatrix(stdout, T);
   printf("\n");

   Matrix SM = scalarMult(2.5, V);
   printf("2.5(V) =\n");
   printMatrix(stdout, SM);
   printf("\n");

   Matrix VM = sum(V, M);
   printf("V+M =\n");
   printMatrix(stdout, VM);
   printf("\n");

   Matrix vm = diff(V, M);
   printf("V-M =\n");
   printMatrix(stdout, vm);
   printf("\n");

   Matrix PVM = product(V, M);
   printf("V*M =\n");
   printMatrix(stdout, PVM);
   printf("\n");

   //make zero of matrix V and M
   makeZero(V);
   makeZero(M);
   printMatrix(stdout, V);
   printMatrix(stdout, M);
   printf("\n");

   freeMatrix(&V);
   freeMatrix(&M);
   freeMatrix(&C);
   freeMatrix(&T);
   freeMatrix(&SM);
   freeMatrix(&VM);
   freeMatrix(&vm);
   freeMatrix(&PVM);

/* output
Matrix V =
1: (1, 1.0) (2, 2.0) (3, 3.0)
2: (1, 4.0) (2, 5.0) (3, 6.0)
3: (1, 7.0) (2, 8.0) (3, 9.0)

Matrix M =
1: (1, 1.0) (3, 1.0)
2: (2, 1.0)
3: (1, 1.0) (2, 1.0) (3, 1.0)

Size of Matrix V: 100, Size of Matrix M: 100

NNZ in Matrix V: 9, NNZ in Matrix M: 6

Are matrices equal?
1 == true, 2 == false
0

Copy(V) =
1: (1, 1.0) (2, 2.0) (3, 3.0)
2: (1, 4.0) (2, 5.0) (3, 6.0)
3: (1, 7.0) (2, 8.0) (3, 9.0)

transpose(V) =
1: (1, 1.0) (2, 4.0) (3, 7.0)
2: (1, 2.0) (2, 5.0) (3, 8.0)
3: (1, 3.0) (2, 6.0) (3, 9.0)

2.5(V) =
1: (1, 2.5) (2, 5.0) (3, 7.5)
2: (1, 10.0) (2, 12.5) (3, 15.0)
3: (1, 17.5) (2, 20.0) (3, 22.5)

V+M =
1: (1, 2.0) (2, 2.0) (3, 4.0)
2: (1, 4.0) (2, 6.0) (3, 6.0)
3: (1, 8.0) (2, 9.0) (3, 10.0)

V-M =
1: (2, 2.0) (3, -1.0)
2: (1, 4.0) (2, 4.0) (3, 6.0)
3: (1, 6.0) (2, 7.0) (3, 8.0)

V*M =
1: (1, 4.0) (2, 5.0) (3, 4.0)
2: (1, 10.0) (2, 11.0) (3, 10.0)
3: (1, 16.0) (2, 17.0) (3, 16.0)
*/












}