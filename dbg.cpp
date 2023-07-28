#include "dbg.h"
static uint64_t bits = 0;

void _l_set(unsigned i) {
  bits |= (1 << i);
}

bool _l_isset(unsigned i) {
  return bits & (1 << i);
}

bool _l_fisset(std::string s) {
#define DBGFLAG(S, B, DESC) if (s == #S) return _l_isset(B);
#include "flags.inl.h"
  return false;
}
