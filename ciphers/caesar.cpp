#include "caesar.h"
#include "caesarCrackResult.h"
#include "../libs/dictionary.h"
#include "../libs/file.h"

#include <z/core/timer.hpp>

#include <iostream>

#define CHARACTER_LIMIT 100

zstring caesarEncode(zstring input, int offset)
{
  return input.cipher(ALPHABET, shiftAlphabet(offset))
      .cipher(ALPHABET.upper(), shiftAlphabet(offset).upper());
}

zstring caesarEncode(zstring input)
{
  return caesarEncode(input, rand() % 25 + 1);
}

zstring caesarDecode(const zstring &input, int offset)
{
  return input.cipher(shiftAlphabet(offset), ALPHABET)
      .cipher(shiftAlphabet(offset).upper(), ALPHABET.upper());
}

z::core::array<crackResult> caesarCrack(zstring input)
{
  caesarCrackResult bestResult;
  z::core::array<crackResult> results;

  if (input.length() <= CHARACTER_LIMIT)
  {
    loadDictionary();

    "Cracking cipher"_u8.write(std::cout);

    for (int i = 1; i <= 25; i++)
    {
      zstring output = caesarDecode(input, i);
      output = output.contains(" ") ? output : wordSearch(output);
      caesarCrackResult newResult(output, i);

      "."_u8.write(std::cout);

      if (newResult.score > bestResult.score || i == 1)
        bestResult = newResult;

      results.append(newResult);
    }

    "Done!"_u8.writeln(std::cout);

    if (bestResult.key != 1)
      results.swap(0, bestResult.key - 1);

    return results;
  }
  else
  {
    results = caesarCrack(input.substr(0, CHARACTER_LIMIT));
    auto key = reinterpret_cast<caesarCrackResult &>(results[0]).key;

    results[0].update(caesarDecode(input, key));

    return results;
  }
}
