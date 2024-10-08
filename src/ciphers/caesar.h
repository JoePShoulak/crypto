#ifndef CAESAR_H
#define CAESAR_H

#include <z/core/string.hpp>
#include <z/core/array.hpp>
#include <iostream>

#include "../helpers/dictionary.h"

// TODO: Can this be generalized to the point of there only being one
//  struct between all the ciphers?

// Either all keys would have to be strings by the time they get created,
// or they would all need an overridden virtual method for returning their
// typename T into a string

class missingText : public std::runtime_error
{
public:
  missingText() : std::runtime_error("Need to define the text first!") {}
};

struct caesarCrackResult
{
  int key;
  zstring text;
  zstring summary;
  float score;

  caesarCrackResult()
  {
    key = 0;
    this->text = text;
    summary = 0;
    score = 0.f;
  }

  caesarCrackResult(const zstring &text, int key)
  {
    this->text = text;
    this->key = key;

    if (!text)
      throw missingText();

    score = spellCheck(text);

    summary = zstring(key) + ": " + text.substr(0, 30) + "... " + score + "%\n";
  }

  void update(zstring newText)
  {
    text = newText;
    score = spellCheck(text);
  }
};

zstring caesarEncode(const zstring &input, int offset);
zstring caesarEncode(const zstring &input, std::string offset);

zstring caesarDecode(const zstring &input, int offset);
zstring caesarDecode(const zstring &input, std::string offset);

z::core::array<caesarCrackResult> caesarCrack(const zstring &input);

#endif
