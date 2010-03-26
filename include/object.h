#ifndef __object_h_
#define __object_h_

#include <string>
#include <vector>
#include <iostream>
#include <exception>
#include <stdexcept>

#ifdef _MSC_VER
# pragma warning(disable:4290)
#endif

enum {
  T_INTEGER,
  T_DOUBLE,
  T_STRING,
  T_BOOLEAN,
  T_CALLABLE,
  T_OBJECT
};

class Object {
  public:
    
    Object(int t);
    virtual ~Object();
    
    virtual Object* clone() const;
    virtual bool isCallable() const;
    virtual int call(class Stack &, class Context &);
    virtual void toStream(std::ostream &os, const std::string &heading="") const;
    virtual bool equal(Object *rhs) const;
    virtual bool lessThan(Object *rhs) const;
    
    virtual double toDouble() const;
    virtual long toInteger() const;
    virtual bool toBoolean() const;
    virtual std::string toString() const;
    
    inline bool notEqual(Object *rhs) const {
      return !equal(rhs);
    }
    
    inline bool lessThanEqual(Object *rhs) const {
      return (equal(rhs) || lessThan(rhs));
    }
    
    inline bool greaterThan(Object *rhs) const {
      return !lessThanEqual(rhs);
    }
    
    inline bool greaterThanEqual(Object *rhs) const {
      return !lessThan(rhs);
    }
    
    inline int type() const {
      return mType;
    }
    
    inline void incRef() {
      ++mRef;
    }
    
    inline void decRef() {
      if (--mRef == 0) {
        delete this;
      }
    }
    
    inline long refCount() const {
      return mRef;
    }
  
  protected:
    
    int mType;
    
    long mRef;
};

class Double : public Object {
  public:
    
    Double(double v = 0.0);
    virtual ~Double();
    
    virtual Object* clone() const;
    virtual void toStream(std::ostream &os, const std::string &heading="") const;
    virtual bool equal(Object *rhs) const;
    virtual bool lessThan(Object *rhs) const;
    virtual double toDouble() const;
    virtual long toInteger() const;
    virtual bool toBoolean() const;
    virtual std::string toString() const;
    
    inline double getValue() const {
      return mValue;
    }
    
    inline void setValue(double v) {
      mValue = v;
    }
    
  protected:
    
    double mValue;
};

class Integer : public Object {
  public:
    
    Integer(long v = 0);
    virtual ~Integer();
    
    virtual Object* clone() const;
    virtual void toStream(std::ostream &os, const std::string &heading="") const;
    virtual bool equal(Object *rhs) const;
    virtual bool lessThan(Object *rhs) const;
    virtual double toDouble() const;
    virtual long toInteger() const;
    virtual bool toBoolean() const;
    virtual std::string toString() const;
    
    inline long getValue() const {
      return mValue;
    }
    
    inline void setValue(long v) {
      mValue = v;
    }
    
  protected:
    
    long mValue;
};

class String : public Object {
  public:
    
    String(const std::string &v = "");
    virtual ~String();
    
    virtual Object* clone() const;
    virtual void toStream(std::ostream &os, const std::string &heading="") const;
    virtual bool equal(Object *rhs) const;
    virtual bool lessThan(Object *rhs) const;
    virtual double toDouble() const;
    virtual long toInteger() const;
    virtual bool toBoolean() const;
    virtual std::string toString() const;
    
    inline const std::string& getValue() const {
      return mValue;
    }
    
    inline void setValue(const std::string &v) {
      mValue = v;
    }
    
  protected:
    
    std::string mValue;
};

class Boolean : public Object {
  public:
    
    Boolean(bool t=false);
    virtual ~Boolean();
    
    virtual Object* clone() const;
    virtual void toStream(std::ostream &os, const std::string &heading="") const;
    virtual bool equal(Object *rhs) const;
    virtual bool lessThan(Object *rhs) const;
    virtual double toDouble() const;
    virtual long toInteger() const;
    virtual bool toBoolean() const;
    virtual std::string toString() const;
    
    inline bool getValue() const {
      return mValue;
    }
    
    inline void setValue(bool b) {
      mValue = b;
    }
    
  protected:
    
    bool mValue;
};

class Callable : public Object {
  public:
    
    Callable();
    virtual ~Callable();
    
    virtual bool isCallable() const;
    virtual bool lessThan(Object *rhs) const;
    virtual double toDouble() const;
    virtual long toInteger() const;
    virtual bool toBoolean() const;
    virtual std::string toString() const;
    virtual int stackConsumption(class Context &) const = 0;
};

class CFunction : public Callable {
  
  public:
    
    CFunction(int nargs, bool hasReturn);
    virtual ~CFunction();
    
    virtual int stackConsumption(class Context &) const;
    virtual void toStream(std::ostream &os, const std::string &heading="") const;
    
  protected:
    
    int mNumArgs;
    bool mHasReturn;
};

class Block : public Callable {
  public:
    
    Block();
    virtual ~Block();
    
    virtual Object* clone() const;
    virtual int call(class Stack &stack, class Context &ctx);
    virtual int stackConsumption(class Context &ctx) const;
    virtual void toStream(std::ostream &os, const std::string &heading="") const;
    
    void addArgument(const std::string &name);
    void addInstruction(class Instruction *i);
    void setCode(class CodeSegment *);
    
    inline class CodeSegment* code() {
      return mCode;
    }
    
    inline const class CodeSegment* getCode() const {
      return mCode;
    }
    
  protected:
    
    class CodeSegment *mCode;
    std::vector<std::string> mArgs;
};

#endif
