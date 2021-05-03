James Tennant
jtennant
Spring 2021
Assignment 4: The Circumnavigations of Denver Long

-----------
DESCRIPTION

This program will use data from an infile to construct an adjacency graph,
find all Hamiltonian paths using depth-first search,
identify the shortest hamiltonian path,
and write the path and number of recursive calls to to an outfile.

-----------
DISCLAIMERS

I helped my friends Bono (bwmirand) and Teresa (tqwu) with some parts
of this assignment, which should explain any unusual similarity in our code.
I made sure to stick to the rules
and do nothing that would be against class policy.

scan-build gives strange error about a print statement. this is clearly a non-issue

-----------
INSTRUCTIONS

To run the program:
1. Enter "make" into the command line. An executable file should appear.
2. Enter "./tsp -h" for the help message and options:
  -u             Use undirected graph.
  -v             Enable verbose printing.
  -h             Program usage and help.
  -i infile      Input containing graph (default: stdin)
  -o outfile     Output of computed path (default: stdout)
