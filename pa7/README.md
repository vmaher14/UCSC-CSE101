# pa7
This assignment is about making a Dictionary ADT in C++ based on a Binary Search Tree. The main program will be an executable named Order that takes in an input file containing a single string and inserting that string as a key into the dictionary. The position of the string in the input file will be the value mapped to the key. The program then prints to the outfile first the key, value pair inorder and then it will print the keys in a pre-order tree walk.

## Files
Order.cpp - C++ file that contains source code for main executable Order

DictionaryTest.cpp - Test file for List ADT

Dictionary.h - Header file containing functions for Dictionary.cpp

Dictionary.cpp - C++ file containing source code for Dictionary ADT

Makefile - Makefile to build and compile files

## Building
make - compiles Order

make clean - removes compiled files

make Check - runs valgrind  

## Running
Order - ./Order < in file > < out file >

DictionaryTest - ./DictionaryTest

Check - ./Check

