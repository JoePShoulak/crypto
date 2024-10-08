#include "../../src/helpers/dictionary.h"

#include <z/all.hpp>
#include <iostream>

using namespace std;

void analyze(std::function<float(zstring)> evaluator, bool random = false)
{
// #define TESTING
  if (random)
  {
#ifdef TESTING
    float total = 2000;
#else
    float total = 31603;
#endif
    ("  Generating "_zs + total + " random paragraphs... ").write(cerr);

    z::core::array<zstring> result;
    z::util::progress loadingBar;
    for (int i : z::core::range(total))
    {
      result.push(evaluator(""));
      loadingBar.set(std::cerr, i, total);
    }

    z::core::join(result, ',').writeln(cout);

    return;
  }

#ifdef TESTING
  for (auto id : z::core::array<zstring>{"5", "6"})
#else
  for (auto id : z::core::array<zstring>{"1", "2", "3", "4"})
#endif
  {
    auto lines = z::file::lines("src/data/wiki/wiki"_zs + id + ".txt").collect();
    double total = lines.length();

    ("  Analyzing file "_u8 + id + " (" + total + " paragraphs)" + "... ").write(cerr);

    z::core::array<zstring> result;
    z::util::progress loadingBar;
    for (int i=0; i < lines.length(); i++)
    {
      result.push(evaluator(lines[i].trim()));
      loadingBar.set(std::cerr, i, total);
    }

    z::core::join(result, ',').writeln(cout);
  }
}
