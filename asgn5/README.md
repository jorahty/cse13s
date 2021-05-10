James Tennant
jtennant
Spring 2021
Assignment 5

# Desciption

For assignment 5 I created two programs: one program called "encode" for
encoding a file with Hamming(8, 4) codes, and another program called
"decode" for decoding the file. I was also provided with a program that
adds random errors to a given file. These 3 programs —- encode, decode,
and error -- can be used to test error correction. An additional program
called "entropy" was provided for measuring the entropy of a file.

# Instructions

1. To build the program, enter "make" into the command line. The three
excecutable files encode, decode, error (and entropy) should
appear.

2. To run the program, enter "./[name of executable]" and add "-h" for
the help message and options.

# Options

ENCODE OPTIONS
  -h               Program usage and help.
  -i infile        Input data to encode.
  -o outfile       Output of encoded data.

DECODE OPTIONS
  -h               Program usage and help.
  -v               Print statistics of decoding to stderr.
  -i infile        Input data to decode.
  -o outfile       Output of decoded data.

ERROR OPTIONS
  -h               Program usage and help.
  -s seed          Specifies the random seed.
  -e error rate    Specifies the error rate.

ENTROPY OPTIONS
  -h               Program usage and help.

# Note

I helped my friend Bono (bwmirand) with some parts of this assignment,
which should explain any unusual similarity in our code. I made sure to
stick to the rules and do nothing that would be against class policy.
