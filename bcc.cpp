#include <vector>
#include <cassert>
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <tuple>
#include "opc.h"
#include "dbg.h"
#include "vm.h"

using std::vector;
using std::string;
using std::tuple;

int help(vector<string> const& args) {
  std::cout << "Usage: \n"
    << args[0] << " [input filename] [-L<debug option>]"
    << "\n"
    << "\t-LN\tEnable debug bit N\n"
#define DBGFLAG(O, BIT, DESC) \
  << "\t-L" #O << "\t" << DESC << "\n"
#include "flags.inl.h"
    ;
  return 1;
}

void dbgbits(vector<string> const& args) {
  for (const string& arg : args) {
    if (arg.size() > 2 && arg[0] == '-' && arg[1] == 'L') {
      char hx[128];
      sscanf(arg.c_str(), "-L%s", hx);

      // parse hex bit
      if (hx[0] == '0' && hx[1] == 'x') {
        unsigned hxi = (unsigned)std::strtol(hx, NULL, 0);
        _l_set(hxi);
        std::cerr << "setting debug bit " << hxi << "\n";
      }

#define DBGFLAG(O, BIT, DESC) \
      if (std::string(#O) == std::string(hx)) { \
        _l_set(BIT); \
        std::cerr << "setting debug bit for " << #O << " (" << BIT << ")\n"; \
      }
#include "flags.inl.h"
    }
  }
}

static int st[STACK_MAX];
int main(int argc, char** argv) {
  vector<string> args(argv, argv+argc);

  if (args.size() < 2)
    return help(args);

  for (const auto& s : args)
    if (s == "-h" || s == "--help")
      return help(args);

  dbgbits(args);

  std::ifstream f(args[1]);
  vector<INSTR> lines;
  std::string line;
  int lineno=0;
  while (std::getline(f, line)) {
    if (!line.size())
      continue;
    if (line[0] == ';')
      continue;
    if (FISSET(fe)) {
      std::cout << lineno++ << ":" << line << "\n";
    }
    lines.push_back(instr_parse(line));
  }

  if (FISSET(fe))
    for (auto const& i : lines)
      std::cout << i.s() << "\n";

  int ec = vm_run(lines);

  return ec;
}
