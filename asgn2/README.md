James Tennant
jtennant
Fall 2020
Assignment 2: A Small Numerical Library

-----------
DESCRIPTION

For this assignment I created a program that provides
numerical libraries for the following functions:
1) y = sin(x)
2) y = cos(x)
3) y = tan(x)
4) y = e^x

-----------
FILES

-
DESIGN.pdf

This file illustrates my approach to this assignment with
a description, a flow chart, and a few graphs.

-
math.c

This file includes the C code and is meant to be compiled.

-
Makefile

This file compiles the C code and then creates an executable file.
-----------
INSTRUCTIONS

This program is intended to be run on the UCSC Unix Timeshare server.
To run the program:
1. Enter "make" into the command line. An executable file should appear.
2. Enter "./math" into the command line followed by
   exactly one of the following command-line options:
	-s runs sin tests
	-c runs cos tests
	-t runs tan tests
	-e runs exp tests
	-a runs all tests
