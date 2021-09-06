//
// Created by Adam Torres on 5/30/21.
//

#ifndef FINAL_PROJECT_KEYWORDCOMPARE_H
#define FINAL_PROJECT_KEYWORDCOMPARE_H
#include <set>
#include <array>
#include <list>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <iostream>

class KeywordCompare
{
public:
    KeywordCompare() { SetKeywords(); };

    void Evaluate(std::list<sf::Text>&);

private:
    void SetKeywords();
    bool InNumberSet(char);
    bool InOperatorSet(char);
    bool InWordSet(std::string);

    std::set<char> numberSet;
    std::set<char> operatorSet;
    std::set<sf::String> wordSet;
};
#endif //FINAL_PROJECT_KEYWORDCOMPARE_H
