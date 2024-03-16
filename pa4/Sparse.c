//------------------------------------------------------------------------------
// Victor Maher - CSE 101 pa4
// CruzID - Vmaher
//------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"

int main(int argc, char *argv[]) {
    FILE *in;
    FILE *out;

    //checks command line for correct number of arguments;
    if (argc != 3) {
        printf("Can only accept 2 arguments, <input file> <output file>\n");
        exit(1);
    }
    //open file for reading
    in = fopen(argv[1], "r");
    if (in == NULL) {
        printf("Unable to open file for reading\n");
        exit(1);
    }
    //open file for writing
    out = fopen(argv[2], "w");
    if (out == NULL) {
        printf("Unable to open file for writing\n");
        exit(1);
    }

    //size of Matrix
    int n, anon, bnon;
    fscanf(in, "%d %d %d", &n, &anon, &bnon);

    //make Matrices
    Matrix A = newMatrix(n);
    Matrix B = newMatrix(n);

    //loop through file until hit first white space
    int row, col;
    double val;
    for (int i = 1; i <= anon; i += 1) {
        if (fscanf(in, "%d %d %lf\n", &row, &col, &val) != EOF) {
            changeEntry(A, row, col, val);
        }
    }

    for (int i = 1; i <= bnon; i += 1) {
        if (fscanf(in, "%d %d %lf\n", &row, &col, &val) != EOF) {
            changeEntry(B, row, col, val);
        }
    }

    //call functions and print out matrices
    fprintf(out, "A has %d non-zero entries:\n", anon);
    printMatrix(out, A);
    fprintf(out, "\n");

    fprintf(out, "B has %d non-zero entries:\n", bnon);
    printMatrix(out, B);
    fprintf(out, "\n");

    //scalar
    fprintf(out, "(1.5)*A =\n");
    double x = 1.5;
    Matrix SM = scalarMult(x, A);
    printMatrix(out, SM);
    fprintf(out, "\n");

    //A+B
    fprintf(out, "A+B =\n");
    Matrix AB = sum(A, B);
    printMatrix(out, AB);
    fprintf(out, "\n");

    //A+A
    fprintf(out, "A+A =\n");
    Matrix AA = sum(A, A);
    printMatrix(out, AA);
    fprintf(out, "\n");

    //B-A
    fprintf(out, "B-A =\n");
    Matrix BA = diff(B, A);
    printMatrix(out, BA);
    fprintf(out, "\n");

    //A-A
    fprintf(out, "A-A =\n");
    Matrix AD = diff(A, A);
    printMatrix(out, AD);
    fprintf(out, "\n");

    //Transpose(A)
    fprintf(out, "Transpose(A) =\n");
    Matrix T = transpose(A);
    printMatrix(out, T);
    fprintf(out, "\n");

    //A*B
    fprintf(out, "A*B =\n");
    Matrix AmB = product(A, B);
    printMatrix(out, AmB);
    fprintf(out, "\n");

    //B*B
    fprintf(out, "B*B =\n");
    Matrix BmB = product(B, B);
    printMatrix(out, BmB);
    fprintf(out, "\n");

    //free allocated memory by matrices
    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&SM);
    freeMatrix(&AB);
    freeMatrix(&AA);
    freeMatrix(&BA);
    freeMatrix(&AD);
    freeMatrix(&T);
    freeMatrix(&AmB);
    freeMatrix(&BmB);
   
    //close files
    fclose(in);
    fclose(out);
}