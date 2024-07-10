// A simple "caller ID" program

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// add a number, name pair to the phonebook
void add(vector<string> &phonebook, int number, string const& name) {
  phonebook[number] = name;
}

// given a phone number, determine who is calling
void identify(const vector<string> & phonebook, int number) {
  if (phonebook[number] == "UNASSIGNED") 
    cout << "unknown caller!" << endl;
  else 
    cout << phonebook[number] << " is calling!" << endl;
}


int main() {
  // create the phonebook; initially all numbers are unassigned
  vector<string> phonebook(10000, "UNASSIGNED");

  // add several names to the phonebook
  add(phonebook, 1111, "fred");
  add(phonebook, 2222, "sally");
  add(phonebook, 3333, "george");

  // test the phonebook
  identify(phonebook, 2222);
  identify(phonebook, 4444);

  //Test case
  add(phonebook, 6767, "jake");
  add(phonebook, 6767, "john");
  add(phonebook, 7776, "gina");


  identify(phonebook, 6767);
  identify(phonebook, 7776);
}


/*--------PART 1--------
  - BigO of constructing the phonebook(if we just call add once) = O(1)
  - BigO of searching the phonebook = O(1)
  - The amount of memory used by this program is O(N), N being the largest number of phone number
  ----------------------*/

