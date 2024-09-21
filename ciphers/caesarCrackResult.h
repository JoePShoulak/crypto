#ifndef CAESAR_CRACK_RESULT_H
#define CAESAR_CRACK_RESULT_H

#include "crackResult.h"

struct caesarCrackResult : public crackResult
{
  int key;

  ~caesarCrackResult() {}

  caesarCrackResult();
  caesarCrackResult(const zstring &text, int key);

  void update(zstring newText);

  zstring getKey() const noexcept override;
};

#endif