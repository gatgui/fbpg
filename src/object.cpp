#include "object.h"
#include "instruction.h"
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

unsigned long gNumObjects = 0;

Object::Object(int t)
  : mType(t), mRef(1) {
  ++gNumObjects;
}

Object::~Object() {
  --gNumObjects;
  if (gNumObjects == 0) {
    std::cout << "### All object deleted" << std::endl;
  }
}

bool Object::equal(Object *rhs) const {
  return (this == rhs);
}

bool Object::lessThan(Object *rhs) const {
  return ((void*)this < (void*)rhs);
}

Object* Object::clone() const {
  return new Object(mType);
}

bool Object::isCallable() const {
  return false;
}

int Object::call(class Stack &, class Context &) {
  throw std::runtime_error("Object is not callable");
}

void Object::toStream(std::ostream &os, const std::string &heading) const {
  os << heading << "<Object: 0x" << std::hex << (void*)this << std::dec << ">";
}

double Object::toDouble() const {
  return 0.0;
}

long Object::toInteger() const {
  return 0;
}

bool Object::toBoolean() const {
  return false;
}

std::string Object::toString() const {
  return "";
}

// ---

Double::Double(double v)
  : Object(T_DOUBLE), mValue(v) {
}

Double::~Double() {
}

Object* Double::clone() const {
  return new Double(mValue);
}

void Double::toStream(std::ostream &os, const std::string &heading) const {
  os << heading << mValue;
}

bool Double::equal(Object *rhs) const {
  return (mValue == rhs->toDouble());
}

bool Double::lessThan(Object *rhs) const {
  return (mValue < rhs->toDouble());
}

double Double::toDouble() const {
  return mValue;
}

long Double::toInteger() const {
  return long(mValue);
}

bool Double::toBoolean() const {
  return (mValue != 0.0);
}

std::string Double::toString() const {
  std::ostringstream oss;
  oss << mValue;
  return oss.str();
}

// ---

Integer::Integer(long v)
  : Object(T_INTEGER), mValue(v) {
}

Integer::~Integer() {
}

Object* Integer::clone() const {
  return new Integer(mValue);
}

void Integer::toStream(std::ostream &os, const std::string &heading) const {
  os << heading << mValue;
}

bool Integer::equal(Object *rhs) const {
  return (mValue == rhs->toInteger());
}

bool Integer::lessThan(Object *rhs) const {
  return (mValue < rhs->toInteger());
}

double Integer::toDouble() const {
  return double(mValue);
}

long Integer::toInteger() const {
  return mValue;
}

bool Integer::toBoolean() const {
  return (mValue != 0);
}

std::string Integer::toString() const {
  std::ostringstream oss;
  oss << mValue;
  return oss.str();
}

// ---

String::String(const std::string &v)
  : Object(T_STRING), mValue(v) {
}

String::~String() {
}

Object* String::clone() const {
  return new String(mValue);
}

void String::toStream(std::ostream &os, const std::string &heading) const {
  os << heading << mValue;
}

bool String::equal(Object *rhs) const {
  return (mValue == rhs->toString());
}

bool String::lessThan(Object *rhs) const {
  return (strcmp(mValue.c_str(), rhs->toString().c_str()) < 0);
}

double String::toDouble() const {
  double v;
  if (sscanf(mValue.c_str(), "%lf", &v) != 1) {
    throw std::runtime_error("String value cannot be converted to a double");
  }
  return v;
}

long String::toInteger() const {
  long v;
  if (sscanf(mValue.c_str(), "%ld", &v) != 1) {
    throw std::runtime_error("String value cannot be converted to an integer");
  }
  return v;
}

bool String::toBoolean() const {
  return (mValue.length() > 0);
}

std::string String::toString() const {
  return mValue;
}


// ---

Boolean::Boolean(bool v)
  : Object(T_BOOLEAN), mValue(v) {
}

Boolean::~Boolean() {
}

Object* Boolean::clone() const {
  return new Boolean(mValue);
}

void Boolean::toStream(std::ostream &os, const std::string &heading) const {
  os << heading << (mValue ? "true" : "false");
}

bool Boolean::equal(Object *rhs) const {
  return (mValue == rhs->toBoolean());
}

bool Boolean::lessThan(Object *) const {
  throw std::runtime_error("Boolean object are not comparable");
  return false;
}

double Boolean::toDouble() const {
  return (mValue ? 1.0 : 0.0);
}

long Boolean::toInteger() const {
  return (mValue ? 1 : 0);
}

bool Boolean::toBoolean() const {
  return mValue;
}

std::string Boolean::toString() const {
  return (mValue ? "true" : "false");
}

// ---

Callable::Callable()
  : Object(T_CALLABLE) {
}

Callable::~Callable() {
}

bool Callable::isCallable() const {
  return true;
}

bool Callable::lessThan(Object *) const {
  throw std::runtime_error("Callable object are not comparable");
  return false;
}

double Callable::toDouble() const {
  throw std::runtime_error("Callable cannot be converted to a double");
  return 0.0;
}

long Callable::toInteger() const {
  throw std::runtime_error("Callable cannot be converted to an integer");
  return 0;
}

bool Callable::toBoolean() const {
  throw std::runtime_error("Callable cannot be converted to a boolean");
  return false;
}

std::string Callable::toString() const {
  throw std::runtime_error("Callable cannot be converted to a string");
  return "";
}

// ---

CFunction::CFunction(int nargs, bool hasReturn)
  : Callable(), mNumArgs(nargs), mHasReturn(hasReturn) {
}

CFunction::~CFunction() {
}

int CFunction::stackConsumption(Context &) const {
  return ((mHasReturn ? 1 : 0) - mNumArgs);
}

void CFunction::toStream(std::ostream &os, const std::string &heading) const {
  os << heading << "<CFunction: 0x" << std::hex << (void*)this << std::dec << ">";
}

// ---

Block::Block()
  : Callable(), mCode(0) {
}

Block::~Block() {
  if (mCode != 0) {
    delete mCode;
    mCode = 0;
  }
}

void Block::addArgument(const std::string &name) {
  mArgs.push_back(name);
}

void Block::addInstruction(Instruction *i) {
  if (mCode == 0) {
    mCode = new CodeSegment();
  }
  mCode->push_back(i);
}

void Block::setCode(CodeSegment *cs) {
  if (mCode != 0) {
    delete mCode;
  }
  mCode = cs;
}

int Block::stackConsumption(Context &ctx) const {
  if (mCode != 0) {
    return mCode->stackConsumption(ctx);
  } else {
    return 0;
  }
}

Object* Block::clone() const {
  Block *b = new Block();
  for (size_t i=0; i<mArgs.size(); ++i) {
    b->addArgument(mArgs[i]);
  }
  if (mCode != 0) {
    b->setCode(new CodeSegment(*mCode));
  }
  return b;
}

int Block::call(Stack &stack, Context &ctx) {
  if (mCode == 0) {
    return EVAL_NEXT;
  }
  // here failure
  Context fctx(ctx);
  int numArgs = int(mArgs.size());
  for (int i=numArgs-1; i>=0; --i) {
    Object *o = stack.pop();
    fctx.setVar(mArgs[i], o);
    o->decRef();
  }
  int rv = mCode->eval(stack, fctx);
  return rv;
}

void Block::toStream(std::ostream &os, const std::string &heading) const {
  os << heading << "{Block:";
  if (mArgs.size() > 0) {
    os << " (";
    for (size_t i=0; i<mArgs.size()-1; ++i) {
      os << mArgs[i] << ", ";
    }
    os << mArgs.back() << ")";
  }
  os << std::endl;
  if (mCode != 0) {
    //os << std::endl;
    mCode->toStream(os, heading + "  ");
    os << std::endl;
  }
  os << heading << "}";
  //os << " >";
}

