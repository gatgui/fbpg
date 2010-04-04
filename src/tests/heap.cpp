#include "heap.h"
#include <iostream>

int main(int, char**) {
  HeapManager h(Heap::Kb(1));
  
  h.status();
  
  std::cerr << "== Allocate 256 bytes" << std::endl;
  void *p0 = h.allocate(256);
  h.status();
  
  std::cerr << "== Allocate 128 bytes" << std::endl;
  void *p1 = h.allocate(128);
  h.status();
  
  std::cerr << "== Allocate 765 bytes" << std::endl;
  void *p2 = h.allocate(765);
  h.status();
  
  std::cerr << "== Allocate 640 bytes" << std::endl;
  void *p3 = h.allocate(640);
  h.status();
  
  std::cerr << "== Free the 128 bytes" << std::endl;
  h.deallocate(p1, 128);
  p1 = 0;
  h.status();
  
  std::cerr << "== Free the 256 bytes" << std::endl;
  h.deallocate(p0, 256);
  p0 = 0;
  h.status();
  
  std::cerr << "== Allocate 4 Mbytes" << std::endl;
  p0 = h.allocate(Heap::Mb(4));
  h.status();
  
  std::cerr << "== Free all" << std::endl;
  h.deallocate(p0, Heap::Mb(4));
  h.deallocate(p2, 765);
  h.deallocate(p3, 640);
  h.status();
  
  return 0;
}
