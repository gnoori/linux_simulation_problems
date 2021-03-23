# linux_simulation_problems
Write a program in C/C++ handling a basic menu–in text mode, with 3 items (Problem 1, Problem 2, and Exititem.  When the user selects Problem1(typing 1 or 2 or 3 from the keyboard) the  software  should  start  running  the  problem  1.  If  the Problem2 menu  item  is  selected,  the problem 2 should run. The software should exist only if the Exitmenu isselected. The problem 1 and problem 2 solutions should run as many times the user wishes.

Problem 1: 

Givena sequence of numbers x0, x1, ..., xn2ε{0,1} in a binary file,where xirepresents a square matrix elementin a linear fashion (concatenate the lines of the matrixfor example),write a simulation process in C/C++  as follows: a) start M threads, b) each thread generates a column  and  a  row  randomly,c)  considering the  element  location in  the  matrix given  by  the generated column and rowchange the value of the matrix element to 0 if its 4/8 neighbors are predominantly 0, and 1 otherwise. 

Problem  2:  

Given  a  sequence  of  numbers, x0, x1,...,xn2εR  in  a  text  file-separated  by  a  ‘\t’ character, write a simulation process in C/C++ as follows: a) start M threads, b) each thread is generating an(i,j)pair randomly such as 0&lt;=i&lt;=j&lt;n, and each thread is sorting the values from xi to xj in the text file and write the values in the fileonce sorted. The threads are finished when the list is completely sorted. Each thread each time after generating the (i,j) pair should randomly select which sorting algorithm should consider. The possible algorithms should be a) quick sort, b) insert sort and c) bubble sort.
