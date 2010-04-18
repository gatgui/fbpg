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
  
#ifdef _MEMMGR
  HeapManager heap;
#endif
  
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
    int p = rand() % nstrings;
    int s = rand() % nstrings;
    skeys[i]  = strpool[p];
    skeys[i] += strpool[s];
  }
  
  from = clock();
  for (int i=0; i<nelems; ++i) {
    lhash.insert(lkeys[i], rand());
  }
  to = clock();
  diff = double(to - from) / CLOCKS_PER_SEC;
  std::cout << "LongHash fill " << nelems << " values: " << diff << " (s)" << std::endl;
  from = clock();
  for (int i=0; i<nelems; ++i) {
    lmap[lkeys[i]] = rand();
  }
  to = clock();
  diff = double(to - from) / CLOCKS_PER_SEC;
  std::cout << "LongMap fill " << nelems << " values: " << diff << " (s)" << std::endl;
  from = clock();
  for (int i=0; i<nelems; ++i) {
    shash.insert(skeys[i], rand());
  }
  to = clock();
  diff = double(to - from) / CLOCKS_PER_SEC;
  std::cout << "StringHash fill " << nelems << " values: " << diff << " (s)" << std::endl;
  from = clock();
  for (int i=0; i<nelems; ++i) {
    smap[skeys[i]] = rand();
  }
  to = clock();
  diff = double(to - from) / CLOCKS_PER_SEC;
  std::cout << "StringMap fill " << nelems << " values: " << diff << " (s)" << std::endl;
  
  
  // check datas
  /*
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
  */
  
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
  
  // test random keys
  // should make it so we have around 50% chances to find the element
  // build a new key array
  size_t numhits = 0;
  double hitperc = 0.0;
  std::vector<long> rkeys(2*nelems);
  for (size_t i=0; i<lkeys.size(); ++i) {
    rkeys[i] = lkeys[i];
  }
  for (size_t i=nelems; i<size_t(2 * nelems); ++i) {
    rkeys[i] = rand();
  }
  
  from = clock();
  for (int i=0; i<naccess; ++i) {
    long k = rkeys[rand() % (2 * nelems)];
    long v;
    if (lhash.getValue(k, v)) {
    //if (lhash.hasKey(k)) {
      ++numhits;
      //long v = lhash.getValue(k);
    }
  }
  to = clock();
  diff = double(to - from) / CLOCKS_PER_SEC;
  hitperc = double(numhits) / double(naccess);
  std::cout << "LongHash " << naccess << " random keys: "
            << diff << " (s) [" << (hitperc*100) << " % hit]" << std::endl;
  
  /*
  HashMap<long, long>::iterator hit;
  numhits = 0;
  from = clock();
  for (int i=0; i<naccess; ++i) {
    long k = rkeys[rand() % (2 * nelems)];
    hit = lhash.find(k);
    if (hit != lhash.end()) {
      ++numhits;
      long v = hit->second;
    }
  }
  to = clock();
  diff = double(to - from) / CLOCKS_PER_SEC;
  hitperc = double(numhits) / double(naccess);
  std::cout << "LongHash " << naccess << " random keys: "
            << diff << " (s) [" << (hitperc*100) << " % hit, using iterators]" << std::endl;
  */
  
  std::map<long,long>::iterator mit;
  numhits = 0;
  from = clock();
  for (int i=0; i<naccess; ++i) {
    long k = rkeys[rand() % (2 * nelems)];
    mit = lmap.find(k);
    if (mit != lmap.end()) {
      ++numhits;
      long v = mit->second;
    }
  }
  to = clock();
  diff = double(to - from) / CLOCKS_PER_SEC;
  hitperc = double(numhits) / double(naccess);
  std::cout << "LongMap " << naccess << " random keys: "
            << diff << " (s) [" << (hitperc*100) << " % hit]" << std::endl;
  
  return 0;
}
