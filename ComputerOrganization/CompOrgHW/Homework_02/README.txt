CompOrg HW2: MIPS LINES
FIFI HSIEH

Collaborators: None

Sources: 
- Class examples
- Lab5: Shell lab
- https://www.w3schools.blog/check-if-string-is-number-c	(isdigit())
- https://www.geeksforgeeks.org/strtok-strtok_r-functions-c-examples/	(File parsing)
- https://www.tutorialspoint.com/cprogramming/c_file_io.how-to-debug-c-program-using-gdb-in-6-simple-steps(Output to file)
- https://u.osu.edu/cstutorials/2018/09/28/how-to-debug-c-program-using-gdb-in-6-simple-steps/	(How to run gdb with input file)

Estimated time used: About 20 hours

Design explanation:
I wanted to simulate actual registers so I made a struct to represent each registers. It contained the type of the register, value it contained, whether it is occupied, the variable name of the value it is holding, and its register number.

Registers t0-t9 and s0-s7 are stored in the same array. I have taken inspiration from stop and copy garbage collecting technique which have working and storage memory in the same array. 

I deeply apologize for the really long main file, I was not sure what the commandline will be so I put them in the same file.