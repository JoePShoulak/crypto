#include "caesarCrackResult.h"
#include "../libs/dictionary.h"

caesarCrackResult::caesarCrackResult() : key(0)
{
  this->text = text;
  summary = 0;
  score = 0.f;
}

caesarCrackResult::caesarCrackResult(const zstring &text, int key) : key(key)
{
  this->text = text;

  if (!text)
    throw missingText();

  score = checkSpelling(text);

  summary = zstring(key) + ": " + text.substr(0, 30) + "... " + score + "%\n";
}

void caesarCrackResult::update(zstring newText)
{
  text = newText;
  score = checkSpelling(text);
}

zstring caesarCrackResult::getKey() const noexcept
{
  return key;
}