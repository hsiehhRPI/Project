HOMEWORK 7: SUPER SMASH BROS. FRAMES


NAME:  < FIFI HSIEH >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< insert collaborators / resources >
- EZ

- GeeksforGeeks: Erasing an element from map c++
	https://www.geeksforgeeks.org/map-erase-function-in-c-stl/
- StackOverflow: Easiest way to convert integer to string
	https://stackoverflow.com/questions/5590381/easiest-way-to-convert-int-to-string-in-c
- GeeksforGeeks: C++ sets
	https://www.geeksforgeeks.org/set-in-cpp-stl/ 


Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 8 HOURS >



ORDER NOTATION ANALYSIS:
Consider the following variables and give the complexity for both running
time AND space along with a short justification for each of the queries below.
For the commands, do not count the space occupied by the database in the space
complexity analysis.

f: The total number of fighters
m: The number of different moves
t: The highest number of *moves that have the same starting frame for a particular move			//*Instead of moves it should be fighters 

//self defined parameter:
l: Limit number of fighters

reading the database/populating your initial data structure: O(fm), we need to account for f number of fighters and their m number of moves

-q (specific move): O(log(f)), since we only need to find the specific fighter and use the accessor of the particular move which is O(1)

-q (all): O(log(f)+m), once we find the number of fighters, we need to access statistics of all the moves which is accessed by accessors for m times to get all the moves

-f: O(m+l): We first need to find which move map I should use, then we need to output l number of fighters that are the fastest

-s: O(m+l): We first need to find which move map I should use, then we need to output l number of fighters that are the fastest(it is basically like the one above, except it is searched from the back)

-d: O(m+t) How I did my function is that I need to check which move is being searched for(hence the m, because I made a map for each map), and we need to output all the character with this particular frame of this move(t)


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)
Initially, there I did try to use vectors, but everything is replaced with allowed containers in the end.
Compared to the last assignment, this one is much more manageable. I hope we are allowed to use multiple maps because I did create maps for each moves instead of searching through the big database created.






