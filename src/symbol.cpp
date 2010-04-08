#include "symbol.h"

SymbolTable& SymbolTable::Instance() {
  static SymbolTable instance;
  return instance;
}

const char* SymbolTable::GetString(const Symbol &s) {
  return Instance().getString(s);
}

Symbol SymbolTable::GetSymbol(const std::string &name) {
  return Instance().getSymbol(name);
}

SymbolTable::SymbolTable() {
}

SymbolTable::~SymbolTable() {
  mSyms.clear();
  mStrs.clear();
}

Symbol SymbolTable::getSymbol(const std::string &name) {
  if (mSyms.hasKey(name)) {
    return Symbol(mSyms.getValue(name));
  } else {
    size_t id = mStrs.size();
    mSyms.insert(name, id);
    mStrs.push_back(name);
    return Symbol(id);
  }
}

const char* SymbolTable::getString(const Symbol &s) {
  if (s.valid() && s.id() < mStrs.size()) {
    return mStrs[s.id()].c_str();
  } else {
    return 0;
  }
}
