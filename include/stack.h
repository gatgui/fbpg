#ifndef __stack_h_
#define __stack_h_

#include <vector>
#include <exception>
#include <stdexcept>
#include "object.h"

class Stack {
  public:
    
    Stack();
    ~Stack();
    
    bool push(Object *o);
    void pushBoolean(bool v);
    void pushInteger(LongInteger v);
    void pushDouble(double v);
    void pushString(const std::string &v);
    
    void clear();
    
    int size() const;
    
    Object* pop(int n = 1); // if n > 1, returns first popped object
    bool popBoolean(bool &err);
    LongInteger popInteger(bool &err);
    double popDouble(bool &err);
    std::string popString(bool &err);
    
    Object* get(int idx) const;
    bool getBoolean(int idx, bool &err) const;
    LongInteger getInteger(int idx, bool &err) const;
    double getDouble(int idx, bool &err) const;
    std::string getString(int idx, bool &err) const;
    
    inline std::string getError() const {
      return mErrString;
    }
    
  protected:
    
    inline void setError(const std::string &m) const {
      mErrString = m;
    }
    
  protected:
    
    std::vector<Object*> mStack;
    mutable std::string mErrString;
};

#endif
