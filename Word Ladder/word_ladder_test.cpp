/*

  == Explanation and rational of testing ==

  I have written tests to ensure that the BFS returns word ladders that contain valid words
  according to the given dictionary and that all word ladders must begin with the input
  start word and finish with the input end word. In addition, the tests test that the correct
  number of word ladders so that only the shortest valid word ladders are being returned. The
  GenerateWords function in word_ladder.cpp is not tested for as it is not an interface function,
  it is only used by the BFS function as such we avoid testing for implementation.

*/
#include <string>
#include <unordered_map>

#include "assignments/wl/word_ladder.h"
#include "catch.h"

SCENARIO("Word ladders contain valid words") {
  GIVEN("A valid start and end word in a dictionary") {
    std::string s = "line";
    std::string e = "cake";
    std::unordered_map<std::string, int> d = {{"line", 0}, {"cake", 0}, {"cine", 0}, {"cane", 0}, {"lane", 0}, {"lake", 0}, {"like", 0}, {"lick", 0}, {"land", 0}, {"lack", 0}, {"cone", 0}, {"pine", 0}};
    WHEN("You try to search for a valid word ladder") {
      auto result = BFS(s, e, d);
      THEN("You get lists beginning with the start word and ending with the destination") {
        for (auto it = result.begin(); it != result.end(); ++it) {
          CHECK((*it).size() >= 2);
          REQUIRE((*it).front() == s);
          REQUIRE((*it).back() == e);
        }
        AND_THEN("each step is a valid word") {
          for (auto it = result.begin(); it != result.end(); ++it) {
            for (auto st = (*it).begin(); st != (*it).end(); ++st) {
              REQUIRE(d.find(*st) != d.end());
            }
          }
        }
      }
    }
  }
  GIVEN("A valid start and end word in a dictionary") {
    std::string s = "work";
    std::string e = "play";
    std::unordered_map<std::string, int> d = {{"work", 0}, {"play", 0}, {"fork", 0}, {"form", 0}, {"foam", 0}, {"flam", 0}, {"flay", 0}, {"pork", 0}, {"perk", 0}, {"peak", 0}, {"pean", 0}, {"plan", 0}, {"peat", 0}, {"plat", 0}, {"pert", 0}, {"porn", 0}, {"pirn", 0}, {"pian", 0}, {"port", 0}, {"word", 0}, {"wood", 0}, {"pood", 0}, {"plod", 0}, {"ploy", 0}, {"worm", 0}, {"worn", 0}, {"wort", 0}, {"bort", 0}, {"boat", 0}, {"blat", 0}, {"wert", 0}};
    WHEN("You try to search for a valid word ladder") {
      auto result = BFS(s, e, d);
      THEN("You get lists beginning with the start word and ending with the destination") {
        for (auto it = result.begin(); it != result.end(); ++it) {
          CHECK((*it).size() >= 2);
          REQUIRE((*it).front() == s);
          REQUIRE((*it).back() == e);
        }
        AND_THEN("each step is a valid word") {
          for (auto it = result.begin(); it != result.end(); ++it) {
            for (auto st = (*it).begin(); st != (*it).end(); ++st) {
              REQUIRE(d.find(*st) != d.end());
            }
          }
        }
      }
    }
  }
}

SCENARIO("BFS returns the correct number of word ladders") {
  GIVEN("A valid start and end word in a dictionary") {
    std::string s = "line";
    std::string e = "cake";
    std::unordered_map<std::string, int> d = {{"line", 0}, {"cake", 0}, {"cine", 0}, {"cane", 0}, {"lane", 0}, {"lake", 0}, {"like", 0}, {"lick", 0}, {"land", 0}, {"lack", 0}, {"cone", 0}, {"pine", 0}};
    WHEN("You try to search for a valid word ladder") {
      auto result = BFS(s, e, d);
      THEN("You get the correct number of word ladders") {
        REQUIRE(result.size() == 4);
      }
    }
  }
  GIVEN("A valid start and end word in a dictionary") {
    std::string s = "work";
    std::string e = "play";
    std::unordered_map<std::string, int> d = {{"work", 0}, {"play", 0}, {"fork", 0}, {"form", 0}, {"foam", 0}, {"flam", 0}, {"flay", 0}, {"pork", 0}, {"perk", 0}, {"peak", 0}, {"pean", 0}, {"plan", 0}, {"peat", 0}, {"plat", 0}, {"pert", 0}, {"porn", 0}, {"pirn", 0}, {"pian", 0}, {"port", 0}, {"word", 0}, {"wood", 0}, {"pood", 0}, {"plod", 0}, {"ploy", 0}, {"worm", 0}, {"worn", 0}, {"bort", 0}, {"boat", 0}, {"blat", 0}, {"wert", 0}};
    WHEN("You try to search for a valid word ladder") {
      auto result = BFS(s, e, d);
      THEN("You get the correct number of word ladders") {
        REQUIRE(result.size() == 12);
      }
    }
  }
}