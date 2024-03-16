# pa2
This assignment is about making a graph ADT and finding the shortest path between two vertices using the Breadth First Search. The main program will be an executable named FindPath that takes in an input file and prints the output to the specified outfile. The input file contains the amount of verticies the graph will hold, the specified pairs, and the pair of verticies to perform the BFS algorithm on. 

## Files
FindPath.c - C file that contains source code for main executable FindPath

List.h - Header file containing functions for List.c

List.c - C file containing source code for List ADT

Graph.h - Header file containing functions for Graph.c

Graph.c - C file containing source code for Graph ADT

GraphTest.c - Test file for graph ADT

Makefile - Makefile to build and compile files

## Building
make - compiles FindPath

make clean - removes compiled files

make checkFind - runs valgrind on FindPath with test input 7 

make checkTest - runs valgrind on GraphTest

## Running
FindPath - ./FindPath < input file > < output file >

GraphTest - ./GraphTest

checkFind - ./checkFind

checkTest - ./checkTest

