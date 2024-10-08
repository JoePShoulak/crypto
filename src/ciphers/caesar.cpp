#include "caesar.h"
#include "../helpers/dictionary.h"

#include <z/core/range.hpp>
#include <iostream>

using z::core::range;

#define CHARACTER_LIMIT 100

zstring caesarEncode(const zstring &input, int offset)
{
  return input.cipher(ALPHABET, shiftAlphabet(offset))
      .cipher(ALPHABET.upper(), shiftAlphabet(offset).upper());
}

zstring caesarEncode(const zstring &input, std::string offset)
{
  return caesarEncode(input, std::stoi(offset));
}

zstring caesarDecode(const zstring &input, int offset)
{
  return input.cipher(shiftAlphabet(offset), ALPHABET)
      .cipher(shiftAlphabet(offset).upper(), ALPHABET.upper());
}

zstring caesarDecode(const zstring &input, std::string offset)
{
  return caesarDecode(input, std::stoi(offset));
}

z::core::array<caesarCrackResult> caesarCrack(const zstring &input)
{
  caesarCrackResult bestResult;
  z::core::array<caesarCrackResult> results;

  if (input.length() <= CHARACTER_LIMIT)
  {
    loadDictionary();

    for (int i : range(1, 26))
    {
      zstring output = caesarDecode(input, i);

      if (!output.contains(" "))
        output = wordSearch(output);

      caesarCrackResult newResult(output, i);

      if (newResult.score > bestResult.score || i == 1)
        bestResult = newResult;

      results.append(newResult);
    }

    if (bestResult.key != 1)
      results.swap(0, bestResult.key - 1);

    return results;
  }
  else
  {
    results = caesarCrack(input.substr(0, CHARACTER_LIMIT));
    results[0].update(caesarDecode(input, results[0].key));

    return results;
  }
}
