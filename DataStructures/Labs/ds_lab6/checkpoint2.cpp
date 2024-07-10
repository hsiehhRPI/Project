#include <iostream>
#include <string>
#include <vector>
#include <list>

template <class T>
void print(std::list<T> &data, const std::string &label) {
  typename std::list<T>::iterator y;
  std::cout << label << " ";
  for (y = data.begin(); y!=data.end(); ++y) {
    std::cout << " " <<*y;
  }
  std::cout << std::endl;
}


template <class T>
void reverse(std::list<T> &data) {
  typename std::list<T>::iterator i;
  i = data.begin();
  for (int u = 0; u < data.size(); u++) {
    T holder = *i;
    i = data.erase(i);
    data.push_front(holder);
  }
}

int main() {
  std::list<int> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);
  data.push_back(4);
  data.push_back(5);
  data.push_back(6);
  data.push_back(7);

  print(data,"before:");
  reverse(data);
  print(data,"after: ");

  std::list<std::string> data2;
  data2.push_back("apple");
  data2.push_back("banana");
  data2.push_back("carrot");
  data2.push_back("date");

  print(data2,"before:");
  reverse(data2);
  print(data2,"after: ");
}
