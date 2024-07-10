HOMEWORK 6: INVERSE WORD SEARCH


NAME:  < FIFI HSIEH >


COLLABORATORS AND OTHER RESOURCES: 
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< insert collaborators / resources >
- EZ
- ALEXANDRA LEE
- GARRETT BROOKS

- StackOverflow: 4D vector declaration
	https://stackoverflow.com/questions/13218318/initialising-a-4d-vector
- Professor Xiao's webex meeting about the homework
- Lab 8
- StackOverflow: integer to string 
	https://stackoverflow.com/questions/4668760/converting-an-int-to-stdstring

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.

ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 40 HOURS >


ALGORITHM ANALYSIS:
What's the order notation of your algorithm?
The order notation of my function findFill = O(n*p). Where n is the number of target words to fill and 
p is the number of positions of the word could be filled.

The order notation of my function findAllGrid is O(n^2*p). Where n is the number of words to fit in a grid and 
p is the number of positions each word could be filled.

The order notation of my function checkForbidden is O(b*f*p). Where b is total number of boards created, 
f is the number of forbidden words, and p is the number of positions the specific forbidden word can be filled.


TEST CASE SUMMARY:
How did your program perform on the different test cases?  Summarize
the running times.  (It's ok if it didn't finish the harder examples.)
What new test cases did you create and how did it perform on those
tests?

My program cannot perform any of the test case as of right now. But I hope the cases where the rows or columns are zero would be terminated immediately.


MISC. COMMENTS TO GRADER:  
Optional, please be concise!
	I started on Monday during spring break, but progress had been staggering and I was quite frustrated.
	I tried my best for this homework, had to forfeit large portion of my birthday to attempt to finish this.
	I struggled quite a bit for this homework. The estimated number of hours spent is very conservative.
	In all honesty, I was worried about this homework because I'm not familiar with recursion before this homework.
	I encountered some difficulties when I did the homework:
	Originally, the function findFill finds a series of possible paths to fill the target word(which calls for a 2D vector to account for all the possibility), however, it will call for a 3D vector(which I am not very confident on implimenting even after looking up on StackOverflow) to contain all the paths for every word we need to fill. To fix this problem, every word is filled into designated 2D arrays and push back into a vector<char**>. 

	The grid is completed by overlaying one grid over another, since the findFill function has 

	Since I used 2D arrays to implement the board. To prevent memory leaks, a destroy function is created and called whenever an array is made.

	This homework is very challenging, but it made me understand recursion much better
