James Tennant
jtennant
Spring 2021
Assignment 6

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

ENCODE OPTIONS
  -h               Program usage and help.
  -v               Print statistics of encoding to stderr.
  -i infile        Input data to encode.
  -o outfile       Output of encoded data.

DECODE OPTIONS
  -h               Program usage and help.
  -v               Print statistics of decoding to stderr.
  -i infile        Input data to decode.
  -o outfile       Output of decoded data.

ENTROPY OPTIONS
  -h               Program usage and help.

# Note

I helped my friends Bono (bwmirand) and Sam Garcia with some parts of this assignment,
which should explain any unusual similarity in our code. I made sure to
stick to the rules and do nothing that would be against class policy.
