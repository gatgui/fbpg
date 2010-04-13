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

// conclusion of those tests
// Hash map with no conflicting keys is faster than std::map with long keys
// Is slower than std::map with std::string keys with few elements be rapidly
// gets faster when the number of elements grows
// what about conflicting keys?

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
  std::vector<std::string> keys(nelems);
  std::cout << "Buid hash and map with " << nelems << " elements" << std::endl;
  for (int k=0; k<nelems; ++k) {
    int v = rand();
    lhash.insert(k, v);
    lmap[k] = v;
    int p = rand() % nstrings;
    int s = rand() % nstrings;
    keys[k]  = strpool[p];
    keys[k] += strpool[s];
    shash.insert(keys[k], v);
    smap[keys[k]] = v;
  }
  
  // check data
  for (int k=0; k<nelems; ++k) {
    long v0 = lhash.getValue(k);
    long v1 = lmap[k];
    if (v0 != v1) {
      std::cout << "Data mismatch at long key \"" << k << "\"" << std::endl;
    }
    v0 = shash.getValue(keys[k]);
    v1 = smap[keys[k]];
    if (v0 != v1) {
      std::cout << "Data mismatch at std::string key \"" << keys[k] << "\"" << std::endl;
    }
  }
  
  from = clock();
  for (int i=0; i<naccess; ++i) {
    long k = rand() % nelems;
    long v = lhash.getValue(k);
  }
  to = clock();
  diff = double(to - from) / CLOCKS_PER_SEC;
  std::cout << "LongHash " << naccess << " random access: " << diff << " (s)" << std::endl;
  from = clock();
  for (int i=0; i<naccess; ++i) {
    long k = rand() % nelems;
    long v = lmap[k];
  }
  to = clock();
  diff = double(to - from) / CLOCKS_PER_SEC;
  std::cout << "LongMap " << naccess << " random access: " << diff << " (s)" << std::endl;
  
  from = clock();
  for (int i=0; i<naccess; ++i) {
    long k = rand() % nelems;
    long v = shash.getValue(keys[k]);
  }
  to = clock();
  diff = double(to - from) / CLOCKS_PER_SEC;
  std::cout << "StringHash " << naccess << " random access: " << diff << " (s)" << std::endl;
  from = clock();
  for (int i=0; i<naccess; ++i) {
    long k = rand() % nelems;
    long v = smap[keys[k]];
  }
  to = clock();
  diff = double(to - from) / CLOCKS_PER_SEC;
  std::cout << "StringMap " << naccess << " random access: " << diff << " (s)" << std::endl;
  
  return 0;
}
