#ifndef __builtins_h__
#define __builtins_h__

#include "object.h"

class Concat : public CFunction {
  public:
    Concat();
    virtual ~Concat();
    virtual Object* clone() const;
    virtual int call(Stack &stack, Context &ctx);
};

class Add : public CFunction {
  public:
    Add();
    virtual ~Add();
    virtual Object* clone() const;
    virtual int call(Stack &stack, Context &ctx);
};

class Sub : public CFunction {
  public:
    Sub();
    virtual ~Sub();
    virtual Object* clone() const;
    virtual int call(Stack &stack, Context &ctx);
};

class Minus : public CFunction {
  public:
    Minus();
    virtual ~Minus();
    virtual Object* clone() const;
    virtual int call(Stack &stack, Context &ctx);
};

class Mult : public CFunction {
  public:
    Mult();
    virtual ~Mult();
    virtual Object* clone() const;
    virtual int call(Stack &stack, Context &ctx);
};

class Div : public CFunction {
  public:
    Div();
    virtual ~Div();
    virtual Object* clone() const;
    virtual int call(Stack &stack, Context &ctx);
};

// --- math

class Sin : public CFunction {
  public:
    Sin();
    virtual ~Sin();
    virtual Object* clone() const;
    virtual int call(Stack &stack, Context &ctx);
};

class Cos : public CFunction {
  public:
    Cos();
    virtual ~Cos();
    virtual Object* clone() const;
    virtual int call(Stack &stack, Context &ctx);
};

class Tan : public CFunction {
  public:
    Tan();
    virtual ~Tan();
    virtual Object* clone() const;
    virtual int call(Stack &stack, Context &ctx);
};

// floor
// ceil
// abs
// exp
// pow
// log
// acos
// asin
// atan
// atan2
// sqrt
// constants?

// --- comparison

class Equal : public CFunction {
  public:
    Equal();
    virtual ~Equal();
    virtual Object* clone() const;
    virtual int call(Stack &stack, Context &ctx);
};

class NotEqual : public CFunction {
  public:
    NotEqual();
    virtual ~NotEqual();
    virtual Object* clone() const;
    virtual int call(Stack &stack, Context &ctx);
};

class LessThan : public CFunction {
  public:
    LessThan();
    virtual ~LessThan();
    virtual Object* clone() const;
    virtual int call(Stack &stack, Context &ctx);
};

class GreaterThan : public CFunction {
  public:
    GreaterThan();
    virtual ~GreaterThan();
    virtual Object* clone() const;
    virtual int call(Stack &stack, Context &ctx);
};

class LessThanEqual : public CFunction {
  public:
    LessThanEqual();
    virtual ~LessThanEqual();
    virtual Object* clone() const;
    virtual int call(Stack &stack, Context &ctx);
};

class GreaterThanEqual : public CFunction {
  public:
    GreaterThanEqual();
    virtual ~GreaterThanEqual();
    virtual Object* clone() const;
    virtual int call(Stack &stack, Context &ctx);
};

// --- print

class Print : public CFunction {
  public:
    Print();
    virtual ~Print();
    virtual Object* clone() const;
    virtual int call(Stack &stack, Context &ctx);
};

void RegisterBuiltins(Context &ctx);

#endif
