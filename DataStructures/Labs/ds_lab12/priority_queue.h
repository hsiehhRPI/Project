#ifndef priority_queue_h_
#define priority_queue_h_

#include <iostream>
#include <vector>
#include <cassert>


template <class T>
class priority_queue {
private:
  std::vector<T> m_heap;

public:
  priority_queue() {}

  priority_queue( std::vector<T> const& values ) {
  }

  const T& top() const 
  {
    assert( !m_heap.empty() );
    return m_heap[0]; 
  }

  void push( const T& entry ) {

    if (m_heap.empty()==true) {
      m_heap.push_back(entry);
    }
    else {
      //Add the entry to the back of the vector first
      m_heap.push_back(entry);
      int i = m_heap.size()-1;
      int pI = (i-1)/2;
      while (pI >= 0) {
        if (m_heap[i]<m_heap[pI]) {
          std::swap(m_heap[i], m_heap[pI]);
          i = pI;
        }
        else {
          break;
        }
      }
    }
 }

 void percolate_down(std::vector<T>& vec, int idx) {
  while ((2*idx)+1<vec.size()) {
    int cI = 0;
    if ((2*idx)+2 < vec.size()&& vec[(2*idx)+1] > vec[(2*idx)+2]) {
      cI = (2*idx)+2;
    }
    else {
      cI = (2*idx)+1;
    }
    if (vec[cI] < vec[idx]) {
      std::swap(vec[cI], vec[idx]);
      idx = cI;
    }
    else {
      break;
    }
  }
 }

  void pop() 
  {
    if (m_heap.size()==1) {
      m_heap.clear();
    }
    else {
      m_heap[0] = m_heap[m_heap.size()-1];
      m_heap.pop_back();
      percolate_down(m_heap, 0);
    }
    assert( !m_heap.empty() );
  }

  int size() { return m_heap.size(); }
  bool empty() { return m_heap.empty(); }


  //  The following three functions are used for debugging.

  //  Check to see that internally the heap property is realized.
  bool check_heap( )
  {
    return this->check_heap( this->m_heap );
  }

  //  Check an external vector to see that the heap property is realized.
  bool check_heap( const std::vector<T>& heap ) {
    if (heap.size()==0||heap.size()==1) {
      return true;
    }
    for (int u = heap.size()-1; u > -1; u--) {
      int i = u;
      int pI = (i-1)/2;
      if (heap[i]<heap[pI]) {
        return false;
      }
    }
    return true;
  }

  //  A utility to print the contents of the heap.  Use it for debugging.
  void print_heap( std::ostream & ostr )
  {
    for ( unsigned int i=0; i<m_heap.size(); ++i )
      ostr << i << ": " << m_heap[i] << std::endl;
  }
  
};


template <class T>
void heap_sort( std::vector<T> & v ) {
  for (int n = 0; n < v.size(); v++) {
    
  }
}

#endif
