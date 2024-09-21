#ifndef CRACK_RESULT_H
#define CRACK_RESULT_H

#include <iostream>
#include <z/core/string.hpp>

class missingText : public std::runtime_error
{
public:
  missingText() : std::runtime_error("Need to define the text first!") {}
};

struct crackResult
{
  zstring text;
  zstring summary;
  float score;

  virtual void update(zstring) {}

  virtual zstring getKey() const noexcept;
};

#endif