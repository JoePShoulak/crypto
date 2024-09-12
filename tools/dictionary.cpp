#include "dictionary.h"

#include <z/core/split.hpp>
#include <z/core/join.hpp>
#include <z/core/array.hpp>

#include <fstream>
#include <iostream>
#include <cmath>

z::util::dictionary dict;

void loadDictionary()
{
  if (dict.length() > 0)
  {
    return;
  }

  std::ifstream file("tools/words.txt");

  z::core::timeout time(1000000); // 1 second timeout

  "Loading dictionary..."_u8.write(std::cout);
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

  for (int i = 0; i < words.length(); i++)
  {
    zstring word = words[i].filter({{'a', 'z'}, {'A', 'Z'}}).lower();

    if (dict.isWord(word))
    {
      successes++;
    }
  }

  return round(10000 * (successes / float(words.length() - 1))) / 100; // todo: confirm the -1
}

zstring wordSearch(zstring text)
{
  loadDictionary();

  int maxWordLength = 10;

  zstring output = "";

  // First pass, greedy longest-first search for word options
  for (int i = 0; i < text.length();)
  {
    bool wordFound = false;

    for (int k = maxWordLength; k > 0; k--)
    {
      zstring word = text.substr(i, k);
      if (dict.isWord(word))
      {
        if (output[output.length() - 1] != ' ' && i > 0)
        {
          output.append(" ");
        }

        output.append(word + " ");
        i += k;
        wordFound = true;
        break;
      }
    }

    if (!wordFound)
    {
      output.append(text.substr(i++, 1));
    }
  }

  // Second pass, correct for the greed errors
  z::core::array<zstring> words = z::core::split(output, " "_u8);

  // Scan the array for greed errors
  for (int i = 0; i < words.length() - 1; i++)
  {
    if (dict.isWord(words[i]) && !dict.isWord(words[i + 1]))
    {
      zstring combo = words[i] + words[i + 1];

      // Try every way of putting a space between these two words until they're both real words
      for (int i = 1; i < combo.length(); i++)
      {
        zstring sub0 = combo.substr(0, i);
        zstring sub1 = combo.substr(i, combo.length() - 1);

        if (dict.isWord(sub0) && dict.isWord(sub1))
        {
          words.replace(i, 1, sub0);
          words.replace(i + 1, 1, sub1);
        }
      }
    }
  }

  return z::core::join(words, " ").replace("  ", " "); // TODO: why do I need to do this replace...?
}
