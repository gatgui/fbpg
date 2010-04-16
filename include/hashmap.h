#ifndef __hashmap_h_
#define __hashmap_h_

#include <string>
#include <vector>
#include <list>
#include <sstream>
#include <stdexcept>
#include <algorithm>

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
    
    struct Entry {
      KeyType first;
      ValueType second;
      unsigned int h;
      
      bool operator==(const Entry &rhs) const;
    };
    
    typedef typename std::pair<KeyType, ValueType> KeyValuePair;
    typedef typename std::list<Entry> EntryList;
    typedef typename std::vector<KeyType> KeyVector;
    typedef typename std::vector<ValueType> ValueVector;
    typedef typename std::vector<KeyValuePair> KeyValueVector;
    typedef typename std::vector<EntryList> EntryListVector;
    
    // implement iterators
    
    class iterator {
      public:
        friend class HashMap;
        
        iterator();
        iterator(const iterator &rhs);
        ~iterator();
        
        iterator& operator=(const iterator &rhs);
        bool operator==(const iterator &rhs) const;
        bool operator!=(const iterator &rhs) const;
        Entry& operator*();
        Entry* operator->();
        iterator& operator++();
        iterator operator++(int);
        
      protected:
        iterator(typename EntryListVector::iterator bend,
                 typename EntryListVector::iterator bit);
        iterator(typename EntryListVector::iterator bend,
                 typename EntryListVector::iterator bit,
                 typename EntryList::iterator eit);
        
      protected:
        typename EntryListVector::iterator mBEnd;
        typename EntryListVector::iterator mBIt;
        typename EntryList::iterator mEIt;
    };
    
    class const_iterator {
      public:
        friend class HashMap;
        
        const_iterator();
        const_iterator(const const_iterator &rhs);
        ~const_iterator();
        
        const_iterator& operator=(const const_iterator &rhs);
        bool operator==(const const_iterator &rhs) const;
        bool operator!=(const const_iterator &rhs) const;
        const Entry& operator*();
        const Entry* operator->();
        const_iterator& operator++();
        const_iterator operator++(int);
        
      protected:
        const_iterator(typename EntryListVector::const_iterator bend,
                       typename EntryListVector::const_iterator bit);
        const_iterator(typename EntryListVector::const_iterator bend,
                       typename EntryListVector::const_iterator bit,
                       typename EntryList::const_iterator eit);
        
      protected:
        typename EntryListVector::const_iterator mBEnd;
        typename EntryListVector::const_iterator mBIt;
        typename EntryList::const_iterator mEIt;
    };
    
    
  public:
    
    HashMap(); //size_t numBuckets=16);
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
    
    iterator begin();
    iterator end();
    iterator find(const KeyType &k);
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator find(const KeyType &k) const;
    void erase(const iterator &it);
    ValueType& operator[](const KeyType &k);
    const ValueType& operator[](const KeyType &k) const;
    
  protected:
    
    void expand();
    
  protected:
    
    EntryListVector mBuckets;
    size_t mNumBuckets;
    size_t mNumEntries;
    size_t mBucketsMask;
    
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

/* size_t == unsigned long
template <HashFunc H>
struct HashValue<size_t, H> {
  inline static unsigned int Compute(const size_t &val) {
    return (unsigned int)val;
  }
};
*/

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
inline HashMap<KeyType, ValueType, H>::iterator::iterator() {
}

template <typename KeyType, typename ValueType, HashFunc H>
inline HashMap<KeyType, ValueType, H>::iterator::iterator(
  typename HashMap<KeyType, ValueType, H>::EntryListVector::iterator bend,
  typename HashMap<KeyType, ValueType, H>::EntryListVector::iterator bit)
  : mBEnd(bend), mBIt(bit) {
}

template <typename KeyType, typename ValueType, HashFunc H>
inline HashMap<KeyType, ValueType, H>::iterator::iterator(
  typename HashMap<KeyType, ValueType, H>::EntryListVector::iterator bend,
  typename HashMap<KeyType, ValueType, H>::EntryListVector::iterator bit,
  typename HashMap<KeyType, ValueType, H>::EntryList::iterator eit)
  : mBEnd(bend), mBIt(bit), mEIt(eit) {
}

template <typename KeyType, typename ValueType, HashFunc H>
inline HashMap<KeyType, ValueType, H>::iterator::iterator(
  const typename HashMap<KeyType, ValueType, H>::iterator &rhs)
  : mBEnd(rhs.mBEnd), mBIt(rhs.mBIt), mEIt(rhs.mEIt) {
}

template <typename KeyType, typename ValueType, HashFunc H>
inline HashMap<KeyType, ValueType, H>::iterator::~iterator() {
}

template <typename KeyType, typename ValueType, HashFunc H>
inline typename HashMap<KeyType, ValueType, H>::iterator&
HashMap<KeyType, ValueType, H>::iterator::operator=(
  const typename HashMap<KeyType, ValueType, H>::iterator &rhs)
{
  if (this != &rhs) {
    mBEnd = rhs.mBEnd;
    mBIt = rhs.mBIt;
    mEIt = rhs.mEIt;
  }
  return *this;
}

template <typename KeyType, typename ValueType, HashFunc H>
inline bool HashMap<KeyType, ValueType, H>::iterator::operator==(
  const typename HashMap<KeyType, ValueType, H>::iterator &rhs) const
{
  if ((mBIt != rhs.mBIt) ||
      (mBIt != mBEnd && mEIt != rhs.mEIt)) {
    return false;
  }
  return true;
}

template <typename KeyType, typename ValueType, HashFunc H>
inline bool HashMap<KeyType, ValueType, H>::iterator::operator!=(
  const typename HashMap<KeyType, ValueType, H>::iterator &rhs) const
{
  return !operator==(rhs);
}

template <typename KeyType, typename ValueType, HashFunc H>
inline typename HashMap<KeyType, ValueType, H>::Entry&
HashMap<KeyType, ValueType, H>::iterator::operator*() {
  return *mEIt;
}

template <typename KeyType, typename ValueType, HashFunc H>
inline typename HashMap<KeyType, ValueType, H>::Entry*
HashMap<KeyType, ValueType, H>::iterator::operator->() {
  return &(*mEIt);
}

template <typename KeyType, typename ValueType, HashFunc H>
inline typename HashMap<KeyType, ValueType, H>::iterator&
HashMap<KeyType, ValueType, H>::iterator::operator++() {
  if (mBIt == mBEnd) {
    return *this;
  }
  if (++mEIt == mBIt->end()) {
    while (++mBIt != mBEnd) {
      if (mBIt->size() > 0) {
        mEIt = mBIt->begin();
        break;
      }
    }
  }
  return *this;
}

template <typename KeyType, typename ValueType, HashFunc H>
inline typename HashMap<KeyType, ValueType, H>::iterator
HashMap<KeyType, ValueType, H>::iterator::operator++(int) {
  typename HashMap<KeyType, ValueType, H>::iterator rv(*this);
  operator++();
  return rv;
}

// ---

template <typename KeyType, typename ValueType, HashFunc H>
inline HashMap<KeyType, ValueType, H>::const_iterator::const_iterator() {
}

template <typename KeyType, typename ValueType, HashFunc H>
inline HashMap<KeyType, ValueType, H>::const_iterator::const_iterator(
  typename HashMap<KeyType, ValueType, H>::EntryListVector::const_iterator bend,
  typename HashMap<KeyType, ValueType, H>::EntryListVector::const_iterator bit)
  : mBEnd(bend), mBIt(bit) {
}


template <typename KeyType, typename ValueType, HashFunc H>
inline HashMap<KeyType, ValueType, H>::const_iterator::const_iterator(
  typename HashMap<KeyType, ValueType, H>::EntryListVector::const_iterator bend,
  typename HashMap<KeyType, ValueType, H>::EntryListVector::const_iterator bit,
  typename HashMap<KeyType, ValueType, H>::EntryList::const_iterator eit)
  : mBEnd(bend), mBIt(bit), mEIt(eit) {
}

template <typename KeyType, typename ValueType, HashFunc H>
inline HashMap<KeyType, ValueType, H>::const_iterator::const_iterator(
  const typename HashMap<KeyType, ValueType, H>::const_iterator &rhs)
  : mBEnd(rhs.mBEnd), mBIt(rhs.mBIt), mEIt(rhs.mEIt) {
}

template <typename KeyType, typename ValueType, HashFunc H>
inline HashMap<KeyType, ValueType, H>::const_iterator::~const_iterator() {
}

template <typename KeyType, typename ValueType, HashFunc H>
inline typename HashMap<KeyType, ValueType, H>::const_iterator&
HashMap<KeyType, ValueType, H>::const_iterator::operator=(
  const typename HashMap<KeyType, ValueType, H>::const_iterator &rhs)
{
  if (this != &rhs) {
    mBEnd = rhs.mBEnd;
    mBIt = rhs.mBIt;
    mEIt = rhs.mEIt;
  }
  return *this;
}

template <typename KeyType, typename ValueType, HashFunc H>
inline bool HashMap<KeyType, ValueType, H>::const_iterator::operator==(
  const typename HashMap<KeyType, ValueType, H>::const_iterator &rhs) const
{
  if ((mBIt != rhs.mBIt) ||
      (mBIt != mBEnd && mEIt != rhs.mEIt)) {
    return false;
  }
  return true;
}

template <typename KeyType, typename ValueType, HashFunc H>
inline bool HashMap<KeyType, ValueType, H>::const_iterator::operator!=(
  const typename HashMap<KeyType, ValueType, H>::const_iterator &rhs) const
{
  return !operator==(rhs);
}

template <typename KeyType, typename ValueType, HashFunc H>
inline const typename HashMap<KeyType, ValueType, H>::Entry&
HashMap<KeyType, ValueType, H>::const_iterator::operator*() {
  return *mEIt;
}

template <typename KeyType, typename ValueType, HashFunc H>
inline const typename HashMap<KeyType, ValueType, H>::Entry*
HashMap<KeyType, ValueType, H>::const_iterator::operator->() {
  return &(*mEIt);
}

template <typename KeyType, typename ValueType, HashFunc H>
inline typename HashMap<KeyType, ValueType, H>::const_iterator&
HashMap<KeyType, ValueType, H>::const_iterator::operator++() {
  if (mBIt == mBEnd) {
    return *this;
  }
  if (++mEIt == mBIt->end()) {
    while (++mBIt != mBEnd) {
      if (mBIt->size() > 0) {
        mEIt = mBIt->begin();
        break;
      }
    }
  }
  return *this;
}

template <typename KeyType, typename ValueType, HashFunc H>
inline typename HashMap<KeyType, ValueType, H>::const_iterator
HashMap<KeyType, ValueType, H>::const_iterator::operator++(int) {
  typename HashMap<KeyType, ValueType, H>::const_iterator rv(*this);
  operator++();
  return rv;
}

// ---

template <typename KeyType, typename ValueType, HashFunc H>
bool HashMap<KeyType, ValueType, H>::Entry::operator==(
  const typename HashMap<KeyType, ValueType, H>::Entry &rhs) const {
  return (h == rhs.h && first == rhs.first);
}

// ---

template <typename KeyType, typename ValueType, HashFunc H>
HashMap<KeyType, ValueType, H>::HashMap() //size_t numBuckets)
  : mNumBuckets(16), mNumEntries(0), mBucketsMask(0x0000000F) {
  mBuckets.resize(mNumBuckets);
}

template <typename KeyType, typename ValueType, HashFunc H>
HashMap<KeyType, ValueType, H>::HashMap(const HashMap &rhs)
  : mBuckets(rhs.mBuckets), mNumBuckets(rhs.mNumBuckets),
    mNumEntries(rhs.mNumEntries), mBucketsMask(rhs.mBucketsMask) {
}

template <typename KeyType, typename ValueType, HashFunc H>
HashMap<KeyType, ValueType, H>::~HashMap() {
  mBuckets.clear();
}

template <typename KeyType, typename ValueType, HashFunc H>
HashMap<KeyType, ValueType, H>& HashMap<KeyType, ValueType, H>::operator=(
  const HashMap<KeyType, ValueType, H> &rhs)
{
  if (this != &rhs) {
    mBuckets = rhs.mBuckets;
    mNumEntries = rhs.mNumEntries;
    mNumBuckets = rhs.mNumBuckets;
    mBucketsMask = rhs.mBucketsMask;
  }
  return *this;
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
  //Entry e;
  //e.h = HashValue<KeyType, H>::Compute(key);
  //e.first = key;
  //unsigned int idx = (e.h % mNumBuckets);
  //EntryList &el = mBuckets[idx];
  //typename EntryList::iterator it = std::find(el.begin(), el.end(), e);
  register unsigned int h = HashValue<KeyType, H>::Compute(key);
  register unsigned int idx = h & mBucketsMask;
  EntryList &el = mBuckets[idx];
  typename EntryList::iterator it = el.begin();
  while (it != el.end()) {
    if (it->first == key) {
      break;
    }
    ++it;
  }
  if (it == el.end()) {
    Entry e;
    e.h = h;
    e.first = key;
    e.second = val;
    el.push_back(e);
    //el.back().second = val;
    ++mNumEntries;
    if (100 * mNumEntries / mNumBuckets > 50) {
      // load factor above 50%
      expand();
    }
  } else {
    it->second = val;
  }
}

template <typename KeyType, typename ValueType, HashFunc H>
void HashMap<KeyType, ValueType, H>::erase(const KeyType &k) {
  //Entry e;
  //e.h = HashValue<KeyType, H>::Compute(k);
  //e.first = k;
  //unsigned int idx = (e.h % mNumBuckets);
  //EntryList &el = mBuckets[idx];
  //typename EntryList::iterator it = std::find(el.begin(), el.end(), e);
  register unsigned int h = HashValue<KeyType, H>::Compute(k);
  register unsigned int idx = h & mBucketsMask;
  EntryList &el = mBuckets[idx];
  typename EntryList::iterator it = el.begin();
  while (it != el.end()) {
    if (it->first == k) {
      break;
    }
    ++it;
  }
  if (it != el.end()) {
    el.erase(it);
    --mNumEntries;
  }
}

template <typename KeyType, typename ValueType, HashFunc H>
void HashMap<KeyType, ValueType, H>::clear() {
  mNumEntries = 0;
  for (size_t i=0; i<mBuckets.size(); ++i) {
    mBuckets[i].clear();
  }
}

template <typename KeyType, typename ValueType, HashFunc H>
bool HashMap<KeyType, ValueType, H>::hasKey(const KeyType &key) const {
  //Entry e;
  //e.h = HashValue<KeyType, H>::Compute(key);
  //e.first = key;
  //unsigned int idx = (e.h % mNumBuckets);
  //const EntryList &el = mBuckets[idx];
  //typename EntryList::const_iterator it = std::find(el.begin(), el.end(), e);
  register unsigned int h = HashValue<KeyType, H>::Compute(key);
  register unsigned int idx = h & mBucketsMask;
  const EntryList &el = mBuckets[idx];
  typename EntryList::const_iterator it = el.begin();
  while (it != el.end()) {
    if (it->first == key) {
      break;
    }
    ++it;
  }
  return (it != el.end());
}

template <typename KeyType, typename ValueType, HashFunc H>
const ValueType& HashMap<KeyType, ValueType, H>::getValue(const KeyType &k) const {
  //Entry e;
  //e.h = HashValue<KeyType, H>::Compute(k);
  //e.first = k;
  //unsigned int idx = (e.h % mNumBuckets);
  //const EntryList &el = mBuckets[idx];
  //typename EntryList::const_iterator it = std::find(el.begin(), el.end(), e);
  register unsigned int h = HashValue<KeyType, H>::Compute(k);
  register unsigned int idx = h & mBucketsMask;
  const EntryList &el = mBuckets[idx];
  typename EntryList::const_iterator it = el.begin();
  while (it != el.end()) {
    if (it->first == k) {
      break;
    }
    ++it;
  }
  if (it == el.end()) {
    std::ostringstream oss;
    oss << "Invalid key: " << k;
    throw std::runtime_error(oss.str());
  }
  return it->second;
}

template <typename KeyType, typename ValueType, HashFunc H>
ValueType& HashMap<KeyType, ValueType, H>::getValue(const KeyType &k) {
  //Entry e;
  //e.h = HashValue<KeyType, H>::Compute(k);
  //e.first = k;
  //unsigned int idx = (e.h % mNumBuckets);
  //EntryList &el = mBuckets[idx];
  //typename EntryList::iterator it = std::find(el.begin(), el.end(), e);
  register unsigned int h = HashValue<KeyType, H>::Compute(k);
  register unsigned int idx = h & mBucketsMask;
  EntryList &el = mBuckets[idx];
  typename EntryList::iterator it = el.begin();
  while (it != el.end()) {
    if (it->first == k) {
      break;
    }
    ++it;
  }
  if (it == el.end()) {
    std::ostringstream oss;
    oss << "Invalid key: " << k;
    throw std::runtime_error(oss.str());
  }
  return it->second;
}

template <typename KeyType, typename ValueType, HashFunc H>
bool HashMap<KeyType, ValueType, H>::getValue(const KeyType &k, ValueType &v) const {
  //Entry e;
  //e.h = HashValue<KeyType, H>::Compute(k);
  //e.first = k;
  //unsigned int idx = (e.h % mNumBuckets);
  //const EntryList &el = mBuckets[idx];
  //typename EntryList::const_iterator it = std::find(el.begin(), el.end(), e);
  register unsigned int h = HashValue<KeyType, H>::Compute(k);
  register unsigned int idx = h & mBucketsMask;
  const EntryList &el = mBuckets[idx];
  typename EntryList::const_iterator it = el.begin();
  while (it != el.end()) {
    if (it->first == k) {
      break;
    }
    ++it;
  }
  if (it == el.end()) {
    return false;
  } else {
    v = it->second;
    return true;
  }
}

template <typename KeyType, typename ValueType, HashFunc H>
size_t HashMap<KeyType, ValueType, H>::getKeys(KeyVector &kl) const {
  kl.resize(mNumEntries);
  for (size_t i=0, j=0; i<mNumBuckets; ++i) {
    const EntryList &el = mBuckets[i];
    typename EntryList::const_iterator it = el.begin();
    while (it != el.end()) {
      kl[j] = it->first;
      ++j;
      ++it;
    }
  }
  return kl.size();
}

template <typename KeyType, typename ValueType, HashFunc H>
size_t HashMap<KeyType, ValueType, H>::getValues(ValueVector &vl) const {
  vl.resize(mNumEntries);
  for (size_t i=0, j=0; i<mNumBuckets; ++i) {
    const EntryList &el = mBuckets[i];
    typename EntryList::const_iterator it = el.begin();
    while (it != el.end()) {
      vl[j] = it->second;
      ++j;
      ++it;
    }
  }
  return vl.size();
}

template <typename KeyType, typename ValueType, HashFunc H>
size_t HashMap<KeyType, ValueType, H>::getPairs(KeyValueVector &kvl) const {
  kvl.resize(mNumEntries);
  for (size_t i=0, j=0; i<mNumBuckets; ++i) {
    const EntryList &el = mBuckets[i];
    typename EntryList::const_iterator it = el.begin();
    while (it != el.end()) {
      kvl[j] = KeyValuePair(it->first, it->second);
      ++j;
      ++it;
    }
  }
  return kvl.size();
}

template <typename KeyType, typename ValueType, HashFunc H>
typename HashMap<KeyType, ValueType, H>::iterator
HashMap<KeyType, ValueType, H>::begin() {
  typename EntryListVector::iterator it = mBuckets.begin();
  while (it != mBuckets.end() && it->size() == 0) {
    ++it;
  }
  if (it != mBuckets.end()) {
    return iterator(mBuckets.end(), it, it->begin());
  } else {
    return iterator(mBuckets.end(), it);
  }
}

template <typename KeyType, typename ValueType, HashFunc H>
typename HashMap<KeyType, ValueType, H>::const_iterator
HashMap<KeyType, ValueType, H>::begin() const {
  typename EntryListVector::const_iterator it = mBuckets.begin();
  while (it != mBuckets.end() && it->size() == 0) {
    ++it;
  }
  if (it != mBuckets.end()) {
    return const_iterator(mBuckets.end(), it, it->begin());
  } else {
    return const_iterator(mBuckets.end(), it);
  }
}

template <typename KeyType, typename ValueType, HashFunc H>
inline typename HashMap<KeyType, ValueType, H>::iterator
HashMap<KeyType, ValueType, H>::end() {
  return iterator(mBuckets.end(), mBuckets.end());
}

template <typename KeyType, typename ValueType, HashFunc H>
inline typename HashMap<KeyType, ValueType, H>::const_iterator
HashMap<KeyType, ValueType, H>::end() const {
  return const_iterator(mBuckets.end(), mBuckets.end());
}

template <typename KeyType, typename ValueType, HashFunc H>
typename HashMap<KeyType, ValueType, H>::iterator
HashMap<KeyType, ValueType, H>::find(const KeyType &k) {
  //Entry e;
  //e.h = HashValue<KeyType, H>::Compute(k);
  //e.first = k;
  //unsigned int idx = (e.h % mNumBuckets);
  //typename EntryListVector::iterator bit = mBuckets.begin() + idx;
  //typename EntryList::iterator eit = std::find(bit->begin(), bit->end(), e);
  register unsigned int h = HashValue<KeyType, H>::Compute(k);
  register unsigned int idx = h & mBucketsMask;
  typename EntryListVector::iterator bit = mBuckets.begin() + idx;
  typename EntryList::iterator eit = bit->begin();
  while (eit != bit->end()) {
    if (eit->first == k) {
      break;
    }
    ++eit;
  }
  if (eit == bit->end()) {
    return iterator(mBuckets.end(), mBuckets.end());
  } else {
    return iterator(mBuckets.end(), bit, eit);
  }
}

template <typename KeyType, typename ValueType, HashFunc H>
typename HashMap<KeyType, ValueType, H>::const_iterator
HashMap<KeyType, ValueType, H>::find(const KeyType &k) const {
  //Entry e;
  //e.h = HashValue<KeyType, H>::Compute(k);
  //e.first = k;
  //unsigned int idx = (e.h % mNumBuckets);
  //typename EntryListVector::const_iterator bit = mBuckets.begin() + idx;
  //typename EntryList::const_iterator eit = std::find(bit->begin(), bit->end(), e);
  register unsigned int h = HashValue<KeyType, H>::Compute(k);
  register unsigned int idx = h & mBucketsMask;
  typename EntryListVector::const_iterator bit = mBuckets.begin() + idx;
  typename EntryList::const_iterator eit = bit->begin();
  while (eit != bit->end()) {
    if (eit->first == k) {
      break;
    }
    ++eit;
  }
  if (eit == bit->end()) {
    return const_iterator(mBuckets.end(), mBuckets.end());
  } else {
    return const_iterator(mBuckets.end(), bit, eit);
  }
}

template <typename KeyType, typename ValueType, HashFunc H>
void HashMap<KeyType, ValueType, H>::erase(
  const typename HashMap<KeyType, ValueType, H>::iterator &it)
{
  if (it != end()) {
    it->mBIt->erase(it->mEIt);
    --mNumEntries;
  }
}

template <typename KeyType, typename ValueType, HashFunc H>
ValueType&
HashMap<KeyType, ValueType, H>::operator[](const KeyType &key) {
  //Entry e;
  //e.h = HashValue<KeyType, H>::Compute(key);
  //e.first = key;
  //unsigned int idx = (e.h % mNumBuckets);
  //EntryList &el = mBuckets[idx];
  //typename EntryList::iterator it = std::find(el.begin(), el.end(), e);
  register unsigned int h = HashValue<KeyType, H>::Compute(key);
  register unsigned int idx = h & mBucketsMask;
  EntryList &el = mBuckets[idx];
  typename EntryList::iterator it = el.begin();
  while (it != el.end()) {
    if (it->first == key) {
      break;
    }
    ++it;
  }
  if (it == el.end()) {
    Entry e;
    e.first = key;
    e.h = h;
    e.second = ValueType();
    el.push_back(e);
    //el.back().second = ValueType();
    ++mNumEntries;
    if (100 * mNumEntries / mNumBuckets > 50) {
      // load factor above 50%
      expand();
      //idx = (e.h % mNumBuckets);
      idx = e.h & mBucketsMask;
      EntryList &el2 = mBuckets[idx];
      //typename EntryList::iterator it = std::find(el2.begin(), el2.end(), e);
      typename EntryList::iterator it = el2.begin();
      while (it != el2.end()) {
        if (it->first == key) {
          break;
        }
        ++it;
      }
      return it->second;
      
    } else {
      return el.back().second;
    }
  } else {
    return it->second;
  }
}

template <typename KeyType, typename ValueType, HashFunc H>
const ValueType&
HashMap<KeyType, ValueType, H>::operator[](const KeyType &key) const {
  //Entry e;
  //e.h = HashValue<KeyType, H>::Compute(key);
  //e.first = key;
  //unsigned int idx = (e.h % mNumBuckets);
  //const EntryList &el = mBuckets[idx];
  //typename EntryList::const_iterator it = std::find(el.begin(), el.end(), e);
  register unsigned int h = HashValue<KeyType, H>::Compute(key);
  register unsigned int idx = h & mBucketsMask;
  const EntryList &el = mBuckets[idx];
  typename EntryList::const_iterator it = el.begin();
  while (it != el.end()) {
    if (it->first == key) {
      break;
    }
    ++it;
  }
  if (it == el.end()) {
    throw std::runtime_error("Invalid Key");
  } else {
    return it->second;
  }
}

template <typename KeyType, typename ValueType, HashFunc H>
void HashMap<KeyType, ValueType, H>::expand() {
  register unsigned int idx;
  register size_t oNumBuckets = mNumBuckets;
  mNumBuckets = mNumBuckets << 1; // x2
  mBucketsMask = (mBucketsMask << 1) | 1;
  EntryListVector buckets(mNumBuckets);
  std::swap(buckets, mBuckets);
  for (size_t i=0; i<oNumBuckets; ++i) {
    EntryList &el = buckets[i];
    typename EntryList::iterator it = el.begin();
    while (it != el.end()) {
      //unsigned int idx = (it->h % mNumBuckets);
      idx = it->h & mBucketsMask;
      mBuckets[idx].push_back(*it);
      ++it;
    }
  }
}

#endif
