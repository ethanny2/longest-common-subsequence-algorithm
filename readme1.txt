-Format: Prompt>./lscProgram program1 <filex.txt> <filey.txt> <output1.txt> 
-Function: Executes normal recursive version of LCS and times the running time of the algorithm.
-Data Structures: Just Vectors used for convenience as opposed to arrays.
-Analysis: The recursive (without dynamic programming or memoization) is wasteful because the subcalls are repeated and thus unnecessarily calculated. In the worst
case all the subcalls will execute O(2^n+n) times.
-Classes: None
-Notes: Compiles with g++ and no additional flags (such as std=c++11). I did not realize each program had to be a separate executable so I have 1 main.cpp file with 
all of my programs. You run the executable and then supply a command line arg (program1,program2,program3) then run with the 2 input files and 1 output file.
