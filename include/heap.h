#ifndef __heap_h_
#define __heap_h_

#include <vector>
#include <list>
#include <string>
#include <map>
#include <new>

class Heap {
  public:
    
    static inline size_t Kb(size_t sz) {
      return sz * 1024;
    }
    
    static inline size_t Mb(size_t sz) {
      return sz * 1024 * 1024;
    }
    
    struct Chunk {
      void *start;
      size_t size;
      
      inline void* end() {
        return (void*)(((unsigned char*)start) + size);
      }
    };
    
    typedef std::vector<Chunk> ChunkList;
    
  public:
    
    // size is in Kb
    // 8096 Kb == 8 Mb
    Heap(size_t initialSize = Kb(8));
    ~Heap();
    
    void* allocate(size_t sz);
    bool deallocate(void *ptr, size_t sz);
    
    inline size_t total() const {
      return mTotalSize;
    }
    
    inline size_t used() const {
      return mUsedSize;
    }
    
    inline void* end() {
      return (void*) (((unsigned char*)mHeap) + mTotalSize);
    }
    
    void status() const;
    
  protected:
    
    void *mHeap;
    ChunkList mChunks;
    size_t mTotalSize;
    size_t mUsedSize;
};

class HeapManager {
  public:
    
    HeapManager(size_t initialSize = Heap::Kb(8));
    ~HeapManager();
    
    void* allocate(size_t sz);
    void deallocate(void *ptr, size_t sz);
    
    size_t total() const;
    size_t used() const;
    
    void status() const;
    
  protected:
    
    std::vector<Heap*> mHeaps;
};

class HeapObject {
  public:

    static void* operator new(size_t sz);
    static void operator delete(void *ptr, size_t sz);
    
  public:
    
    HeapObject();
    virtual ~HeapObject();
};

#endif
