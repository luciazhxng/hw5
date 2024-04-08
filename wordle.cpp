#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordleHelper(
    const std::string& in,
    std::map<char, int>& floating,
    const std::set<std::string>& dict,
    std::set<std::string>& words,
    std::string& alphabet,
    int index,
    std::string curr,
    int letters,
    int num_floating
);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
  map<char, int> floating_map;
  set<string> words;
  for(int i = 0; i < floating.length(); i++) {
    if(floating_map.find(floating[i]) == floating_map.end()) {
      floating_map[floating[i]] = 1;
    }
    else {
      floating_map[floating[i]]++;
    }
  }
  string alphabet = "abcdefghijklmnopqrstuvwxyz";

  if(in == "") {
    return words;
  }
  int letters = 0;
  for(int i = 0; i < in.length(); i++) {
    if(in[i] != '-') {
      letters ++;
    }
  }
  wordleHelper(in, floating_map, dict, words, alphabet, 0, "", letters, floating.length());
  return words;
}

// Define any helper functions here
void wordleHelper(
    const std::string& in,
    std::map<char, int>& floating,
    const std::set<std::string>& dict,
    std::set<std::string>& words,
    std::string& alphabet,
    int index,
    std::string curr,
    int letters,
    int num_floating
)
{
  if(index == in.length()) {
    if(dict.find(curr) != dict.end()) {
      if(words.find(curr) == words.end()) {
        words.insert(curr);
        // cout << curr <<endl;
        return;
      }
    }
  }
  if(index > in.length()) {
    return;
  }
  if(in[index] != '-') {
    curr = curr + in[index];
    wordleHelper(in, floating, dict, words, alphabet, index + 1, curr, letters - 1, num_floating);
    return;
  }
  map<char, int>::iterator floating_it;
  for(floating_it = floating.begin(); floating_it != floating.end(); ++floating_it) {
    map<char, int> new_floating = floating;
    new_floating[floating_it->first]--;
    if(new_floating[floating_it->first] == 0) {
      new_floating.erase(floating_it->first);
    }
    int new_num_floating = num_floating - 1;
    string new_curr = curr + floating_it->first;
    wordleHelper(in, new_floating, dict, words, alphabet, index + 1, new_curr, letters, new_num_floating);
  }
  if(in.length() > (curr.length() + num_floating + letters)) {
    
    for(unsigned int i = 0; i < alphabet.length(); i++) {
      wordleHelper(in, floating, dict, words, alphabet, index + 1, curr + alphabet[i], letters, num_floating);
    }
  }
}
