#ifndef WORDGAME_H
#define WORDGAME_H

#include <set>
#include <string>
#include "openai.hpp"
#include <iostream>
#include <algorithm>
#include <fstream>

class Test {
protected:
    std::set<std::string> usedWords;
    std::string lastChar;
public:
     bool isWordValid(const std::string& wordToSearch, const std::set<std::string>& wordslist);
     bool isWordValid(const std::string& wordToSearch, const std::string& word);
     bool isWordValid(const std::string& str);
     bool isWordReal(const std::string& wordToSearch);
};

class WordGame : public Test{
private:
    std::set<std::string> usedWords;
    std::string lastChar;

public:
    std::string aiWordans;
    WordGame();
    int maxwrong;
    int maxattempt;
    std::string getUserWord();
    void Gamesetting();
    std::string generateAIWord();

    void playGame();
};

#endif // WORDGAME_H
