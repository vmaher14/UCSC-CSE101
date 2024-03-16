# pa4
This assignment is about making a Matrix ADT and performing different matrix operations on any two matrices. The main program will be an executable named Sparse that takes in an input file and prints the output to the specified outfile. The input file contains the number of rows there will be, and the number of non-zero entries for both matrices along with the values for each row and column. It will print out the different matrices after performing different operations on them.

## Files
Sparse.c - C file that contains source code for main executable Sparse

List.h - Header file containing functions for List.c

List.c - C file containing source code for List ADT

Matrix.h - Header file containing functions for Matrix.c

Matrix.c - C file containing source code for Matrix ADT

MatrixTest.c - Test file for Matrix ADT

ListTest.c - Test file for List ADT

Makefile - Makefile to build and compile files

## Building
make - compiles Matrix ADT

make ListTest - compiled List test

make MatrixTest - compiles Matrix test

make clean - removes compiled files

make checkFind - runs valgrind on FindComponents with test input 7 

make checkTest - runs valgrind on GraphTest

## Running
Sparse - ./Sparse < input file > < output file >

MatrixTest - ./MatrixTest

ListTest - ./ListTest

checkSparse - ./checkSparse

checkTestM - ./checkTestM

checkTestL - ./checkTestL