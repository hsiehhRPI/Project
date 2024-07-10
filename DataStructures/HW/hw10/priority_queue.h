#ifndef priority_queue_h_
#define priority_queue_h_

#include <cassert>
#include <iostream>
#include <vector>
#include <map>

// The DistancePixel_PriorityQueue is a customized, non-templated
// priority queue that stores DistancePixel pointers in a heap.  The 
// elements in the heap can be looked up in a map, to quickly find out
// the current index of the element within the heap.

// ASSIGNMENT: The class implementation is incomplete.  Finish the
//   implementation of this class, and add any functions you need.

// =========================================================================

class DistancePixel_PriorityQueue {

 public:
  
  // --------------------------
  // CONSTRUCTORS
  // default constructor
  DistancePixel_PriorityQueue() {}
  // construct a heap from a vector of data
  DistancePixel_PriorityQueue(const std::vector<DistancePixel*> &values) {
    //Use the push function that is now fully written
    for (unsigned long int n = 0; n < values.size(); n++) {
      push(values[n]);
    }
  }

  // ------------------------
  // ACCESSORS
  int size() { return m_heap.size(); }
  bool empty() { return m_heap.empty(); }
  int last_non_leaf() { return (size()-1) / 2; }
  int get_parent(int i) { assert (i > 0 && i < size()); return (i-1) / 2; }
  bool has_left_child(int i) { return (2*i)+1 < size(); }
  bool has_right_child(int i) { return (2*i)+2 < size(); }
  int get_left_child(int i) { assert (i >= 0 && has_left_child(i)); return 2*i + 1; }
  int get_right_child(int i) { assert (i >= 0 && has_right_child(i)); return 2*i + 2; }

  // read the top element
  const DistancePixel* top() const  {
    assert(!m_heap.empty());
    return m_heap[0]; 
  }

  // is this element in the heap?
  bool in_heap(DistancePixel* element) const {
    std::map<DistancePixel*,int>::const_iterator itr = backpointers.find(element);
    return (itr != backpointers.end());
  }

  // add an element to the heap
  void push(DistancePixel* element) {
    std::map<DistancePixel*,int>::iterator itr = backpointers.find(element);
    assert (itr == backpointers.end());
    m_heap.push_back(element);
    backpointers[element] = m_heap.size()-1;
    this->percolate_up(int(m_heap.size()-1));
  }

  // the value of this element has been edited, move the element up or down
  void update_position(DistancePixel* element) {
    std::map<DistancePixel*,int>::iterator itr = backpointers.find(element);
    assert (itr != backpointers.end());
    this->percolate_up(itr->second);
    this->percolate_down(itr->second);
  }
  
  // remove the top (minimum) element
  void pop() {
    assert(!m_heap.empty());
    int success = backpointers.erase(m_heap[0]);
    assert (success == 1);
    m_heap[0] = m_heap.back();
    m_heap.pop_back();
    this->percolate_down(0);
  }
  
 private:

  // REPRESENTATION
  // the heap is stored in a vector representation (the binary tree
  // structure "unrolled" one row at a time)
  std::vector<DistancePixel*> m_heap;
  // the map stores a correpondence between elements & indices in the heap
  std::map<DistancePixel*,int> backpointers;

  // private helper functions
  //i seems to be the index element of the priority queue    
  void percolate_up(int i) {
    //This is written based on my understanding of the lecture note example
    //Index 0 is guaranteed to not have parent
    while (get_parent(i)) { //If we can get the parent(new values are added at the very end first)
      if (m_heap[i] < m_heap[get_parent(i)]) { 
        //If the child is less than its parent
        std::swap(m_heap[i],m_heap[get_parent(i)]);
        i = get_parent(i);
      }
      else {
        break;
      }
    }
  }
  
  void percolate_down(int i) {
    //This is written based on my understanding of the lecture note example
    while (get_left_child(i)) {
      int cI; //Child index
      //First check if there are both child and that the right child is smaller than the left
      if (get_right_child(i)&&m_heap[get_right_child(i)] < m_heap[get_left_child(i)]) {
        cI = get_right_child(i); 
      }
      else {
        //If that is not the case, child index should be the left child
        cI = get_left_child(i);
      }
      if (m_heap[cI] < m_heap[i]) {
        //If the child is less than its parent, switch their position
        std::swap(m_heap[cI], m_heap[i]);
        i = cI; //Starting from where the child is now, check if the tree structure maintain
      }
      else {
        break;
      }
    }
  }
};

#endif
