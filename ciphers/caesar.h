#ifndef CAESAR_H
#define CAESAR_H

#include <z/core/string.hpp>
#include <z/core/array.hpp>

// TODO: Can this be generalized to the point of there only being one
//  struct between all the ciphers?

struct caesarCrackResult
{
  zstring text;
  float score;
  int key;
  zstring summary;
};

zstring caesarEncode(zstring input, int offset);
zstring caesarEncode(zstring input);

zstring caesarDecode(zstring input, int offset);

z::core::array<caesarCrackResult> caesarCrack(zstring input);

#endif
