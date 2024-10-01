#include "substitution.h"
#include "../src/dictionary.h"

#include <iostream>

zstring substitutionEncode(zstring input, zstring key)
{
  return input.cipher(ALPHABET, key.toLower())
      .cipher(ALPHABET.upper(), key.upper());
}

zstring substitutionEncode(zstring input)
{
  auto key = randomAlphabet();

  return input.cipher(ALPHABET, key.toLower())
      .cipher(ALPHABET.upper(), key.upper());
}

zstring substitutionDecode(zstring input, zstring key)
{
  return input.cipher(key.toLower(), ALPHABET)
      .cipher(key.upper(), ALPHABET.upper());
}

z::core::array<substitutionCrackResult> substitutionCrack(zstring input)
{
  // TODO: Implement
  return z::core::array<substitutionCrackResult>();
}