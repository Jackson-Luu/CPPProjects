#ifndef ASSIGNMENTS_WL_WORD_LADDER_H_
#define ASSIGNMENTS_WL_WORD_LADDER_H_

#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

std::vector<std::string> GenerateWords(const std::vector<std::string> wl,
                                    std::unordered_map<std::string, int>& dictionary);
std::vector<std::vector<std::string>> BFS(const std::string start,
                                        const std::string end,
                                        std::unordered_map<std::string, int> dictionary);

#endif  // ASSIGNMENTS_WL_WORD_LADDER_H_