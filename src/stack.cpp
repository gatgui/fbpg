#include "stack.h"
#include <sstream>

Stack::Stack() {
}

Stack::~Stack() {
  clear();
}

int Stack::size() const {
  return int(mStack.size());
}

void Stack::clear() {
  while (size() > 0) {
    Object *o = pop();
    if (o->refCount() <= 0) {
       std::ostringstream oss;
      oss << "*** Object on stack at position " << size() << " has already been deleted";
      throw std::runtime_error(oss.str());
    }
    o->decRef();
  }
}

void Stack::push(Object *o) {
  if (!o) {
    throw std::runtime_error("Push null");
  }
  o->incRef();
  mStack.push_back(o);
}

void Stack::pushBoolean(bool v) {
  push(new Boolean(v));
}

void Stack::pushInteger(long v) {
  push(new Integer(v));
}

void Stack::pushDouble(double v) {
  push(new Double(v));
}

void Stack::pushString(const std::string &v) {
  push(new String(v));
}

Object* Stack::pop(int n) {
  Object *rv = 0;
  Object *o = 0;
  if (n <= 0) {
    return rv;
  }
  while (n > 0 && mStack.size() > 0) {
    o = mStack.back();
    if (rv == 0) {
      rv = o;
    }
    if (o) {
      o->decRef();
    }
    mStack.pop_back();
    --n;
  }
  return rv;
}

bool Stack::popBoolean() {
  Object *o = pop();
  bool rv = o->toBoolean();
  o->decRef();
  return rv;
}

long Stack::popInteger() {
  Object *o = pop();
  long rv = o->toInteger();
  o->decRef();
  return rv;
}

double Stack::popDouble() {
  Object *o = pop();
  double rv = o->toDouble();
  o->decRef();
  return rv;
}

std::string Stack::popString() {
  Object *o = pop();
  std::string rv = o->toString();
  o->decRef();
  return rv;
}

Object* Stack::get(int idx) const {
  if (idx < 0) {
    idx = size() + idx;
    if (idx < 0) {
      throw std::runtime_error("Invalid stack index");
    }
  }
  if (idx >= size()) {
    throw std::runtime_error("Invalid stack index");
  }
  return mStack[idx];
}

bool Stack::getBoolean(int idx) const {
  return (get(idx)->toBoolean());
}

long Stack::getInteger(int idx) const {
  return (get(idx)->toInteger());
}

double Stack::getDouble(int idx) const {
  return (get(idx)->toDouble());
}

std::string Stack::getString(int idx) const {
  return (get(idx)->toString());
}

