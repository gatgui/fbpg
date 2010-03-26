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
    
    void push(Object *o);
    void pushBoolean(bool v);
    void pushInteger(long v);
    void pushDouble(double v);
    void pushString(const std::string &v);
    
    void clear();
    
    int size() const;
    
    Object* pop(int n = 1); // if n > 1, returns first popped object
    bool popBoolean();
    long popInteger();
    double popDouble();
    std::string popString();
    
    Object* get(int idx = -1) const;
    bool getBoolean(int idx = -1) const;
    long getInteger(int idx = -1) const;
    double getDouble(int idx = -1) const;
    std::string getString(int idx = -1) const;
    
  protected:
    
    std::vector<Object*> mStack;
};

#endif
