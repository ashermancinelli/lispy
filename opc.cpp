#include "opc.h"
#include <cassert>
#include <iostream>
#include <cstring>
#include <sstream>
using std::string;

std::string opc_str(OPC o)
{
#define OPC_ALL(o) case OPC::o: return std::string(#o);
  switch (o) {
#include "opc.inl.h"
    default: return "unknown";
  }
}

std::string INSTR::s() const {
  std::stringstream ss;
  ss << "INSTR{opc=" << opc_str(opc);
  if (args.size()) {
    ss << ", args={";
    for (auto i : args)
      ss << i << ",";
    ss << "}";
  }
  ss << "}";
  return ss.str();
}

INSTR instr_parse(std::string s) {
  std::string opcs = "";
  std::string rest = "";
  OPC opc;

  auto it = s.begin();
  while (it < s.end() && *it != ' ')
    opcs += std::toupper(*it++);
  while (it < s.end())
    rest += *it++;

#define OPC_ALL(o) if (opcs == #o) opc = OPC::o;
#include "opc.inl.h"

  assert(opc != OPC::NONE && "unable to parse opcode");

  int a, b, c;
  switch (opc) {
    default:
      std::cerr << "opc=" << static_cast<int>(opc) << "\n";
      assert(false && "couldn't match opc");
#define OPC_ARG0(O) \
    case OPC::O: return {opc, {}};
#define OPC_ARG1(O) \
    case OPC::O: \
      sscanf(rest.c_str(), "%d", &a); \
      return {opc, {a}};
#define OPC_ARG2(O) \
    case OPC::O: \
      sscanf(rest.c_str(), "%d%d", &a, &b); \
      return {opc, {a, b}};
#define OPC_ARG3(O) \
    case OPC::O: \
      sscanf(rest.c_str(), "%d%d%d", &a, &b, &c); \
      return {opc, {a, b, c}};
#include "opc.inl.h"
  }
}

OPC opc_parse(std::string s)
{
  string opcs = "";
  for (const char c : s) {
    if (c == ' ')
      break;
    opcs += std::toupper(c);
  }

#define OPC_ALL(o) if (opcs == #o) return OPC::o;
#include "opc.inl.h"

  return OPC::NONE;
}
