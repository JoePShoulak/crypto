#include "../../src/dictionary.h"
#include "../../ciphers/caesar.h"

#include <z/all.hpp>
#include <iostream>

using namespace std;

void deleteMessage(zstring message, ostream &os)
{
  for (int i : z::core::range(message.length()))
    os << '\b' << ' ' << '\b' << flush;
}

void analyze(std::function<float(zstring)> evaluator)
{
  // for (auto id : z::core::array<zstring>{"1", "2", "3", "4"})
  for (auto id : z::core::array<zstring>{"5", "6"})
  {
    zstring message;
    auto lines = z::file::lines("data/wiki"_zs + id + ".txt").collect();
    double total = lines.length();

    ("  Analyzing file "_u8 + id + " (" + total + " paragraphs)" + "... ").write(cerr);

    int i = 0;
    z::core::array<zstring> result;

    for (auto line : lines)
    {
      if (++i % 50 == 0 || i == total)
      {
        deleteMessage(message, cerr);

        zstring p = zstring(((int)(i / total * 1000)) / 10.0);
        if (!p.count('.'))
          p += ".0";

        message = p + "%";
        message.write(cerr);
      }

      auto input = line.trim();

      result.push(evaluator(input));
    }

    deleteMessage(message, cerr);

    cerr << "Done!" << endl;

    z::core::join(result, ',').writeln(cout);
  }

  cerr << endl;
}
