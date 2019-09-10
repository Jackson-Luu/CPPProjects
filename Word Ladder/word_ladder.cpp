#include "assignments/wl/word_ladder.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>


// Generates words for next step in a word ladder
std::vector<std::string> GenerateWords(const std::vector<std::string> wl,
                                       std::unordered_map<std::string, int>& dictionary) {
  std::vector<std::string> word_list;
  std::string new_word = wl.back();

  // loop through every character in a word
  for (auto it = new_word.begin(); it != new_word.end(); ++it) {
    char letter = *it;

    // replace with each letter of the alphabet
    for (char c = 'a'; c <= 'z'; ++c) {
      new_word.replace(it, it + 1, std::string(1, c));

      // if word is valid append to return vector
      try {
        size_t visited = dictionary.at(new_word);
        if (visited == 0 || visited == wl.size()) {
          word_list.emplace_back(new_word);
          dictionary[new_word] = wl.size();
        }
      } catch (const std::exception& e) {
      }
    }

    // restore original letter
    new_word.replace(it, it + 1, std::string(1, letter));
  }

  // sort words alphabetically
  std::sort(word_list.begin(), word_list.end());
  return word_list;
}

std::vector<std::vector<std::string>> BFS(const std::string start,
                                          const std::string end,
                                          std::unordered_map<std::string, int> dictionary) {
  std::vector<std::vector<std::string>> wl_all;
  std::queue<std::vector<std::string>> wl_queue;
  std::vector<std::string> wl;
  std::vector<std::string> next_words;
  size_t wl_length;

  // initialise first word ladder for queue and mark as visited
  std::vector<std::string> init{start};
  wl_queue.emplace(init);
  dictionary[start] = 1;

  // loop until nothing left in queue
  while (!wl_queue.empty()) {
    wl = wl_queue.front();
    wl_queue.pop();

    // if word ladder is longer than one that has been found, exit
    if (wl_all.empty() == false && wl.size() >= wl_length) {
      break;
    }

    // generate next step
    next_words = GenerateWords(wl, dictionary);

    // queue new word ladders with generated words
    for (auto it = next_words.begin(); it != next_words.end(); ++it) {
      std::vector<std::string> new_wl = wl;
      new_wl.emplace_back(*it);

      // if destination word found, move on
      if ((*it).compare(end) == 0) {
        wl_all.emplace_back(new_wl);
        wl_length = new_wl.size();
        break;
      }
      wl_queue.emplace(new_wl);
    }
  }
  return wl_all;
}