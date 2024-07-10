HOMEWORK 8: B+ TREES


NAME:  < FIFI HSIEH >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< insert collaborators / resources >
- EZ
- Xujun

- GeeksforGeeks: Forward Declaration
	https://www.geeksforgeeks.org/what-are-forward-declarations-in-c/ 
- StackOverflow: Accessing private member of a friend class
	https://stackoverflow.com/questions/33860882/c-accessing-a-private-member-in-a-friend-class
- GeeksforGeeks: B+ tree
	https://www.geeksforgeeks.org/b-trees-implementation-in-c/
- OpenGenus IQ: B+ tree
	https://iq.opengenus.org/b-tree-search-insert-delete-operations/
- Programiz: B-tree
	https://www.programiz.com/dsa/b-tree 
- Programiz: B+tree
	https://www.programiz.com/dsa/b-plus-tree

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  <20 HOURS>


TESTING & DEBUGGING STRATEGY: 
Discuss your strategy for testing & debugging your program.  
What tools did you use (gdb/lldb/Visual Studio debugger,
Valgrind/Dr. Memory, std::cout & print, etc.)?  How did you test the
"corner cases" of your implementation?

I mainly used gdb and valgrind to find errors. When using gdb, I set break points at the start of the function and step through them, and would print out variables or sizes of vectors. When using valgrind, I will definitely compile with -g and run with --leak-check=full to get the line number. To locate where printing is wrong, some std::cout for outputting to the consol are sprinkled through the test.cpp we were given. Since there were so many example tests, I comment out and worked through the test one by one. It helps limit the range my errors occur. To deal with corner cases(in this case, destructor could be a big problem where you delete a specific side of tree), so I would construct a big tree and delete it and use valgrind to see if there are any memory error.


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)
I really struggle for this homework. I had trouble to understand what is going on for the homework, the B+ tree is also much more complex compared to the binary tree/ binary search tree we where taught in class. I understand that we went over trees for three lectures, but it still feel like one of the more complex topics in data structure. 

I really appreciate the mentor and friend that worked with me. All the mentors at ALAC worked very hard. I went to ALAC half an hour early, and joined the queue when there where 3 people in the queue. Two and a half hours later, it was never my turn. I really appreciate all the ds helper and I understand that there are no way that they could help all of us, but I can't help feeling a bit frustrated. 

If I had more time, I believe I could understand this topic better. But I find understanding this tree challenging. Although binary tree and B+ tree are both tree structures, they are quite different. Binary tree only needed to account for two children, while there are much more children to account for for B+ trees. B+ tree grows to create new roots while the base remained(not really, but mostly), meaning new roots needed to be constantly accounted for, making the operations much more complex. It is also much harder to traverse. 