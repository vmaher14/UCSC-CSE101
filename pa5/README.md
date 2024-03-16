# pa5
This assignment is about making an integer doubly linked list ADT in C++. The main program will be an executable named Shuffle that takes in an input file, and runs a perfect shuffle algorithm until the deck returns back to it's original state. The deck's size is specified by the user.

## Files
Shuffle.cpp - C file that contains source code for main executable Lex

List.h - Header file containing functions for List.c

List.cpp - C file containing source code for List ADT

ListTest.cpp - Test file for List ADT

Makefile - Makefile to build and compile files

## Building
make - compiles Shuffle

make clean - removes compiled files

make check1 - runs valgrind on ListTest 

make check2 - runs valgrind on Shuffle w/ argument 35

## Running
Shuffle - ./Shuffle < argument > 

ListTest - ./ListTest

check1 - ./check1

check2 - ./check2