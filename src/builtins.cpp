#include "builtins.h"
#include "stack.h"
#include "context.h"
#include "instruction.h"
#include <iostream>
#include <cmath>

Concat::Concat() : CFunction(2, true) {
}

Concat::~Concat() {
}

Object* Concat::clone() const {
  return new Add();
}

int Concat::call(Stack &stack, Context &) {
  std::string v1 = stack.popString();
  std::string v0 = stack.popString();
  stack.pushString(v0+v1);
  return EVAL_NEXT;
}

// ---

Add::Add() : CFunction(2, true) {
}

Add::~Add() {
}

Object* Add::clone() const {
  return new Add();
}

int Add::call(Stack &stack, Context &) {
  double v1 = stack.popDouble();
  double v0 = stack.popDouble();
  stack.pushDouble(v0+v1);
  return EVAL_NEXT;
}

// ---

Sub::Sub() : CFunction(2, true) {
}

Sub::~Sub() {
}

Object* Sub::clone() const {
  return new Sub();
}

int Sub::call(Stack &stack, Context &) {
  double v1 = stack.popDouble();
  double v0 = stack.popDouble();
  stack.pushDouble(v0-v1);
  return EVAL_NEXT;
}

// ---

Minus::Minus() : CFunction(1, true) {
}

Minus::~Minus() {
}

Object* Minus::clone() const {
  return new Sub();
}

int Minus::call(Stack &stack, Context &) {
  double v = stack.popDouble();
  stack.pushDouble(-v);
  return EVAL_NEXT;
}

// ---

Mult::Mult() : CFunction(2, true) {
}

Mult::~Mult() {
}

Object* Mult::clone() const {
  return new Mult();
}

int Mult::call(Stack &stack, Context &) {
  double v1 = stack.popDouble();
  double v0 = stack.popDouble();
  stack.pushDouble(v0*v1);
  return EVAL_NEXT;
}

// ---

Div::Div() : CFunction(2, true) {
}

Div::~Div() {
}

Object* Div::clone() const {
  return new Div();
}

int Div::call(Stack &stack, Context &) {
  double v1 = stack.popDouble();
  double v0 = stack.popDouble();
  stack.pushDouble(v0/v1);
  return EVAL_NEXT;
}

// ---

Sin::Sin() : CFunction(1, true) {
}

Sin::~Sin() {
}

Object* Sin::clone() const {
  return new Sin();
}

int Sin::call(Stack &stack, Context &) {
  double r = sin(stack.popDouble());
  stack.pushDouble(r);
  return EVAL_NEXT;
}

// ---

Cos::Cos() : CFunction(1, true) {
}

Cos::~Cos() {
}

Object* Cos::clone() const {
  return new Cos();
}

int Cos::call(Stack &stack, Context &) {
  double r = cos(stack.popDouble());
  stack.pushDouble(r);
  return EVAL_NEXT;
}

// ---

Tan::Tan() : CFunction(1, true) {
}

Tan::~Tan() {
}

Object* Tan::clone() const {
  return new Tan();
}

int Tan::call(Stack &stack, Context &) {
  double r = tan(stack.popDouble());
  stack.pushDouble(r);
  return EVAL_NEXT;
}

// ---

Equal::Equal() : CFunction(2, true) {
}

Equal::~Equal() {
}

Object* Equal::clone() const {
  return new Equal();
}

int Equal::call(Stack &stack, Context &) {
  Object *o2 = stack.pop();
  Object *o1 = stack.pop();
  stack.pushBoolean(o1->equal(o2));
  o1->decRef();
  o2->decRef();
  return EVAL_NEXT;
}

// ---

NotEqual::NotEqual() : CFunction(2, true) {
}

NotEqual::~NotEqual() {
}

Object* NotEqual::clone() const {
  return new Equal();
}

int NotEqual::call(Stack &stack, Context &) {
  Object *o2 = stack.pop();
  Object *o1 = stack.pop();
  stack.pushBoolean(o1->notEqual(o2));
  o1->decRef();
  o2->decRef();
  return EVAL_NEXT;
}

// ---

LessThan::LessThan() : CFunction(2, true) {
}

LessThan::~LessThan() {
}

Object* LessThan::clone() const {
  return new Equal();
}

int LessThan::call(Stack &stack, Context &) {
  Object *o2 = stack.pop();
  Object *o1 = stack.pop();
  stack.pushBoolean(o1->lessThan(o2));
  o1->decRef();
  o2->decRef();
  return EVAL_NEXT;
}

// ---

GreaterThan::GreaterThan() : CFunction(2, true) {
}

GreaterThan::~GreaterThan() {
}

Object* GreaterThan::clone() const {
  return new Equal();
}

int GreaterThan::call(Stack &stack, Context &) {
  Object *o2 = stack.pop();
  Object *o1 = stack.pop();
  stack.pushBoolean(o1->greaterThan(o2));
  o1->decRef();
  o2->decRef();
  return EVAL_NEXT;
}

// ---

LessThanEqual::LessThanEqual() : CFunction(2, true) {
}

LessThanEqual::~LessThanEqual() {
}

Object* LessThanEqual::clone() const {
  return new Equal();
}

int LessThanEqual::call(Stack &stack, Context &) {
  Object *o2 = stack.pop();
  Object *o1 = stack.pop();
  stack.pushBoolean(o1->lessThanEqual(o2));
  o1->decRef();
  o2->decRef();
  return EVAL_NEXT;
}

// ---

GreaterThanEqual::GreaterThanEqual() : CFunction(2, true) {
}

GreaterThanEqual::~GreaterThanEqual() {
}

Object* GreaterThanEqual::clone() const {
  return new Equal();
}

int GreaterThanEqual::call(Stack &stack, Context &) {
  Object *o2 = stack.pop();
  Object *o1 = stack.pop();
  stack.pushBoolean(o1->greaterThanEqual(o2));
  o1->decRef();
  o2->decRef();
  return EVAL_NEXT;
}


// ---

Print::Print() : CFunction(1, false) {
}

Print::~Print() {
}

Object* Print::clone() const {
  return new Print();
}

int Print::call(Stack &stack, Context &) {
  Object *o = stack.pop();
  if (o == NULL) {
    std::cout << "<Null>";
  } else {
    o->toStream(std::cout);
    o->decRef();
  }
  return EVAL_NEXT;
}

// ---

void RegisterBuiltins(Context &ctx) {
  CFunction *f = 0;
  
  f = new Minus(); ctx.setVar("__uminus__", f); f->decRef();
  f = new Concat(); ctx.setVar("..", f); f->decRef();
  f = new Add(); ctx.setVar("+", f); f->decRef();
  f = new Sub(); ctx.setVar("-", f); f->decRef();
  f = new Mult(); ctx.setVar("*", f); f->decRef();
  f = new Div(); ctx.setVar("/", f); f->decRef();
  f = new Equal(); ctx.setVar("==", f); f->decRef();
  f = new NotEqual(); ctx.setVar("!=", f); f->decRef();
  f = new LessThan(); ctx.setVar("<", f); f->decRef();
  f = new LessThanEqual(); ctx.setVar("<=", f); f->decRef();
  f = new GreaterThan(); ctx.setVar(">", f); f->decRef();
  f = new GreaterThanEqual(); ctx.setVar(">=", f); f->decRef();
  f = new Sin(); ctx.setVar("sin",f); f->decRef();
  f = new Cos(); ctx.setVar("cos", f); f->decRef();
  f = new Tan(); ctx.setVar("tan", f); f->decRef();
  f = new Print(); ctx.setVar("print", f); f->decRef();
}
