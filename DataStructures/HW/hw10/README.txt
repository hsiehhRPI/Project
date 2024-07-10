HOMEWORK 10: DISTANCE FIELDS & FAST MARCHING METHOD


NAME:  < FIFI HSIEH >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< insert collaborators / resources >
- EZ

- Lecture notes
- Lab 12 code(Which was done under the help of TA Kajsa)
- Submitty Discussion Forum(For downloading GIMP)
- Gimp(Used to convert .ppm files)



Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 12 HOURS >



NAIVE ALGORITHM:

Order Notation: 
- NAIVE DISTANCE FIELD METHOD: O(w^w+h^h)

Timing Experiment Data:

The whole file:
- REAL: 0m 0.878s
- USER: 0m 0.598s
- SYS: 0m 0.094s

The program:
- REAL 0m 0.007s
- USER: 0m 0.002s
- SYS: 0m 0.000s


Discussion:
The reason the naive algorithm is O((w^w)(h^h)) is because both pictures need to be looped through to get the distance(each image has w and h, in this case the dimension is the same because the colored distanced image is mapped from the original picture).




IMPROVED ALGORITHM:

Order Notation: 
- IMPROVED DISTANCE FIELD METHOD: O(w*h + w*h*b)
- b is the number of black pixels present in the graph

Timing Experiment Data: 
The whole file:
- REAL: 0m 0.892s
- USER: 0m 0.675s
- SYS: 0m 0.024s

The program:
- REAL 0m 0.008s
- USER: 0m 0.002s
- SYS: 0m 0.000s

Discussion:
The improved method first loop through the input image to get the black dots and pushed into a vector, so when looping through the second image, we only need to compare each point with the number of entries in the vector containing all the black points.

FAST MARCHING METHOD (with a map):

Order Notation: O(w*h)

Timing Experiment Data: //I did not manage to make this function work

Discussion:
I couldn't impliment this function correctly, but ideally it will go through the priority queue where we will get all the neighbors of the target pixel, ideally we will only need to run through the entire picture once to initialize the neighbors of the black pixels, all the other initialization is done by the priority



DISTANCE FIELD VISUALIZATIONS FOR EXTRA CREDIT:




FAST MARCHING METHOD (with a hash table) FOR EXTRA CREDIT:

Order Notation:

Timing Experiment Data:

Discussion:



MISC. COMMENTS TO GRADER:  
Optional, please be concise!
I understand what the fast marching method attempt to do and can impliment it. However, I really struggle to use a priority queue to do so. I really appreciate the detailed instruction of this homework. I feel like it is the clearest of all the homework we have so far. In my opinion, priority queue is one of the hardest data structures we have learn so far. While it does not cause memory problems, the need to immitate a tree inside a vector and rearranging when need to is quite difficult.





