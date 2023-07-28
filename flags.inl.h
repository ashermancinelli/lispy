#ifdef DBGFLAG
DBGFLAG(opc, 0x1, "enable debug output for opcode")
DBGFLAG(vm, 0x10, "enable debug output for virtual machine")
DBGFLAG(vm_stack, 0x20, "enable debug output for virtual machine")
DBGFLAG(fe, 0x100, "enable debug output for frontend")
#undef DBGFLAG
#endif
