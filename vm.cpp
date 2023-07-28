#include "vm.h"
#include "dbg.h"
#include <iostream>
#include <cassert>

static int64_t stk[STACK_MAX];
static int64_t hp[HEAP_MAX];
static uint64_t sp = 0;
static uint64_t sp_max = 0;
static uint64_t ioffset = 0;

#define STKDBG(X) if(FISSET(vm_stack)){X;}
#define PO(X) X=stk[--sp]; STKDBG(std::cerr << "popped " << X << "\n");
#define PU(X) stk[sp++]=X; STKDBG(std::cerr << "pushed " << X << "\n");

#define HPS(I, X) hp[I]=X;
#define HPG(I, X) X=hp[I];

void vm_run_one(INSTR const& i) {
  int a, b, c;
  if (FISSET(vm_stack)) {
    std::cout << "stack:";
    for (int i=0; i<sp; i++) {
      std::cout << stk[i] << ",";
    }
    std::cout << "\n";
  }
  if(FISSET(vm)) {
    std::cerr << i.s() << "\n";
  }
  switch (i.opc) {
    case OPC::ASSERT:
      PO(a); assert(a == i.args[0] && "assertion failed");
      break;
    case OPC::PUSH: PU(i.args[0]); break;
    case OPC::MEM_SIZE: PU(sp_max); break;
    case OPC::MEM_ALLOC: PO(sp_max); break;
    case OPC::ADD: PO(a);PO(b);PU(a+b); break;
    case OPC::SUB: PO(a);PO(b);PU(b-a); break;
    case OPC::STORE: PO(a);HPS(i.args[0],a); break;
    case OPC::LOAD: HPG(i.args[0],a);PU(a); break;
    case OPC::CMP_GT: PO(a);PU(((int)a>i.args[0])); break;
    case OPC::CMP_GE: PO(a);PU(((int)a>=i.args[0])); break;
    case OPC::CMP_LT: PO(a);PU(((int)a<i.args[0])); break;
    case OPC::CMP_LE: PO(a);PU(((int)a<=i.args[0])); break;
    case OPC::CMP_EQ: PO(a);PU(((int)a==i.args[0])); break;
    case OPC::SELECT: PO(a);PU(i.args[!a]); break;
    case OPC::GOTO: ioffset+=i.args[0]; break;
    default:
      std::cerr << i.s() << "\n";
      assert(false && "unknown opc");
      break;
  }
}

int vm_run(std::vector<INSTR> const& instrs) {
  while (ioffset < instrs.size()) {
    vm_run_one(instrs[ioffset]);
    ioffset++;
  }
  return stk[sp];
}
