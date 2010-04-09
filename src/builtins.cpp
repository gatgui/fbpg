#include "builtins.h"
#include "object.h"
#include "stack.h"
#include "context.h"
#include "instruction.h"
#include <iostream>
#ifdef _MSC_VER
# define _USE_MATH_DEFINES
#endif
#include <cmath>
#ifdef _MSC_VER
// MSVC and its annoying "deprecated" API
# define hypot _hypot
#endif

class Add : public CFunction {
  public:
    Add() : CFunction(2, true) {}
    virtual ~Add() {}
    virtual Object* clone() const {return new Add();}
    virtual int call(Stack *stack, Context *, bool &failed) {
      int rv = EVAL_NEXT;
      
      Object *o1 = stack->pop();
      
      if (!o1) {
        setError("Not enough values on stack");
        return EVAL_FAILURE;
      }
      
      Object *o0 = stack->pop();
      
      if (!o0) {
        o1->decRef();
        setError("Not enough values on stack");
        return EVAL_FAILURE;
      }
      
      if (o0->type() == T_INTEGER) {
        LongInteger v0 = o0->toInteger(failed);
        
        if (o1->type() == T_INTEGER) {
          LongInteger v1 = o1->toInteger(failed);
          stack->pushInteger(v0 + v1);
        
        } else if (o1->type() == T_DOUBLE) {
          double v1 = o1->toDouble(failed);
          stack->pushDouble(v0 + v1);
          
        } else {
          LongInteger v1 = o1->toInteger(failed);
          
          if (failed) {
            double v1 = o1->toDouble(failed);
          
            if (failed) {
              setError("Invalid right operand type for operator +");
              rv = EVAL_FAILURE;
            
            } else {
              stack->pushDouble(v0 + v1);
            }
          } else {
            stack->pushInteger(v0 + v1);
          }
        }
        
      } else if (o0->type() == T_DOUBLE) {
        double v0 = o0->toDouble(failed);
        double v1 = o1->toDouble(failed);
        
        if (failed) {
          LongInteger v1 = o1->toInteger(failed);
          
          if (failed) {
            setError("Invalid right operand type for operator +");
            rv = EVAL_FAILURE;
          
          } else {
            stack->pushDouble(v0 + v1);
          }
          
        } else {
          stack->pushDouble(v0 + v1);
        }
        
      } else if (o0->type() == T_STRING) {
        std::string v0 = o0->toString(failed);
        std::string v1 = o1->toString(failed);
        
        if (failed) {
          setError("Invalid right operand type for operator +");
          rv = EVAL_FAILURE;
          
        } else {
          stack->pushString(v0 + v1);
        }
        
      } else {
        setError("Invalid left operand type for operator +");
        rv = EVAL_FAILURE;
        
      }
      
      o0->decRef();
      o1->decRef();
      return rv;
    }
};

class Sub : public CFunction {
  public:
    Sub() : CFunction(2, true) {}
    virtual ~Sub() {}
    virtual Object* clone() const {return new Sub();}
    virtual int call(Stack *stack, Context *, bool &failed) {
      int rv = EVAL_NEXT;
      
      Object *o1 = stack->pop();
      
      if (!o1) {
        setError("Not enough values on stack");
        return EVAL_FAILURE;
      }
      
      Object *o0 = stack->pop();
      
      if (!o0) {
        o1->decRef();
        setError("Not enough values on stack");
        return EVAL_FAILURE;
      }
      
      if (o0->type() == T_INTEGER) {
        LongInteger v0 = o0->toInteger(failed);
        
        if (o1->type() == T_INTEGER) {
          LongInteger v1 = o1->toInteger(failed);
          stack->pushInteger(v0 - v1);
        
        } else if (o1->type() == T_DOUBLE) {
          double v1 = o1->toDouble(failed);
          stack->pushDouble(v0 - v1);
          
        } else {
          LongInteger v1 = o1->toInteger(failed);
          
          if (failed) {
            double v1 = o1->toDouble(failed);
          
            if (failed) {
              setError("Invalid right operand type for operator -");
              rv = EVAL_FAILURE;
            
            } else {
              stack->pushDouble(v0 - v1);
            }
          } else {
            stack->pushInteger(v0 - v1);
          }
        }
        
      } else if (o0->type() == T_DOUBLE) {
        double v0 = o0->toDouble(failed);
        double v1 = o1->toDouble(failed);
        
        if (failed) {
          LongInteger v1 = o1->toInteger(failed);
          
          if (failed) {
            setError("Invalid right operand type for operator -");
            rv = EVAL_FAILURE;
          
          } else {
            stack->pushDouble(v0 - v1);
          }
          
        } else {
          stack->pushDouble(v0 - v1);
        }
        
      } else {
        setError("Invalid left operand type for operator -");
        rv = EVAL_FAILURE;
        
      }
      
      o0->decRef();
      o1->decRef();
      return rv;
    }
};

class Minus : public CFunction {
  public:
    Minus() : CFunction(1, true) {}
    virtual ~Minus() {}
    virtual Object* clone() const {return new Minus();}
    virtual int call(Stack *stack, Context *, bool &failed) {
      Object *o = stack->pop();
      if (!o) {
        setError("Not enough values on stack");
        return EVAL_FAILURE;
      }
      int rv = EVAL_NEXT;
      if (o->type() == T_INTEGER) {
        LongInteger v = o->toInteger(failed);
        stack->pushInteger(-v);
      } else if (o->type() == T_DOUBLE) {
        double v = o->toDouble(failed);
        stack->pushDouble(-v);
      } else {
        setError("Invalid operand type for unary minus");
        rv = EVAL_FAILURE;
      }
      o->decRef();
      return rv;
    }
};

class Mult : public CFunction {
  public:
    Mult() : CFunction(2, true) {}
    virtual ~Mult() {}
    virtual Object* clone() const {return new Mult();}
    virtual int call(Stack *stack, Context *, bool &failed) {
      int rv = EVAL_NEXT;
      
      Object *o1 = stack->pop();
      
      if (!o1) {
        setError("Not enough values on stack");
        return EVAL_FAILURE;
      }
      
      Object *o0 = stack->pop();
      
      if (!o0) {
        o1->decRef();
        setError("Not enough values on stack");
        return EVAL_FAILURE;
      }
      
      if (o0->type() == T_INTEGER) {
        LongInteger v0 = o0->toInteger(failed);
        
        if (o1->type() == T_INTEGER) {
          LongInteger v1 = o1->toInteger(failed);
          stack->pushInteger(v0 * v1);
        
        } else if (o1->type() == T_DOUBLE) {
          double v1 = o1->toDouble(failed);
          stack->pushDouble(v0 * v1);
          
        } else {
          LongInteger v1 = o1->toInteger(failed);
          
          if (failed) {
            double v1 = o1->toDouble(failed);
          
            if (failed) {
              setError("Invalid right operand type for operator *");
              rv = EVAL_FAILURE;
            
            } else {
              stack->pushDouble(v0 * v1);
            }
          } else {
            stack->pushInteger(v0 * v1);
          }
        }
        
      } else if (o0->type() == T_DOUBLE) {
        double v0 = o0->toDouble(failed);
        double v1 = o1->toDouble(failed);
        
        if (failed) {
          LongInteger v1 = o1->toInteger(failed);
          
          if (failed) {
            setError("Invalid right operand type for operator *");
            rv = EVAL_FAILURE;
          
          } else {
            stack->pushDouble(v0 * v1);
          }
          
        } else {
          stack->pushDouble(v0 * v1);
        }
        
      } else {
        setError("Invalid left operand type for operator *");
        rv = EVAL_FAILURE;
        
      }
      
      o0->decRef();
      o1->decRef();
      return rv;
    }
};

class Div : public CFunction {
  public:
    Div() : CFunction(2, true) {}
    virtual ~Div() {}
    virtual Object* clone() const {return new Div();}
    virtual int call(Stack *stack, Context *, bool &failed) {
      int rv = EVAL_NEXT;
      
      Object *o1 = stack->pop();
      
      if (!o1) {
        setError("Not enough values on stack");
        return EVAL_FAILURE;
      }
      
      Object *o0 = stack->pop();
      
      if (!o0) {
        o1->decRef();
        setError("Not enough values on stack");
        return EVAL_FAILURE;
      }
      
      if (o0->type() == T_INTEGER) {
        LongInteger v0 = o0->toInteger(failed);
        
        if (o1->type() == T_INTEGER) {
          LongInteger v1 = o1->toInteger(failed);
          stack->pushInteger(v0 / v1);
        
        } else if (o1->type() == T_DOUBLE) {
          double v1 = o1->toDouble(failed);
          stack->pushDouble(v0 / v1);
          
        } else {
          LongInteger v1 = o1->toInteger(failed);
          
          if (failed) {
            double v1 = o1->toDouble(failed);
          
            if (failed) {
              setError("Invalid right operand type for operator /");
              rv = EVAL_FAILURE;
            
            } else {
              stack->pushDouble(v0 / v1);
            }
          } else {
            stack->pushInteger(v0 / v1);
          }
        }
        
      } else if (o0->type() == T_DOUBLE) {
        double v0 = o0->toDouble(failed);
        double v1 = o1->toDouble(failed);
        
        if (failed) {
          LongInteger v1 = o1->toInteger(failed);
          
          if (failed) {
            setError("Invalid right operand type for operator /");
            rv = EVAL_FAILURE;
          
          } else {
            stack->pushDouble(v0 / v1);
          }
          
        } else {
          stack->pushDouble(v0 / v1);
        }
        
      } else {
        setError("Invalid left operand type for operator /");
        rv = EVAL_FAILURE;
        
      }
      
      o0->decRef();
      o1->decRef();
      return rv;
    }
};

class Mod : public CFunction {
  public:
    Mod() : CFunction(2, true) {}
    virtual ~Mod() {}
    virtual Object* clone() const {return new Mod();}
    virtual int call(Stack *stack, Context *, bool &failed) {
      LongInteger v1 = stack->popInteger(failed);
      
      if (failed) {
        setError(stack->getError());
        return EVAL_FAILURE;
      }
      
      LongInteger v0 = stack->popInteger(failed);
      
      if (failed) {
        setError(stack->getError());
        return EVAL_FAILURE;
      }
      
      stack->pushInteger(v0 % v1);
      
      return EVAL_NEXT;
    }
};

// --- comparison

class Equal : public CFunction {
  public:
    Equal() : CFunction(2, true) {}
    virtual ~Equal() {}
    virtual Object* clone() const {return new Equal();}
    virtual int call(Stack *stack, Context *, bool &failed) {
      Object *o2 = stack->pop();
      Object *o1 = stack->pop();
      failed = (!o1 || !o2);
      if (failed) {setError(stack->getError()); return EVAL_FAILURE;}
      stack->pushBoolean(o1->equal(o2, failed));
      if (failed) {setError(stack->getError()); return EVAL_FAILURE;}
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
    virtual int call(Stack *stack, Context *, bool &failed) {
      Object *o2 = stack->pop();
      Object *o1 = stack->pop();
      failed = (!o1 || !o2);
      if (failed) {setError(stack->getError()); return EVAL_FAILURE;}
      stack->pushBoolean(o1->notEqual(o2, failed));
      if (failed) {setError(stack->getError()); return EVAL_FAILURE;}
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
    virtual int call(Stack *stack, Context *, bool &failed) {
      Object *o2 = stack->pop();
      Object *o1 = stack->pop();
      failed = (!o1 || !o2);
      if (failed) {setError(stack->getError()); return EVAL_FAILURE;}
      stack->pushBoolean(o1->lessThan(o2, failed));
      if (failed) {setError(stack->getError()); return EVAL_FAILURE;}
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
    virtual int call(Stack *stack, Context *, bool &failed) {
      Object *o2 = stack->pop();
      Object *o1 = stack->pop();
      failed = (!o1 || !o2);
      if (failed) {setError(stack->getError()); return EVAL_FAILURE;}
      stack->pushBoolean(o1->greaterThan(o2, failed));
      if (failed) {setError(stack->getError()); return EVAL_FAILURE;}
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
    virtual int call(Stack *stack, Context *, bool &failed) {
      Object *o2 = stack->pop();
      Object *o1 = stack->pop();
      failed = (!o1 || !o2);
      if (failed) {setError(stack->getError()); return EVAL_FAILURE;}
      stack->pushBoolean(o1->lessThanEqual(o2, failed));
      if (failed) {setError(stack->getError()); return EVAL_FAILURE;}
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
    virtual int call(Stack *stack, Context *, bool &failed) {
      Object *o2 = stack->pop();
      Object *o1 = stack->pop();
      failed = (!o1 || !o2);
      if (failed) {setError(stack->getError()); return EVAL_FAILURE;}
      stack->pushBoolean(o1->greaterThanEqual(o2, failed));
      if (failed) {setError(stack->getError()); return EVAL_FAILURE;}
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
    virtual int call(Stack *stack, Context *, bool &failed) {
      bool b1 = stack->popBoolean(failed);
      if (failed) {setError(stack->getError()); return EVAL_FAILURE;}
      bool b0 = stack->popBoolean(failed);
      if (failed) {setError(stack->getError()); return EVAL_FAILURE;}
      stack->pushBoolean(b0 && b1);
      return EVAL_NEXT;
    }
};

class Or : public CFunction {
  public:
    Or() : CFunction(2, true) {}
    virtual ~Or() {}
    virtual Object* clone() const {return new Or();}
    virtual int call(Stack *stack, Context *, bool &failed) {
      bool b1 = stack->popBoolean(failed);
      if (failed) {setError(stack->getError()); return EVAL_FAILURE;}
      bool b0 = stack->popBoolean(failed);
      if (failed) {setError(stack->getError()); return EVAL_FAILURE;}
      stack->pushBoolean(b0 || b1);
      return EVAL_NEXT;
    }
};

class Not : public CFunction {
  public:
    Not() : CFunction(1, true) {}
    virtual ~Not() {}
    virtual Object* clone() const {return new Not();}
    virtual int call(Stack *stack, Context *, bool &failed) {
      bool b1 = stack->popBoolean(failed);
      if (failed) {setError(stack->getError()); return EVAL_FAILURE;}
      stack->pushBoolean(!b1);
      return EVAL_NEXT;
    }
};

// --- conversions

class ToDouble : public CFunction {
public:
  ToDouble() : CFunction(1, true) {}
  virtual ~ToDouble() {}
  virtual Object* clone() const {return new ToDouble();}
  virtual int call(Stack *stack, Context *, bool &failed) {
    Object *o = stack->pop();
    
    if (!o) {
      setError("Not enough values on stack");
      return EVAL_FAILURE;
    }
    
    double v = o->toDouble(failed);
    
    if (failed) {
      setError(stack->getError());
      o->decRef();
      return EVAL_FAILURE;
      
    } else {
      stack->pushDouble(v);
      o->decRef();
      return EVAL_NEXT;
    }
  }
};

class ToInteger : public CFunction {
public:
  ToInteger() : CFunction(1, true) {}
  virtual ~ToInteger() {}
  virtual Object* clone() const {return new ToInteger();}
  virtual int call(Stack *stack, Context *, bool &failed) {
    Object *o = stack->pop();
    
    if (!o) {
      setError("Not enough values on stack");
      return EVAL_FAILURE;
    }
    
    LongInteger v = o->toInteger(failed);
    
    if (failed) {
      setError(stack->getError());
      o->decRef();
      return EVAL_FAILURE;
      
    } else {
      stack->pushInteger(v);
      o->decRef();
      return EVAL_NEXT;
    }
  }
};

class ToBoolean : public CFunction {
public:
  ToBoolean() : CFunction(1, true) {}
  virtual ~ToBoolean() {}
  virtual Object* clone() const {return new ToBoolean();}
  virtual int call(Stack *stack, Context *, bool &failed) {
    Object *o = stack->pop();
    
    if (!o) {
      setError("Not enough values on stack");
      return EVAL_FAILURE;
    }
    
    bool v = o->toBoolean(failed);
    
    if (failed) {
      setError(stack->getError());
      o->decRef();
      return EVAL_FAILURE;
      
    } else {
      stack->pushBoolean(v);
      o->decRef();
      return EVAL_NEXT;
    }
  }
};

class ToString : public CFunction {
public:
  ToString() : CFunction(1, true) {}
  virtual ~ToString() {}
  virtual Object* clone() const {return new ToString();}
  virtual int call(Stack *stack, Context *, bool &failed) {
    Object *o = stack->pop();
    
    if (!o) {
      setError("Not enough values on stack");
      return EVAL_FAILURE;
    }
    
    std::string v = o->toString(failed);
    
    if (failed) {
      setError(stack->getError());
      o->decRef();
      return EVAL_FAILURE;
      
    } else {
      stack->pushString(v);
      o->decRef();
      return EVAL_NEXT;
    }
  }
};

// --- print

class Print : public CFunction {
  public:
    Print() : CFunction(1, false) {}
    virtual ~Print() {}
    virtual Object* clone() const {return new Print();}
    virtual int call(Stack *stack, Context *, bool &failed) {
      Object *o = stack->pop();
      failed = (o == NULL);
      if (failed) {setError(stack->getError()); return EVAL_FAILURE;}
      o->toStream(std::cout);
      o->decRef();
      return EVAL_NEXT;
    }
};

// --- print

class PrintLn : public CFunction {
  public:
    PrintLn() : CFunction(1, false) {}
    virtual ~PrintLn() {}
    virtual Object* clone() const {return new PrintLn();}
    virtual int call(Stack *stack, Context *, bool &failed) {
      Object *o = stack->pop();
      failed = (o == NULL);
      if (failed) {setError(stack->getError()); return EVAL_FAILURE;}
      o->toStream(std::cout);
      o->decRef();
      std::cout << std::endl;
      return EVAL_NEXT;
    }
};


// ---

template <double (*Func)(double)>
class OneArgFunc : public CFunction {
  public:
    OneArgFunc() : CFunction(1, true) {}
    virtual ~OneArgFunc() {}
    virtual Object* clone() const {return new OneArgFunc<Func>();}
    virtual int call(Stack *stack, Context *, bool &failed) {
      double o = stack->popDouble(failed);
      if (failed) {setError(stack->getError()); return EVAL_FAILURE;}
      stack->pushDouble(Func(o));
      return EVAL_NEXT;
    }
};

template <double (*Func)(double, double)>
class TwoArgFunc : public CFunction {
  public:
    TwoArgFunc() : CFunction(2, true) {}
    virtual ~TwoArgFunc() {}
    virtual Object* clone() const {return new TwoArgFunc<Func>();}
    virtual int call(Stack *stack, Context *, bool &failed) {
      double o1 = stack->popDouble(failed);
      if (failed) {setError(stack->getError()); return EVAL_FAILURE;}
      double o0 = stack->popDouble(failed);
      if (failed) {setError(stack->getError()); return EVAL_FAILURE;}
      stack->pushDouble(Func(o0, o1));
      return EVAL_NEXT;
    }
};

double degrees(double rv) {
  static double conv = 180.0 / M_PI;
  return rv * conv;
}

double radians(double dv) {
  static double conv = M_PI / 180.0;
  return dv * conv;
}

// ---

void RegisterBuiltins(Context *ctx) {
  if (!ctx) {
    return;
  }
  // operators
  ctx->registerCFunction<Minus>(Symbol("__uminus__"));
  ctx->registerCFunction<Add>(Symbol("+"));
  ctx->registerCFunction<Sub>(Symbol("-"));
  ctx->registerCFunction<Mult>(Symbol("*"));
  ctx->registerCFunction<Div>(Symbol("/"));
  ctx->registerCFunction<Mod>(Symbol("%"));
  ctx->registerCFunction<Equal>(Symbol("=="));
  ctx->registerCFunction<NotEqual>(Symbol("!="));
  ctx->registerCFunction<LessThan>(Symbol("<"));
  ctx->registerCFunction<GreaterThan>(Symbol(">"));
  ctx->registerCFunction<LessThanEqual>(Symbol("<="));
  ctx->registerCFunction<GreaterThanEqual>(Symbol(">="));
  // logical operator
  ctx->registerCFunction<Not>(Symbol("not"));
  ctx->registerCFunction<And>(Symbol("and"));
  ctx->registerCFunction<Or>(Symbol("or"));
  // explicit convertion
  ctx->registerCFunction<ToDouble>(Symbol("double"));
  ctx->registerCFunction<ToInteger>(Symbol("integer"));
  ctx->registerCFunction<ToString>(Symbol("string"));
  ctx->registerCFunction<ToBoolean>(Symbol("boolean"));
  // math function
  ctx->registerCFunction<OneArgFunc<degrees> >(Symbol("degrees"));
  ctx->registerCFunction<OneArgFunc<radians> >(Symbol("radians"));
  ctx->registerCFunction<OneArgFunc<ceil> >(Symbol("ceil"));
  ctx->registerCFunction<OneArgFunc<floor> >(Symbol("floor"));
  ctx->registerCFunction<OneArgFunc<fabs> >(Symbol("abs"));
  ctx->registerCFunction<OneArgFunc<sqrt> >(Symbol("sqrt"));
  ctx->registerCFunction<OneArgFunc<exp> >(Symbol("exp"));
  ctx->registerCFunction<OneArgFunc<log> >(Symbol("log"));
  ctx->registerCFunction<OneArgFunc<log10> >(Symbol("log10"));
  ctx->registerCFunction<OneArgFunc<cos> >(Symbol("cos"));
  ctx->registerCFunction<OneArgFunc<sin> >(Symbol("sin"));
  ctx->registerCFunction<OneArgFunc<tan> >(Symbol("tan"));
  ctx->registerCFunction<OneArgFunc<cosh> >(Symbol("cosh"));
  ctx->registerCFunction<OneArgFunc<sinh> >(Symbol("sinh"));
  ctx->registerCFunction<OneArgFunc<tanh> >(Symbol("tanh"));
  ctx->registerCFunction<OneArgFunc<acos> >(Symbol("acos"));
  ctx->registerCFunction<OneArgFunc<asin> >(Symbol("asin"));
  ctx->registerCFunction<OneArgFunc<atan> >(Symbol("atan"));
  ctx->registerCFunction<TwoArgFunc<atan2> >(Symbol("atan2"));
  ctx->registerCFunction<TwoArgFunc<fmod> >(Symbol("mod"));
  ctx->registerCFunction<TwoArgFunc<hypot> >(Symbol("hypot"));
  ctx->registerCFunction<TwoArgFunc<pow> >(Symbol("pow"));
  //ctx->registerCFunction<OneArgFunc<round> >("round"); // NOT SUPPORTED ON WINDOWS
  //ctx->registerCFunction<OneArgFunc<trunc> >("trunc"); // NOT SUPPORTED ON WINDOWS
  //ctx->registerCFunction<OneArgFunc<cbrt> >("cbrt"); // NOT SUPPORTED ON WINDOWS
  //ctx->registerCFunction<OneArgFunc<exp2> >("exp2"); // NOT SUPPORTED ON WINDOWS
  //ctx->registerCFunction<OneArgFunc<log2> >("log2"); // NOT SUPPORTED ON WINDOWS
  //ctx->registerCFunction<OneArgFunc<acosh> >("acosh"); // NOT SUPPORTED ON WINDOWS
  //ctx->registerCFunction<OneArgFunc<asinh> >("asinh"); // NOT SUPPORTED ON WINDOWS
  //ctx->registerCFunction<OneArgFunc<atanh> >("atanh"); // NOT SUPPORTED ON WINDOWS
  //ctx->registerCFunction<TwoArgFunc<remainder> >("remainder"); // NOT SUPPORTED ON WINDOWS
  //ctx->registerCFunction<TwoArgFunc<fmin> >("min"); // NOT SUPPORTED ON WINDOWS
  //ctx->registerCFunction<TwoArgFunc<fmax> >("max"); // NOT SUPPORTED ON WINDOWS
  // math constants
  Object *o = NULL;
  o = new Double(M_PI);
  ctx->setVar(Symbol("PI"), o);
  o->decRef();
  // don't care the others
  // utilities
  ctx->registerCFunction<Print>(Symbol("print"));
  ctx->registerCFunction<PrintLn>(Symbol("println"));
}
