// A simple "caller ID" program

#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

// add a number, name pair to the phonebook
void add(map<int, string> &phonebook, int number, string const& name) {
  map<int, string>::iterator itr = phonebook.find(number);
  if (itr == phonebook.end()) {
   phonebook[number] = name;
  }
  else {
    cout << "This number is already taken!" << endl;
  }
}

// given a phone number, determine who is calling
void identify(const map<int, string> & phonebook, int number) {
  map<int, string>::const_iterator vtr = phonebook.find(number);
  if (vtr->first == number) {
     cout << vtr->second << " is calling!" << endl;
  }
  else if (vtr == phonebook.end()) {
    cout << "unknown caller!" << endl;
  }

}


int main() {
  // create the phonebook; initially all numbers are unassigned
  map<int, string> phonebook;

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
