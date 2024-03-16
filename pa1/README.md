# pa1
This assignment is about making an integer doubly linked list ADT in C and alphabetizing the lines in a given input file. The main program will be an executable named Lex that takes in an input file, does the sorting, and prints out the new list into the specified outfile. 

## Files
Lex.c - C file that contains source code for main executable Lex

List.h - Header file containing functions for List.c

List.c - C file containing source code for List ADT

ListTest.c - Test file for List ADT

ListClient.c - Given Test file for List ADT

Makefile - Makefile to build and compile files

## Building
make - compiles Lex

make clean - removes compiled files

make checkTest - runs valgrind on ListTest 

make checkLex - runs valgrind on Lex

## Running
Lex - ./Lex < input file > < output file >

ListTest - ./ListTest

checkTest - ./checkTest

checkLex - ./checkLex

