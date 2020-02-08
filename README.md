# Longest Common Subsequence Dynamic Programming Algorithm
[![Twitter Badge](https://img.shields.io/badge/chat-twitter-blue.svg)](https://twitter.com/ArrayLikeObj)
[![GitHub license](https://img.shields.io/github/license/ethanny2/longest-common-subsequence-algorithm)](https://github.com/ethanny2/longest-common-subsequence-algorithm/blob/master/LICENSE)

![Picture of Longest Common Subsequence Algorithm](https://i2.wp.com/algorithms.tutorialhorizon.com/files/2015/06/LCS-Printing-Result.png " Longest Common Subsequence Algorithm")


## Requirements
Requires some form of C++ compliation; and GNU make to create the executable .

## Usage
+ Invoke the make command to create an executable called lscProgram.exe
+ Run the executable with..
  + ./lscProgram [program1 or program2 or program3] [fileX.txt] [fileY.txt] [output.txt]
  + Where fileX.txt contains a single string (no spaces); first input string 
  + Where fileY.txt contains a single string (no spaces); the second input string
  + output.txt will contain the length of the LCS of the  two strings from fileX and fileY and a the running time the algorithm took to complete. Output varies slightly depending on if you used program1, program2 etc...
+ program1 command: Solves the Longest Common Subsequence between two strings by utilizing a bottom-up dynamic programming approach
  + Output Format:
    ```
    For input strings of size less or equal to 10: Each line i, for i = 0 to m (m = length of the string in filex.txt) of the output file will contain a row of the matrix lenLCS (as shown in image above). It will contain the lenLCS[i, j] for columns j = 0, 1, …, n (n = length of the string in filey.txt).

    Line m+1 will contain a longest common subsequence.
    Line m+2 will contain the running time of the algorithm. 
    ```

+ program2 command: Solves the Longest Common Subsequence between two strings via recursion with no memoization
  + Output Format:
    ```
    Line 1: The length of the LCS
    Line 2: The running time of the algorithm
    ```
+ program3 command: Solves the Longest Common Subsequence between two strings by utilizing a top-down dynamic programming approach and recursion
  + Output Format:
    ```
    Line 1: The length of the LCS
    Line 2: The running time of the algorithm
    ```
## Concepts and Analysis

### Concepts
+ Memoization:  *Storing the results of expensive function calls and returning the cached result when the same inputs occur again*
+ Constructing 2D array/table to utilize memoization
+ C++ vectors and high resolution clocks

### Analysis
+ The recursive (without dynamic programming or memoization) is wasteful because the subcalls are repeated and thus unnecessarily calculated. In the worst case all the subcalls will execute O(2^n+n) times
+ Data structures used: Just Vectors used for convenience as opposed to arrays

