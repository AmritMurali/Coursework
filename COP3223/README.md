as1.c - finds roots/solutions of quadratic equation (ax^2 + bx + c = 0) using discriminant (b^2 -4ac)

as2.c - as1 + finds roots of linear equation (bx + c = 0) & gets user input (a, b, and c)

as3.c - find slope/y-int for linear eq. using 2 ordered pairs & calculates y-vals for x-vals + file input/output

as4.c - creates line struct based on title, slope, y-int, and x-vals + computes y-vals + writes to binary file

as5.c - as4 but writes to text file + memory allocation included (malloc(), free(), sizeof()...)

project.c - Calculator with a paper tape
- access/scroll through history using "b" and 10 storage variables(0-9) accessed using "sto" (binary) and "rcl"
- quick reset using "c", full reset including storage variables using "ca", quit calc program and print tape using "q" 
- use "pi" and "e", and 4-function ability ("+","-","/","x") + exp "^" + trig (sin,cos,tan,arcsin,arccos,arctan) 
- sqr root (sqr), rmv sign (abs), inverse: 1/x (inv), log base 10 (log), log base 2 (log2)
- No input file is needed. This program creates a text file, "calculator-tape-file-murali-amrit.txt". 
- I tested the project script given and everything worked prefectly and I have tried many test cases. The error
   handling is pretty good and even checks domains of functions.
