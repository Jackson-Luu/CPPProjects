#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "assignments/wl/lexicon.h"
#include "assignments/wl/word_ladder.h"

void wl_print(std::vector<std::string> input);

int main() {
  auto lexicon_set = GetLexicon("assignments/wl/words.txt");
  std::unordered_map<std::string, int> lexicon;

  //convert lexicon to hash table/dictionary
  for (const auto& item : lexicon_set) {
    lexicon.insert({item, 0});
  }

  std::cout << "Enter start word (RETURN to quit): ";

  std::string start;
  std::getline(std::cin, start);
  if (start.length() == 0) {
    std::exit(0);
  }
  std::cout << "Enter destination word: ";

  std::string end;
  std::getline(std::cin, end);

  // perform BFS for word ladders
  auto wl = BFS(start, end, lexicon);
  if (wl.empty() == true) {
    std::cout << "No ladder found." << std::endl;
  } else {
    std::cout << "Found ladder: ";
    for (auto it = wl.begin(); it != wl.end(); ++it) {
      wl_print(*it);
    }
  }
}

// function for printing word ladders
void wl_print(std::vector<std::string> input) {
  for (auto it = input.begin(); it != input.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
}