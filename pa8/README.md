# pa8
This assignment is about making a Dictionary ADT in C++ based on a Red Black Tree. There are two main programs. The first will be an executable named Order that takes in an input file containing a single string and inserting that string as a key into the dictionary. The position of the string in the input file will be the value mapped to the key. The program then prints to the outfile first the key, value pair inorder and then it will print the keys in a pre-order tree walk. The second executable will be WordFrequency that takes in a specified input file and parses through it and prints out the word and the frequency of that word in an inorder traversal.

## Files
Order.cpp - C++ file that contains source code for main executable Order

WordFrequency.cpp - C++ file that contains source code for main executable WordFrequency

DictionaryTest.cpp - Test file for List ADT

Dictionary.h - Header file containing functions for Dictionary.cpp

Dictionary.cpp - C++ file containing source code for Dictionary ADT

Makefile - Makefile to build and compile files

## Building
make - compiles Order WordFrequency DictionaryTest

make clean - removes compiled files

make Check - runs valgrind  

## Running
Order - ./Order < infile > < outfile > 

WordFrequency - ./WordFrequency < infile > < outfile >

DictionaryTest - ./DictionaryTest

Check - ./Check

