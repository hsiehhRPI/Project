HOMEWORK 9: MINIBLAST


NAME:  < FIFI HSIEH >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

- ANDRE
- EZ
- THALIA
- SMAYAN
- PROFESSOR XIAO

- GeeksforGeeks: Open Addressing and Collision Handling
    https://www.geeksforgeeks.org/open-addressing-collision-handling-technique-in-hashing/
- StackOverflow: Implimenting Linear Probing in C++:
    https://stackoverflow.com/questions/59343959/how-do-i-implement-linear-probing-in-c
- Quescol: Linear Probing Explanation with Example
    https://quescol.com/data-structure/linear-probing
- Lab 11
- Lecture notes

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 15 HOURS >


HASH FUNCTION DESCRIPTION
The hash function present in my code is taken from lab 11. 
I decide to use this hash function is because it is a good hash function for hashing strings in general.
Since we are passing in Kmer length strings, I thought the hash function would be suitable for this homework.


HASH TABLE IMPLEMENTATION
I decide to impliment my hash table as a vector of pairs.
The first argument of the pair is a string(the kmer length DNA), the second is the location it is in the genome file.
I choose to use pairs because we need the key later for searching the file, but also the location segment in the file.
Since only two variables need to be stored at each position, I choose pairs over vector because I don't trust myself for not making 2D vector indexing errors. It is easy to access values in a pair by using .first and .second.
I chose vectors over lists is because I prefer indexing over using an iterator, which could cause complication when I tried to dereference it. 


ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)

L = length of the genome sequence
q - query length
p - number of different locations where key is found
k - key size (k-mer size)

How much memory will the hash table data structure require (order notation for memory use)?

l = size of the location integer
K = length of kmer(integer, ex. 10)
O((L-(K-1))*(k+l))
Where L-K-1 is the number of kmer length segments in the hash table(Since the last k-1 number cannot form kmer-length segments), k+1 is memory space each individual pair of kmer key and location integer require. 

What is the order notation for performance (running time) of each of
the commands? What about for the hash table's insert, find, and resize?

insert: O(1)
On average O(1), since the hash function creates a random location in the hash table for the function to assign the value.
Since the data structure used to construct the hash table is a vector, we could access the result index from the hash function by indexing which is a O(1) process. It will only be longer because there are repeating segments of DNA which will yield the same hash value.
I used linear probing(go to the next empty space and assign the value there).

find: O(pq)
The run time for find really depends on how repeats of said kmer length DNA there are, each of the location will have to run through CheckSame, which check the similarity between DNA at the location and the query DNA.(The q part of this function is from the checkSame function below)

checkSame(HELPER OF FIND): O(q)
We run through the entire length of the query string to determine whether its mismatch is within acceptable range.

resize: O(2T+T)
Where T is the original hash table memory size(in other words: O((L-(K-1))*(k+l))).
We need to create a vector with 2T amount of space allocated and then re-hash each value of the table into the new table.

EXTRA CREDIT
Add a new command to implement the database using one of the other
 data structures that we have covered so far in the course: 
vectors, lists, arrays etc. 

Compare the performance your alternative method to the homework method
by making a table of run times for each of the genomes and query 
sets provided with the homework  and compare the times to build
the index and the times to process the queries. 
Document any new commands you have added in your README file.



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)
This homework really help me understand how hash tables work. In all honesty, I was confused between separate chaining and linear probing before this homework. Special thanks to my friends who has taken the course before, they really explained it to me well. I thought this homework give a good amount of challenge but is still executable. 

On a side note, when I tried to output on my computer, the results are correct. However, it does not work on submitty because of basic_string::_M_construct null not valid. However, when running both clang++ and g++ on my computer they where fine.

I started a question on the forum and the professor answered and said that it was because I didn't include my h file, but I don't think that's where my problem was. I included everything I needed(all the functions are included in the miniBlast.cpp file, I didn't need an h file at the time.) Even after moving all my functions to an h file and constructing my hash table as a class, the print function still has error occuring.

