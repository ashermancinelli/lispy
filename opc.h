#pragma once
#include <string>
#include <regex>
#include <tuple>

#define OPC_ALL(o) o,
enum class OPC {
#include "opc.inl.h"
};

struct INSTR {
  OPC opc = OPC::NONE;
  std::vector<int> args;
  std::string s() const;
};

std::string opc_str(OPC o);
INSTR instr_parse(std::string s);
