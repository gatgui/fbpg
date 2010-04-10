#include "heap.h"
#include <iostream>
#include <stdexcept>
#include <algorithm>

// ---

inline void* offset(void *ptr, size_t sz) {
  return (void*) (((unsigned char*)ptr) + sz);
}

inline bool operator<(const Heap::Chunk &c0, const Heap::Chunk &c1) {
  return (c0.start < c1.start);
}

#if defined(_DEBUG) && defined(_DEBUG_VERBOSE)
# define PrintDebug(txt) std::cerr << "### " << txt << std::endl
#else
# define PrintDebug(txt)
#endif

// ---

Heap::Heap(size_t initialSize)
  : mHeap(0), mTotalSize(initialSize), mUsedSize(0) {
  mHeap = malloc(initialSize);
  Chunk firstChunk = {mHeap, initialSize};
  mChunks.push_back(firstChunk);
}

Heap::~Heap() {
#ifdef _DEBUG
  if (mUsedSize > 0) {
    std::cerr << "### Heap memory still in use" << std::endl;
  }
#endif
  mChunks.clear();
  free(mHeap);
}

void* Heap::allocate(size_t sz) {
  ChunkList::iterator it = mChunks.begin();
  while (it != mChunks.end()) {
    if (it->size >= sz) {
      void *ptr = it->start;
      it->start = offset(ptr, sz);
      it->size -= sz;
      if (it->size == 0) {
        PrintDebug("Remove empty chunk after allocation");
        mChunks.erase(it);
      }
      mUsedSize += sz;
      return ptr;
    }
    ++it;
  }
  return 0;
}

bool Heap::deallocate(void *ptr, size_t sz) {
  if (ptr < mHeap || ptr >= end()) {
    return false;
  }
  
  mUsedSize -= sz;
  
  Chunk chunk = {ptr, sz};
  
  ChunkList::iterator it = std::lower_bound(mChunks.begin(), mChunks.end(), chunk);
  
  if (it != mChunks.begin()) {
    // have a previous chunk
    ChunkList::iterator pit = it;
    --pit;
    
    if (it == mChunks.end()) {
      // no next chunk
      if (pit->end() == ptr) {
        PrintDebug("Merge with prev free chunk");
        pit->size += sz;
        
      } else {
        PrintDebug("Add new free chunk");
        mChunks.insert(it, chunk);
      }
      
    } else {
      // also have next chunk
      if (pit->end() == ptr) {
        PrintDebug("Merge with prev free chunk");
        pit->size += sz;
        
        if (pit->end() == it->start) {
          PrintDebug("Merge with next free chunk");
          pit->size += it->size;
          mChunks.erase(it);
          
        }
        
      } else {
        if (offset(ptr, sz) == it->start) {
          PrintDebug("Merge with next free chunk");
          it->start = ptr;
          it->size += sz;
        
        } else {
          PrintDebug("Add new free chunk");
          mChunks.insert(it, chunk);
        }
      }
    }
    
  } else {
    // no previous chunk
    if (it == mChunks.end()) {
      // no next chunk
      PrintDebug("Add new free chunk");
      mChunks.insert(it, chunk);
      
    } else {
      // have next chunk
      if (offset(ptr, sz) == it->start) {
        PrintDebug("Merge with next free chunk");
        it->start = ptr;
        it->size += sz;
        
      } else {
        PrintDebug("Add new free chunk");
        mChunks.insert(it, chunk);
        
      }
    }
  }
  
  /*
  ChunkList::iterator it = std::lower_bound(mChunks.begin(), mChunks.end(), chunk);
  
  if (it != mChunks.begin()) {
    // have a previous chunk
    ChunkList::iterator pit = it;
    --pit;
    
    if (it == mChunks.end()) {
      // no next chunk
      
    } else {
      // also have next chunk
    }
    
  } else {
    // no previous chunk
    if (it == mChunks.end()) {
      // no next chunk
      
    } else {
      // have next chunk
    }
  }
  
  if (it != mChunks.end()) {
    // it points to next available chunk
    if (offset(ptr, sz) < it->start) {
      if (it != mChunks.begin()) {
        // theres also a previous chunck
        ChunkList::iterator pit = it;
        --pit;
        if (ptr > pit->end()) {
#ifdef _DEBUG
          std::cerr << "### Add new free chunk" << std::endl;
#endif
          mChunks.insert(it, chunk);
        } else {
#ifdef _DEBUG
          std::cerr << "### Merge with previous free chunk" << std::endl;
#endif
          // merge with prev
          pit->size += sz;
        }
      } else {
        mChunks.insert(it, chunk);
      }
    } else {
      // merge with next
#ifdef _DEBUG
      std::cerr << "### Merge with next free chunk" << std::endl;
#endif
      it->start = ptr;
      it->size += sz;
    }
  
  } else {
    ChunkList::iterator pit = it;
    --pit;
    if (ptr > pit->end()) {
#ifdef _DEBUG
      std::cerr << "### Add new free chunk" << std::endl;
#endif
      mChunks.insert(it, chunk);
    } else {
      // merge with prev
#ifdef _DEBUG
      std::cerr << "### Merge with previous free chunk" << std::endl;
#endif
      pit->size += sz;
    }
  }
  */
  
  return true;
}

void Heap::status() const {
  std::cerr << "Heap" << std::endl;
  std::cerr << "  0x" << std::hex << mHeap << std::dec << std::endl;
  std::cerr << "  " << mTotalSize << " bytes" << std::endl;
  std::cerr << "  " << mUsedSize << " used" << std::endl;
  for (size_t i=0; i<mChunks.size(); ++i) {
    std::cerr << "  Chunk " << i << std::endl;
    std::cerr << "    0x" << std::hex << mChunks[i].start << std::dec << std::endl;
    std::cerr << "    " << mChunks[i].size << " bytes free" << std::endl;
  }
}

// ---

static HeapManager *gHeapMgr = 0;

HeapManager::HeapManager(size_t initialSize) {
  if (gHeapMgr != 0) {
    throw std::runtime_error("Heap manager already allocated");
  }
  gHeapMgr = this;
  mHeaps.push_back(new Heap(initialSize));
}

HeapManager::~HeapManager() {
  for (size_t i=0; i<mHeaps.size(); ++i) {
    delete mHeaps[i];
  }
  mHeaps.clear();
  gHeapMgr = 0;
}

void* HeapManager::allocate(size_t sz) {
  void *rv = 0;
  for (size_t i=0; i<mHeaps.size(); ++i) {
    rv = mHeaps[i]->allocate(sz);
    if (rv != 0) {
      return rv;
    }
  }
  size_t newHeapSize = total() * 2;
  if (newHeapSize < sz) {
    newHeapSize = sz * 2;
  }
  Heap *h = new Heap(newHeapSize);
  mHeaps.push_back(h);
  return h->allocate(sz);
}

void HeapManager::deallocate(void *ptr, size_t sz) {
  for (size_t i=0; i<mHeaps.size(); ++i) {
    if (mHeaps[i]->deallocate(ptr, sz)) {
      return;
    }
  }
#ifdef _DEBUG
  std::cerr << "Memory @ 0x" << std::hex << ptr << std::dec
            << " (" << sz << " bytes) was not allocated through HeapManager"
            << std::endl;
#endif
}

size_t HeapManager::total() const {
  size_t rv = 0;
  for (size_t i=0; i<mHeaps.size(); ++i) {
    rv += mHeaps[i]->total();
  }
  return rv;
}

size_t HeapManager::used() const {
  size_t rv = 0;
  for (size_t i=0; i<mHeaps.size(); ++i) {
    rv += mHeaps[i]->used();
  }
  return rv;
}

void HeapManager::status() const {
  for (size_t i=0; i<mHeaps.size(); ++i) {
    mHeaps[i]->status();
  }
}

// ---

void* HeapObject::operator new(size_t sz) {
  return gHeapMgr->allocate(sz);
}

void HeapObject::operator delete(void *ptr, size_t sz) {
  gHeapMgr->deallocate(ptr, sz);
}

HeapObject::HeapObject() {
}

HeapObject::~HeapObject() {
}
