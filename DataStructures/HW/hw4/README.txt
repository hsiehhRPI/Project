HOMEWORK 4: TOOL RENTAL LISTS


NAME:  < FIFI HSIEH >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< insert collaborators / resources >
- Rupak Stephen
- Nyx
- Andre L.
- Ez
- Mina

Resources:
- StackOverflow: Can you have two ifstream open at the same time?
	https://stackoverflow.com/questions/47957532/read-two-files-at-the-same-time#:~:text=You%20can%20have%202%20ifstreams%20at%20the%20same,it%20is%20quite%20a%20bit%20more%20the%202.\
- StackOverflow: Big O Notation for loading a file
	https://stackoverflow.com/questions/4957249/the-big-o-notation-for-reading-a-textfile-with-5-20-words
- StackOverflow: Operator Overloading for Multiple Classes
	https://stackoverflow.com/questions/4957249/the-big-o-notation-for-reading-a-textfile-with-5-20-words
- Geeks for geeks: Outputting to a file
	https://www.geeksforgeeks.org/readwrite-class-objects-fromto-file-c/
- Gist: Different sort algorithms for c++
	https://gist.github.com/svdamani/dc57e4d1b00342d4507d
- 


Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  <20 hours>



ORDER NOTATION:
Use these variables to analyze each phase of computation.  Briefly
justify your answer for each part.


i = # of different inventory items
c = # of different customers
p = # of pending customers
q = max quantity of a particular tool owned by the store
r = max # of tools rented or requested by a customer at one time
p = total # of pending tool rentals
e = # of rental or return events


Load inventory file: O(i)
Loading the inventory file could be dependent of the number of elements in said file.
There is no restriction on the number of element in the input file so the overall file loading
time should be O(i).

Rental event: O(i*c)
We need to step through the inventory list once in total. However, every one step in the 
inventory list we need to step throug the entire customer list to see if any of the customer
wanted the tool. The run time will be dependent on both the number of different inventory items
and the number of customers.

Return event - no pending customer(s): O(1)
If there is no pending customer, we only need to change the number of tools in the inventory.

Return event - with pending customer(s): O(p*r)
If there are pending customer, the process will be dependent of the quantity that is returned 
and the number of that specific tool the customer requested. We may be able to get through a 
few people on the waiting list or not at all.

Entire program: O(e)
The run time of the program is dependent of the number of rental or return events.
If the input file does not have a lot of cotent, not as much memory will be 
allocated which could take less time than another file that has a lot.


MISC. COMMENTS TO GRADER:
(optional, please be concise!)
I know the result is not great, but I really tried my best. I struggled a bit for the sorting.
I was recommended at ALAC that I could use this piece of code provided below(not accurate my variable names):
	list<customer>::iterator iter = customers.begin();
	customer c(#the inputs go here);
	while (itr->getID() < c.getID() && itr!=customers.end()) {
		++itr;
	}
	customers.insert(itr,c);
This works perfectly with just one file, however, if a second ifstream is present(closed or open, 
I tried them both), the code immediately throws a bad::aloc() upon reaching the while loop.
I'm quite curious as to why this happen(eventually, I resorted to look up other methods of sorting).

