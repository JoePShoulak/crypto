#include "catch.hpp"

#include "../../libs/dictionary.cpp"

TEST_CASE("Testing Random Alphabet")
{
  REQUIRE(randomAlphabet() != "abcdefghijklmnopqrstuvwxyz");
}

TEST_CASE("Testing Shift Alphabet")
{
  REQUIRE(shiftAlphabet(0) == "abcdefghijklmnopqrstuvwxyz");
  REQUIRE(shiftAlphabet(26) == "abcdefghijklmnopqrstuvwxyz");
  REQUIRE(shiftAlphabet(-26) == "abcdefghijklmnopqrstuvwxyz");

  REQUIRE(shiftAlphabet(5) == "fghijklmnopqrstuvwxyzabcde");

  REQUIRE(shiftAlphabet(10) == "klmnopqrstuvwxyzabcdefghij");
  REQUIRE(shiftAlphabet(36) == "klmnopqrstuvwxyzabcdefghij");
  REQUIRE(shiftAlphabet(-16) == "klmnopqrstuvwxyzabcdefghij");
}

TEST_CASE("Testing Spell Check")
{
  REQUIRE(checkSpelling("testing one two three") == 100.0);
  REQUIRE(checkSpelling("testingg onee twoo threee") == 0.0);
}

TEST_CASE("Testing Word Search")
{
  REQUIRE(wordSearch("testingonetwothree") == "testing one two three");
  REQUIRE(wordSearch("myvoiceismypassportverifyme") == "my voice is my passport verify me");
}
