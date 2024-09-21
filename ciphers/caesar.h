#ifndef CAESAR_H
#define CAESAR_H

#include <z/core/string.hpp>
#include <z/core/array.hpp>

#include "../libs/dictionary.h"
#include "crackResult.h"

zstring caesarEncode(zstring input, int offset);
zstring caesarEncode(zstring input);

zstring caesarDecode(const zstring &input, int offset);

z::core::array<crackResult> caesarCrack(zstring input);

#endif
