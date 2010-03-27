#include "builtins.h"
#include "object.h"
#include "stack.h"
#include "context.h"
#include "instruction.h"
#include <iostream>
#include <cmath>

class Concat : public CFunction {
  public:
    Concat() : CFunction(2, true) {}
    virtual ~Concat() {}
    virtual Object* clone() const {return new Concat();}
    virtual int call(Stack &stack, Context &) {
      std::string v1 = stack.popString();
      std::string v0 = stack.popString();
      stack.pushString(v0+v1);
      return EVAL_NEXT;
    }
};

class Add : public CFunction {
  public:
    Add() : CFunction(2, true) {}
    virtual ~Add() {}
    virtual Object* clone() const {return new Add();}
    virtual int call(Stack &stack, Context &) {
      double v1 = stack.popDouble();
      double v0 = stack.popDouble();
      stack.pushDouble(v0+v1);
      return EVAL_NEXT;
    }
};

class Sub : public CFunction {
  public:
    Sub() : CFunction(2, true) {}
    virtual ~Sub() {}
    virtual Object* clone() const {return new Sub();}
    virtual int call(Stack &stack, Context &) {
      double v1 = stack.popDouble();
      double v0 = stack.popDouble();
      stack.pushDouble(v0-v1);
      return EVAL_NEXT;
    }
};

class Minus : public CFunction {
  public:
    Minus() : CFunction(1, true) {}
    virtual ~Minus() {}
    virtual Object* clone() const {return new Minus();}
    virtual int call(Stack &stack, Context &) {
      double v = stack.popDouble();
      stack.pushDouble(-v);
      return EVAL_NEXT;
    }
};

class Mult : public CFunction {
  public:
    Mult() : CFunction(2, true) {}
    virtual ~Mult() {}
    virtual Object* clone() const {return new Mult();}
    virtual int call(Stack &stack, Context &) {
      double v1 = stack.popDouble();
      double v0 = stack.popDouble();
      stack.pushDouble(v0*v1);
      return EVAL_NEXT;
    }
};

class Div : public CFunction {
  public:
    Div() : CFunction(2, true) {}
    virtual ~Div() {}
    virtual Object* clone() const {return new Div();}
    virtual int call(Stack &stack, Context &) {
      double v1 = stack.popDouble();
      double v0 = stack.popDouble();
      stack.pushDouble(v0/v1);
      return EVAL_NEXT;
    }
};

// --- math

class Sin : public CFunction {
  public:
    Sin() : CFunction(1, true) {}
    virtual ~Sin() {}
    virtual Object* clone() const {return new Sin();}
    virtual int call(Stack &stack, Context &) {
      double r = sin(stack.popDouble());
      stack.pushDouble(r);
      return EVAL_NEXT;
    }
};

class Cos : public CFunction {
  public:
    Cos() : CFunction(1, true) {}
    virtual ~Cos() {}
    virtual Object* clone() const {return new Cos();}
    virtual int call(Stack &stack, Context &) {
      double r = cos(stack.popDouble());
      stack.pushDouble(r);
      return EVAL_NEXT;
    }
};

class Tan : public CFunction {
  public:
    Tan() : CFunction(1, true) {}
    virtual ~Tan() {}
    virtual Object* clone() const {return new Tan();}
    virtual int call(Stack &stack, Context &) {
      double r = tan(stack.popDouble());
      stack.pushDouble(r);
      return EVAL_NEXT;
    }
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
    Equal() : CFunction(2, true) {}
    virtual ~Equal() {}
    virtual Object* clone() const {return new Equal();}
    virtual int call(Stack &stack, Context &) {
      Object *o2 = stack.pop();
      Object *o1 = stack.pop();
      stack.pushBoolean(o1->equal(o2));
      o1->decRef();
      o2->decRef();
      return EVAL_NEXT;
    }
};

class NotEqual : public CFunction {
  public:
    NotEqual() : CFunction(2, true) {}
    virtual ~NotEqual() {}
    virtual Object* clone() const {return new NotEqual();}
    virtual int call(Stack &stack, Context &) {
      Object *o2 = stack.pop();
      Object *o1 = stack.pop();
      stack.pushBoolean(o1->notEqual(o2));
      o1->decRef();
      o2->decRef();
      return EVAL_NEXT;
    }
};

class LessThan : public CFunction {
  public:
    LessThan() : CFunction(2, true) {}
    virtual ~LessThan() {}
    virtual Object* clone() const {return new LessThan();}
    virtual int call(Stack &stack, Context &) {
      Object *o2 = stack.pop();
      Object *o1 = stack.pop();
      stack.pushBoolean(o1->lessThan(o2));
      o1->decRef();
      o2->decRef();
      return EVAL_NEXT;
    }
};

class GreaterThan : public CFunction {
  public:
    GreaterThan() : CFunction(2, true) {}
    virtual ~GreaterThan() {}
    virtual Object* clone() const {return new GreaterThan();}
    virtual int call(Stack &stack, Context &) {
      Object *o2 = stack.pop();
      Object *o1 = stack.pop();
      stack.pushBoolean(o1->greaterThan(o2));
      o1->decRef();
      o2->decRef();
      return EVAL_NEXT;
    }
};

class LessThanEqual : public CFunction {
  public:
    LessThanEqual() : CFunction(2, true) {}
    virtual ~LessThanEqual() {}
    virtual Object* clone() const {return new LessThanEqual();}
    virtual int call(Stack &stack, Context &) {
      Object *o2 = stack.pop();
      Object *o1 = stack.pop();
      stack.pushBoolean(o1->lessThanEqual(o2));
      o1->decRef();
      o2->decRef();
      return EVAL_NEXT;
    }
};

class GreaterThanEqual : public CFunction {
  public:
    GreaterThanEqual() : CFunction(2, true) {}
    virtual ~GreaterThanEqual() {}
    virtual Object* clone() const {return new GreaterThanEqual();}
    virtual int call(Stack &stack, Context &) {
      Object *o2 = stack.pop();
      Object *o1 = stack.pop();
      stack.pushBoolean(o1->greaterThanEqual(o2));
      o1->decRef();
      o2->decRef();
      return EVAL_NEXT;
    }
};

// logical operator

class And : public CFunction {
  public:
    And() : CFunction(2, true) {}
    virtual ~And() {}
    virtual Object* clone() const {return new And();}
    virtual int call(Stack &stack, Context &) {
      bool b1 = stack.popBoolean();
      bool b0 = stack.popBoolean();
      stack.pushBoolean(b0 && b1);
      return EVAL_NEXT;
    }
};

class Or : public CFunction {
  public:
    Or() : CFunction(2, true) {}
    virtual ~Or() {}
    virtual Object* clone() const {return new Or();}
    virtual int call(Stack &stack, Context &) {
      bool b1 = stack.popBoolean();
      bool b0 = stack.popBoolean();
      stack.pushBoolean(b0 || b1);
      return EVAL_NEXT;
    }
};

class Not : public CFunction {
  public:
    Not() : CFunction(1, true) {}
    virtual ~Not() {}
    virtual Object* clone() const {return new Not();}
    virtual int call(Stack &stack, Context &) {
      bool b1 = stack.popBoolean();
      stack.pushBoolean(!b1);
      return EVAL_NEXT;
    }
};

// --- print

class Print : public CFunction {
  public:
    Print() : CFunction(1, false) {}
    virtual ~Print() {}
    virtual Object* clone() const {return new Print();}
    virtual int call(Stack &stack, Context &) {
      Object *o = stack.pop();
      if (o == NULL) {
        std::cout << "<Null>";
      } else {
        o->toStream(std::cout);
        o->decRef();
      }
      return EVAL_NEXT;
    }
};

// ---

void RegisterBuiltins(Context &ctx) {
  // operators
  RegisterCFunction<Minus>(ctx, "__uminus__");
  RegisterCFunction<Concat>(ctx, "..");
  RegisterCFunction<Add>(ctx, "+");
  RegisterCFunction<Sub>(ctx, "-");
  RegisterCFunction<Mult>(ctx, "*");
  RegisterCFunction<Div>(ctx, "/");
  RegisterCFunction<Equal>(ctx, "==");
  RegisterCFunction<NotEqual>(ctx, "!=");
  RegisterCFunction<LessThan>(ctx, "<");
  RegisterCFunction<GreaterThan>(ctx, ">");
  RegisterCFunction<LessThanEqual>(ctx, "<=");
  RegisterCFunction<GreaterThanEqual>(ctx, ">=");
  // logical operator
  RegisterCFunction<Not>(ctx, "not");
  RegisterCFunction<And>(ctx, "and");
  RegisterCFunction<Or>(ctx, "or");
  // math function
  RegisterCFunction<Cos>(ctx, "cos");
  RegisterCFunction<Sin>(ctx, "sin");
  RegisterCFunction<Tan>(ctx, "tan");
  // utilities
  RegisterCFunction<Print>(ctx, "print");
}
