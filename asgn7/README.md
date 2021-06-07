James Tennant
jtennant
Spring 2021
Assignment 7

# Desciption

Create a program that serves as a censorship firewall. The program will
read words with regex from standard input and print a message with a list
of the user’s transgressions. The program will also print statistics if
specified. The program will determine if each word is allowed by searching
for it in a database using a Bloom filter and a Hash table.

# Instructions

1. To build the programs, enter "make" into the command line. The executable
file "banhammer" excecutable

2. To run the program, enter "./[name of executable]" and add "-h" for
the help message and options.

# Options

OPTIONS

-h           Program usage and help

-s           Print program statistics.

-m           Enable move-to-front rule.

-t size      Specify hash table size (default: 10000).

-f size      Specify Bloom filter size (default: 2^20).

# Note

I helped my friend Bono with this assignment,
so hopefully that explains any unusual similarity in out code.
