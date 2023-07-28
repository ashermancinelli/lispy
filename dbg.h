#pragma once
#include <cstdint>
#include <string>
bool _l_isset(unsigned);
bool _l_fisset(std::string);
void _l_set(unsigned);
#define DBGBIT(i) _l_isset(i)
#define FISSET(X) _l_fisset(#X)
