#include "hashmap.h"
#include <vector>
#include <map>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

typedef HashMap<long, long>  LongHash;
typedef std::map<long, long> LongMap;

typedef HashMap<std::string, long>  StringHash;
typedef std::map<std::string, long> StringMap;

// HashMap is slower with small number of elements

int main(int argc, char **argv) {
  
  clock_t from, to;
  double diff;
  
  LongHash lhash;
  LongMap lmap;
  StringHash shash;
  StringMap smap;
  
  srand(clock());
  
  int nelems = 10;
  int naccess = 100;
  
  if (argc >= 2) {
    sscanf(argv[1], "%d", &nelems);
  }
  if (argc >= 3) {
    sscanf(argv[2], "%d", &naccess);
  }
  
  const char *strpool[] = {
    "hello",
    "_",
    "world",
    "012",
    "before",
    "after",
    "if",
    "then",
    "else",
    "for",
    "while",
    "do",
    "@",
    "~",
    "+",
    "-",
    "function",
    "class"
  };
  size_t nstrings = sizeof(strpool) / sizeof(const char*);
  
  // fill elements
  std::vector<std::string> skeys(nelems);
  std::vector<long> lkeys(nelems);
  std::cout << "Buid hash and map with " << nelems << " elements" << std::endl;
  for (int i=0; i<nelems; ++i) {
    long k = rand();
    lkeys[i] = k;
    long v = rand();
    lhash.insert(k, v);
    lmap[k] = v;
    int p = rand() % nstrings;
    int s = rand() % nstrings;
    skeys[i]  = strpool[p];
    skeys[i] += strpool[s];
    shash.insert(skeys[i], v);
    smap[skeys[i]] = v;
    //std::cout << "  Add long key: " << lkeys[i] << std::endl;
    //std::cout << "  Add string key: " << skeys[i] << std::endl;
  }
  
  // check datas
  std::cout << "Check data" << std::endl;
  for (int k=0; k<nelems; ++k) {
    long v0 = lhash.getValue(lkeys[k]);
    long v1 = lmap[lkeys[k]];
    if (v0 != v1) {
      std::cout << "Data mismatch at long key \"" << lkeys[k] << "\"" << std::endl;
    }
    v0 = shash.getValue(skeys[k]);
    v1 = smap[skeys[k]];
    if (v0 != v1) {
      std::cout << "Data mismatch at std::string key \"" << skeys[k] << "\"" << std::endl;
    }
  }
  
  // test long map
  from = clock();
  for (int i=0; i<naccess; ++i) {
    long k = rand() % nelems;
    long v = lhash.getValue(lkeys[k]);
  }
  to = clock();
  diff = double(to - from) / CLOCKS_PER_SEC;
  std::cout << "LongHash " << naccess << " random access: " << diff << " (s)" << std::endl;
  from = clock();
  for (int i=0; i<naccess; ++i) {
    long k = rand() % nelems;
    long v = lmap[lkeys[k]];
  }
  to = clock();
  diff = double(to - from) / CLOCKS_PER_SEC;
  std::cout << "LongMap " << naccess << " random access: " << diff << " (s)" << std::endl;
  
  // test string map
  from = clock();
  for (int i=0; i<naccess; ++i) {
    long k = rand() % nelems;
    long v = shash.getValue(skeys[k]);
  }
  to = clock();
  diff = double(to - from) / CLOCKS_PER_SEC;
  std::cout << "StringHash " << naccess << " random access: " << diff << " (s)" << std::endl;
  from = clock();
  for (int i=0; i<naccess; ++i) {
    long k = rand() % nelems;
    long v = smap[skeys[k]];
  }
  to = clock();
  diff = double(to - from) / CLOCKS_PER_SEC;
  std::cout << "StringMap " << naccess << " random access: " << diff << " (s)" << std::endl;
  
  return 0;
}
