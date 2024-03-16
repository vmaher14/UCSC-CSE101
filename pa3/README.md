# pa3
This assignment is about making a graph ADT and finding strongly connected components using the Depth First Search Algorithm. The main program will be an executable named FindComponents that takes in an input file and prints the output to the specified outfile. The input file contains the amount of verticies the graph will hold, the specified pairs, and the pair of verticies to perform the DFS algorithm on. It will print out the adjacency list representation of G and the strongly connected component pairs.

## Files
FindComponents.c - C file that contains source code for main executable FindComponents

List.h - Header file containing functions for List.c

List.c - C file containing source code for List ADT

Graph.h - Header file containing functions for Graph.c

Graph.c - C file containing source code for Graph ADT

GraphTest.c - Test file for graph ADT

Makefile - Makefile to build and compile files

## Building
make - compiles FindComponents

make clean - removes compiled files

make checkFind - runs valgrind on FindComponents with test input 7 

make checkTest - runs valgrind on GraphTest

## Running
FindComponents - ./FindComponents < input file > < output file >

GraphTest - ./GraphTest

checkFind - ./checkFind

checkTest - ./checkTest