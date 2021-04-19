James Tennant
jtennant
Spring 2021
Assignment 2: A Small Numerical Library

-----------
DESCRIPTION

For this assignment I created a program that provides
numerical libraries for the following functions:
1) y = arcsin(x)
2) y = arccos(x)
3) y = arctan(x)
4) y = log(x)

Disclaimer: my log(x) function does not work properly

-----------
FILES

-
DESIGN.pdf

This file illustrates my approach to this assignment with
a description, a flow chart, and a few graphs.

-
mathlib-test.c

This file includes main() and test harness

-
mathlib.c

This file includes the C code for each of my functions

-
mathlib.h

This is the header file for my math functions

-
Makefile

This file compiles the C code and then creates an executable file.
-----------
INSTRUCTIONS

To run the program:
1. Enter "make" into the command line. An executable file should appear.
2. Enter "./math" into the command line followed by
   some combination of the following command-line options:
	-s runs arcsin tests
	-c runs arccos tests
	-t runs arctan tests
	-l runs log tests
	-a runs all tests

