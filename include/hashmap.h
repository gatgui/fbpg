#ifndef __hashmap_h_
#define __hashmap_h_

#include <string>
#include <vector>
#include <list>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#ifdef _MEMMGR
#include "heap.h"
#endif

// --- Hash function prototype

typedef unsigned int (*HashFunc)(const unsigned char *, size_t);

template <typename T, HashFunc H>
struct HashValue {
  inline static unsigned int Compute(const T &val) {
    return H((const unsigned char *)&val, sizeof(T));
  }
};

// --- Hash functions

unsigned int hash_djb(const unsigned char *data, size_t len);
unsigned int hash_jenkins(const unsigned char *data, size_t len);
unsigned int hash_fnv1(const unsigned char *data, size_t len);
unsigned int hash_fnv1a(const unsigned char *data, size_t len);
unsigned int hash_murmur2(const unsigned char *data_in, size_t len);
unsigned int hash_murmur2a(const unsigned char *data_in, size_t len);

// ---

template <typename KeyType, typename ValueType, HashFunc H=hash_jenkins>
class HashMap {
  public:
    
    #ifdef _MEMMGR
    class Entry : public HeapObject
    #else
    class Entry
    #endif
    {
      public:
        
        Entry();
        Entry(const Entry &rhs);
        virtual ~Entry();
        
        Entry& operator=(const Entry &rhs);
        bool operator==(const Entry &rhs) const;
      
      public:
        
        KeyType first;
        ValueType second;
        unsigned int h;
        Entry *next;
    };
    
    typedef typename std::vector<KeyType> KeyVector;
    typedef typename std::vector<ValueType> ValueVector;
    typedef typename std::pair<KeyType, ValueType> KeyValuePair;
    typedef typename std::vector<KeyValuePair> KeyValueVector;
    
  public:
    
    HashMap();
    HashMap(const HashMap &rhs);
    ~HashMap();
    
    HashMap& operator=(const HashMap &rhs);
    
    double loadFactor() const;
    
    size_t size() const;
    void clear();
    void insert(const KeyType &key, const ValueType &val);
    void erase(const KeyType &k);
    bool hasKey(const KeyType &key) const;
    const ValueType& getValue(const KeyType &k) const;
    ValueType& getValue(const KeyType &k);
    bool getValue(const KeyType &k, ValueType &v) const;
    
    size_t getKeys(KeyVector &kl) const;
    size_t getValues(ValueVector &vl) const;
    size_t getPairs(KeyValueVector &kvl) const;
    
    Entry* find(const KeyType &key);
    const Entry* find(const KeyType &key) const;
    void erase(Entry *e);
    
    Entry* first();
    Entry* next();
    
    const Entry* first() const;
    const Entry* next() const;
    
  protected:
    
    void expand();
    
  protected:
    
    Entry **mBuckets;
    size_t mNumBuckets;
    size_t mNumEntries;
    size_t mBucketsMask;
    
    mutable size_t mItCurBucket;
    mutable Entry *mItCurEntry;
};

// ---

template <HashFunc H>
struct HashValue<char*, H> {
  inline static unsigned int Compute(const char* &val) {
    return H((const unsigned char *)val, strlen(val));
  }
};

template <HashFunc H>
struct HashValue<std::string, H> {
  inline static unsigned int Compute(const std::string &val) {
    return H((const unsigned char *)val.c_str(), val.length());
  }
};

template <HashFunc H>
struct HashValue<char, H> {
  inline static unsigned int Compute(const char &val) {
    return (unsigned int)val;
  }
};

template <HashFunc H>
struct HashValue<unsigned char, H> {
  inline static unsigned int Compute(const unsigned char &val) {
    return (unsigned int)val;
  }
};

template <HashFunc H>
struct HashValue<short, H> {
  inline static unsigned int Compute(const short &val) {
    return (unsigned int)val;
  }
};

template <HashFunc H>
struct HashValue<unsigned short, H> {
  inline static unsigned int Compute(const unsigned short &val) {
    return (unsigned int)val;
  }
};

template <HashFunc H>
struct HashValue<int, H> {
  inline static unsigned int Compute(const int &val) {
    return (unsigned int)val;
  }
};

template <HashFunc H>
struct HashValue<unsigned int, H> {
  inline static unsigned int Compute(const unsigned int &val) {
    return (unsigned int)val;
  }
};

template <HashFunc H>
struct HashValue<long, H> {
  inline static unsigned int Compute(const long &val) {
    return (unsigned int)val;
  }
};

template <HashFunc H>
struct HashValue<unsigned long, H> {
  inline static unsigned int Compute(const unsigned long &val) {
    return (unsigned int)val;
  }
};

template <HashFunc H>
struct HashValue<float, H> {
  inline static unsigned int Compute(const float &val) {
    return (unsigned int)(*((unsigned int*)&val));
  }
};

template <HashFunc H>
struct HashValue<double, H> {
  inline static unsigned int Compute(const double &val) {
    return (unsigned int)(*((unsigned int*)&val));
  }
};

// ---

template <typename KeyType, typename ValueType, HashFunc H>
HashMap<KeyType, ValueType, H>::Entry::Entry()
  : next(0) {
}

template <typename KeyType, typename ValueType, HashFunc H>
HashMap<KeyType, ValueType, H>::Entry::Entry(const Entry &rhs)
  : first(rhs.first), second(rhs.second), h(rhs.h), next(0) {
}

template <typename KeyType, typename ValueType, HashFunc H>
HashMap<KeyType, ValueType, H>::Entry::~Entry() {
}

template <typename KeyType, typename ValueType, HashFunc H>
typename HashMap<KeyType, ValueType, H>::Entry&
HashMap<KeyType, ValueType, H>::Entry::operator=(
  const typename HashMap<KeyType, ValueType, H>::Entry &rhs)
{
  if (this != &rhs) {
    first = rhs.first;
    second = rhs.second;
    h = rhs.h;
  }
  return *this;
}

template <typename KeyType, typename ValueType, HashFunc H>
bool HashMap<KeyType, ValueType, H>::Entry::operator==(
  const typename HashMap<KeyType, ValueType, H>::Entry &rhs) const
{
  return ((h == rhs.h) && (first == rhs.first));
}

// ---

template <typename KeyType, typename ValueType, HashFunc H>
HashMap<KeyType, ValueType, H>::HashMap()
  : mNumBuckets(16), mNumEntries(0), mBucketsMask(0x0000000F),
    mItCurBucket(0), mItCurEntry(0) {
  mBuckets = new Entry*[16];
  memset(mBuckets, 0, 16*sizeof(Entry*));
}

template <typename KeyType, typename ValueType, HashFunc H>
HashMap<KeyType, ValueType, H>::HashMap(const HashMap &rhs)
  : mBuckets(0), mNumBuckets(rhs.mNumBuckets),
    mNumEntries(rhs.mNumEntries), mBucketsMask(rhs.mBucketsMask),
    mItCurBucket(0), mItCurEntry(0) {
  Entry *c=0, *f=0, *e=0, *p=0;
  mBuckets = new Entry*[mNumBuckets];
  for (size_t i=0; i<mNumBuckets; ++i) {
    c = rhs.mBuckets[i];
    f = 0;
    if (c != 0) {
      f = new Entry(*c);
      p = f;
      while (c->next) {
        c = c->next;
        e = new Entry(*c);
        p->next = e;
        p = e;
      }
    }
    mBuckets[i] = f;
  }
}

template <typename KeyType, typename ValueType, HashFunc H>
HashMap<KeyType, ValueType, H>::~HashMap() {
  for (size_t i=0; i<mNumBuckets; ++i) {
    Entry *c = mBuckets[i];
    Entry *n = 0;
    while (c) {
      n = c->next;
      delete c;
      c = n;
    }
  }
  delete[] mBuckets;
}

template <typename KeyType, typename ValueType, HashFunc H>
HashMap<KeyType, ValueType, H>& HashMap<KeyType, ValueType, H>::operator=(
  const HashMap<KeyType, ValueType, H> &rhs)
{
  if (this != &rhs) {
    if (mBuckets) {
      for (size_t i=0; i<mNumBuckets; ++i) {
        Entry *c = mBuckets[i];
        while (c) {
          Entry *n = c->next;
          delete c;
          c = n;
        }
      }
      delete[] mBuckets;
    }
    
    mNumEntries = rhs.mNumEntries;
    mNumBuckets = rhs.mNumBuckets;
    mBucketsMask = rhs.mBucketsMask;
    mItCurBucket = 0;
    mItCurEntry = 0;
    
    mBuckets = new Entry*[mNumBuckets];
    
    for (size_t i=0; i<mNumBuckets; ++i) {
      Entry *c = rhs.mBuckets[i];
      Entry *f = 0;
      Entry *p = 0;
      if (c != 0) {
        f = new Entry(*c);
        p = f;
        while (c->next) {
          c = c->next;
          Entry *e = new Entry(*c);
          p->next = e;
          p = e;
        }
      }
      mBuckets[i] = f;
    }
  }
  return *this;
}

template <typename KeyType, typename ValueType, HashFunc H>
inline typename HashMap<KeyType, ValueType, H>::Entry*
HashMap<KeyType, ValueType, H>::first() {
  mItCurBucket = 0;
  mItCurEntry  = mBuckets[mItCurBucket];
  while (mItCurEntry == 0 && (mItCurBucket+1) < mNumBuckets) {
    mItCurEntry = mBuckets[++mItCurBucket];
  }
  return mItCurEntry;
}

template <typename KeyType, typename ValueType, HashFunc H>
inline typename HashMap<KeyType, ValueType, H>::Entry*
HashMap<KeyType, ValueType, H>::next() {
  if (mItCurEntry) {
    mItCurEntry = mItCurEntry->next;
    if (!mItCurEntry) {
      while (++mItCurBucket < mNumBuckets) {
        if (mBuckets[mItCurBucket] != 0) {
          mItCurEntry = mBuckets[mItCurBucket];
          break;
        }
      }
    }
  }
  return mItCurEntry;
}

template <typename KeyType, typename ValueType, HashFunc H>
inline const typename HashMap<KeyType, ValueType, H>::Entry*
HashMap<KeyType, ValueType, H>::first() const {
  mItCurBucket = 0;
  mItCurEntry  = mBuckets[mItCurBucket];
  while (mItCurEntry == 0 && (mItCurBucket+1) < mNumBuckets) {
    mItCurEntry = mBuckets[++mItCurBucket];
  }
  return mItCurEntry;
}

template <typename KeyType, typename ValueType, HashFunc H>
inline const typename HashMap<KeyType, ValueType, H>::Entry*
HashMap<KeyType, ValueType, H>::next() const {
  if (mItCurEntry) {
    mItCurEntry = mItCurEntry->next;
    if (!mItCurEntry) {
      while (++mItCurBucket < mNumBuckets) {
        if (mBuckets[mItCurBucket] != 0) {
          mItCurEntry = mBuckets[mItCurBucket];
          break;
        }
      }
    }
  }
  return mItCurEntry;
}


template <typename KeyType, typename ValueType, HashFunc H>
inline double HashMap<KeyType, ValueType, H>::loadFactor() const {
  return (double(mNumEntries) / double(mNumBuckets));
}

template <typename KeyType, typename ValueType, HashFunc H>
inline size_t HashMap<KeyType, ValueType, H>::size() const {
  return mNumEntries;
}

template <typename KeyType, typename ValueType, HashFunc H>
void HashMap<KeyType, ValueType, H>::insert(const KeyType &key, const ValueType &val) {
  register unsigned int h = HashValue<KeyType, H>::Compute(key);
  register unsigned int idx = h & mBucketsMask;
  Entry *e = mBuckets[idx];
  while (e && e->first != key) {
    e = e->next;
  }
  if (e == 0) {
    e = new Entry();
    e->h = h;
    e->first = key;
    e->second = val;
    e->next = mBuckets[idx];
    mBuckets[idx] = e;
    ++mNumEntries;
    if ((mNumEntries << 1) > mNumBuckets) {
      expand();
    }
  } else {
    e->second = val;
  }
}

template <typename KeyType, typename ValueType, HashFunc H>
void HashMap<KeyType, ValueType, H>::erase(const KeyType &k) {
  register unsigned int h = HashValue<KeyType, H>::Compute(k);
  register unsigned int idx = h & mBucketsMask;
  Entry *e = mBuckets[idx];
  Entry *p = 0;
  while (e && e->first != k) {
    p = e;
    e = e->next;
  }
  if (e != 0) {
    if (p) {
      p->next = e->next;
    } else {
      mBuckets[idx] = e->next;
    }
    delete e;
    --mNumEntries;
  }
}

template <typename KeyType, typename ValueType, HashFunc H>
void HashMap<KeyType, ValueType, H>::clear() {
  mNumEntries = 0;
  for (size_t i=0; i<mNumBuckets; ++i) {
    Entry *c = mBuckets[i];
    Entry *n = 0;
    while (c) {
      n = c->next;
      delete c;
      c = n;
    }
    mBuckets[i] = 0;
  }
}

template <typename KeyType, typename ValueType, HashFunc H>
bool HashMap<KeyType, ValueType, H>::hasKey(const KeyType &key) const {
  register unsigned int h = HashValue<KeyType, H>::Compute(key);
  register unsigned int idx = h & mBucketsMask;
  const Entry *e = mBuckets[idx];
  while (e && e->first != key) {
    e = e->next;
  }
  return (e != 0);
}

template <typename KeyType, typename ValueType, HashFunc H>
const ValueType& HashMap<KeyType, ValueType, H>::getValue(const KeyType &k) const {
  register unsigned int h = HashValue<KeyType, H>::Compute(k);
  register unsigned int idx = h & mBucketsMask;
  const Entry *e = mBuckets[idx];
  while (e && e->first != k) {
    e = e->next;
  }
  if (e == 0) {
    std::ostringstream oss;
    oss << "Invalid key: " << k;
    throw std::runtime_error(oss.str());
  }
  return e->second;
}

template <typename KeyType, typename ValueType, HashFunc H>
ValueType& HashMap<KeyType, ValueType, H>::getValue(const KeyType &k) {
  register unsigned int h = HashValue<KeyType, H>::Compute(k);
  register unsigned int idx = h & mBucketsMask;
  Entry *e = mBuckets[idx];
  while (e && e->first != k) {
    e = e->next;
  }
  if (e == 0) {
    std::ostringstream oss;
    oss << "Invalid key: " << k;
    throw std::runtime_error(oss.str());
  }
  return e->second;
}

template <typename KeyType, typename ValueType, HashFunc H>
bool HashMap<KeyType, ValueType, H>::getValue(const KeyType &k, ValueType &v) const {
  register unsigned int h = HashValue<KeyType, H>::Compute(k);
  register unsigned int idx = h & mBucketsMask;
  const Entry *e = mBuckets[idx];
  while (e && e->first != k) {
    e = e->next;
  }
  if (e == 0) {
    return false;
  } else {
    v = e->second;
    return true;
  }
}

template <typename KeyType, typename ValueType, HashFunc H>
size_t HashMap<KeyType, ValueType, H>::getKeys(KeyVector &kl) const {
  kl.resize(mNumEntries);
  for (size_t i=0, j=0; i<mNumBuckets; ++i) {
    const Entry *e = mBuckets[i];
    while (e) {
      kl[j++] = e->first;
      e = e->next;
    }
  }
  return kl.size();
}

template <typename KeyType, typename ValueType, HashFunc H>
size_t HashMap<KeyType, ValueType, H>::getValues(ValueVector &vl) const {
  vl.resize(mNumEntries);
  for (size_t i=0, j=0; i<mNumBuckets; ++i) {
    const Entry *e = mBuckets[i];
    while (e) {
      vl[j++] = e->second;
      e = e->next;
    }
  }
  return vl.size();
}

template <typename KeyType, typename ValueType, HashFunc H>
size_t HashMap<KeyType, ValueType, H>::getPairs(KeyValueVector &kvl) const {
  kvl.resize(mNumEntries);
  for (size_t i=0, j=0; i<mNumBuckets; ++i) {
    const Entry *e = mBuckets[i];
    while (e) {
      kvl[j++] = KeyValuePair(e->first, e->second);
      e = e->next;
    }
  }
  return kvl.size();
}

template <typename KeyType, typename ValueType, HashFunc H>
typename HashMap<KeyType, ValueType, H>::Entry*
HashMap<KeyType, ValueType, H>::find(const KeyType &key) {
  register unsigned int h = HashValue<KeyType, H>::Compute(key);
  register unsigned int idx = h & mBucketsMask;
  Entry *e = mBuckets[idx];
  while (e && e->first != key) {
    e = e->next;
  }
  return e;
}

template <typename KeyType, typename ValueType, HashFunc H>
const typename HashMap<KeyType, ValueType, H>::Entry*
HashMap<KeyType, ValueType, H>::find(const KeyType &key) const {
  register unsigned int h = HashValue<KeyType, H>::Compute(key);
  register unsigned int idx = h & mBucketsMask;
  const Entry *e = mBuckets[idx];
  while (e && e->first != key) {
    e = e->next;
  }
  return e;
}

template <typename KeyType, typename ValueType, HashFunc H>
void HashMap<KeyType, ValueType, H>::erase(typename HashMap<KeyType, ValueType, H>::Entry *e) {
  register unsigned int idx = e->h & mBucketsMask;
  Entry *c = mBuckets[idx];
  Entry *p = 0;
  while (c && c != e) {
    p = c;
    c = c->next;
  }
  if (e != 0) {
    if (p != 0) {
      p->next = e->next;
    } else {
      mBuckets[idx] = e->next;
    }
    delete e;
    --mNumEntries;
  }
}

template <typename KeyType, typename ValueType, HashFunc H>
void HashMap<KeyType, ValueType, H>::expand() {
  register unsigned int idx;
  register size_t oNumBuckets = mNumBuckets;
  mNumBuckets = mNumBuckets << 1;
  mBucketsMask = (mBucketsMask << 1) | 1;
  Entry **newBuckets = new Entry*[mNumBuckets];
  memset(newBuckets, 0, mNumBuckets*sizeof(Entry*));
  for (size_t i=0; i<oNumBuckets; ++i) {
    Entry *e = mBuckets[i];
    Entry *n = 0;
    while (e) {
      n = e->next;
      idx = e->h & mBucketsMask;
      e->next = newBuckets[idx];
      newBuckets[idx] = e;
      e = n;
    }
  }
  delete[] mBuckets;
  mBuckets = newBuckets;
}

#endif
