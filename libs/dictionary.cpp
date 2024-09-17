#include "dictionary.h"

#include <z/core/split.hpp>
#include <z/core/join.hpp>
#include <z/core/array.hpp>

#include <fstream>
#include <iostream>
#include <cmath>

z::util::dictionary dict;

zstring getAlphabet()
{
  return "abcdefghijklmnopqrstuvwxyz";
}

zstring shiftAlphabet(int offset)
{
  return getAlphabet().substr(offset, 26) + getAlphabet().substr(0, offset);
}

void loadDictionary()
{
  if (dict.length() > 0)
    return;

  "Loading dictionary..."_u8.write(std::cout);

  std::ifstream file("libs/words.txt");
  z::core::timeout time(1000000); // 1 second timeout

  while (!dict.read(file, time))
  {
    '.'_u8.write(std::cout);
    time.reset();
  }

  (" Done! Loaded "_u8 + dict.length() + " words.").writeln(std::cout);
}

float checkSpelling(zstring text)
{
  loadDictionary();

  float successes = 0;
  z::core::array<zstring> words = z::core::split(text, zstring(" "));
  float total = float(words.length());

  for (int i = 0; i < words.length(); i++)
  {
    zstring word = words[i].filter({{'a', 'z'}, {'A', 'Z'}}).lower();

    if (dict.isWord(word))
      successes++;
  }

  return round(10'000 * (successes / total)) / 100;
}

zstring wordSearch(zstring input)
{
  loadDictionary();

  // First pass, greedy longest-first search for word options
  zstring output = "";
  int i = 0;
  bool midIsland = false;

  while (i < input.length())
  {
    bool wordFound = false;

    for (int k = dict.maxWordLength(); k > 0; k--)
    {
      zstring word = input.substr(i, k);

      if (dict.isWord(word))
      {
        output.append(" "_u8 + word);

        i += k;
        wordFound = true;
        midIsland = false;
        break;
      }
    }

    if (!wordFound)
    {
      output.append(zstring(midIsland ? "" : " ") + input.substr(i++, 1));
      midIsland = true;
    }
  }

  if (output[output.length() - 1] == ' ')
    output = output.substr(0, output.length() - 1);
  if (output[0] == ' ')
    output = output.substr(1, output.length() - 1);

  // Second pass, correct for the greed errors
  z::core::array<zstring> words = z::core::split(output, " "_u8);

  for (int i = 0; i < words.length() - 1; i++)
  {
    if (dict.isWord(words[i]) && !dict.isWord(words[i + 1]))
    {
      zstring combo = words[i] + words[i + 1];

      // Try every way of putting a space between these two words until they're both real words
      for (int i = combo.length() - 1; i >= 1; i--)
      {
        zstring subA = combo.substr(0, i);
        zstring subB = combo.substr(i, combo.length() - i);

        if (dict.isWord(subA) && dict.isWord(subB))
        {
          words.replace(i, 1, subA);
          words.replace(i + 1, 1, subB);
        }
      }
    }
  }

  return z::core::join(words, " ");
}
