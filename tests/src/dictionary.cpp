#include "catch.hpp"

#include "../../libs/dictionary.h"

#include <z/core/string.hpp>
#include <z/core/array.hpp>
#include <z/core/split.hpp>
#include <z/file/lines.hpp>

#include <fstream>

zstring alphabet = "abcdefghijklmnopqrstuvwxyz";
zstring alphabet10 = "klmnopqrstuvwxyzabcdefghij";

zstring testingText = "one two three";
zstring testingWrongText = "testingg onee twoo threee";
zstring voicePassport = "my voice is my passport verify me";

TEST_CASE("Random Alphabet", "[dict]")
{
  REQUIRE(randomAlphabet() != alphabet);
}

TEST_CASE("Shift Alphabet", "[dict]")
{
  REQUIRE(shiftAlphabet(0) == alphabet);
  REQUIRE(shiftAlphabet(26) == alphabet);
  REQUIRE(shiftAlphabet(-26) == alphabet);

  REQUIRE(shiftAlphabet(10) == alphabet10);
  REQUIRE(shiftAlphabet(10 + 26) == alphabet10);
  REQUIRE(shiftAlphabet(10 - 26) == alphabet10);
  REQUIRE(shiftAlphabet(10 - 2 * 26) == alphabet10);
}

TEST_CASE("Spell Check", "[dict]")
{
  REQUIRE(spellCheck(testingText) == 100.0);
  REQUIRE(spellCheck(testingWrongText) == 0.0);
}

TEST_CASE("Word Search", "[dict]")
{
  REQUIRE(wordSearch(removeSpaces(testingText)) == testingText);
  REQUIRE(wordSearch(removeSpaces(voicePassport)) == voicePassport);
}

// TODO: In general, come up with a toolset that allows us to analyze and manipulate
// our sample text as well as our dictionary to be able to figure out where our efficiencies,
// inefficiencies, and flaws occur. We should be able to add and remove words,
// and see score distributions for our input text.

// Part of the above todo is done; we've implemented wordSearch analysis and visualization
void testFile(zstring filename, float scoreThreshold = 0)
{
  for (auto line : z::file::lines(filename))
  {
    if (line == "")
      continue; // HACK ?

    zstring input = line.trim();
    zstring output = wordSearch(removeSpaces(input));
    float score = spellCheck(output);

    INFO("input: " << input << "\n");
    INFO("output: " << output << "\n");
    INFO("score: " << score << "\n");

    REQUIRE(score > scoreThreshold);
  }
}

TEST_CASE("Word Search 1 (large sample size)", "[.][.p1][dict]")
{
  testFile("data/p1.txt");
}

TEST_CASE("Word Search 2 (large sample size)", "[.][.p2][dict]")
{
  testFile("data/p2.txt");
}

TEST_CASE("Word Search 3 (large sample size)", "[.][.p3][dict]")
{
  testFile("data/p3.txt");
}

TEST_CASE("Word Search 4 (large sample size)", "[.][.p4][dict]")
{
  testFile("data/p4.txt");
}
