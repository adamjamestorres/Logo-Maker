//
// Created by Adam Torres on 5/30/21.
//

#include "KeywordCompare.h"
void KeywordCompare::Evaluate(std::list<sf::Text>& textList)
{
    //2-pointer technique to evaluate list
    std::list<sf::Text>::iterator front_itr = textList.begin();
    std::list<sf::Text>::iterator trailing_itr = textList.begin();

    std::string compString = "";

    while (front_itr != textList.end())
    {
        compString += front_itr->getString();
        front_itr->setFillColor(sf::Color::White);

        if (front_itr->getString() == " ")
        {
            compString.clear();
            trailing_itr = ++front_itr;
            continue;
        }
        if (InNumberSet(front_itr->getString()[0]))
        {
            front_itr->setFillColor(sf::Color::Red);
            compString.clear();
            trailing_itr = ++front_itr;
            continue;
        }
        if (InOperatorSet(front_itr->getString()[0]))
        {
            front_itr->setFillColor(sf::Color::Green);
            compString.clear();
            trailing_itr = ++front_itr;
            continue;
        }
        if (InWordSet(compString))
        {
            while (trailing_itr != front_itr)
            {
                trailing_itr->setFillColor(sf::Color::Blue);
                trailing_itr++;
            }

            trailing_itr->setFillColor(sf::Color::Blue);

        }

        front_itr++;
    }
}

bool KeywordCompare::InNumberSet(char c)
{
    if (numberSet.find(c) != numberSet.end())
        return true;

    return false;
}

bool KeywordCompare::InOperatorSet(char c)
{
    if (operatorSet.find(c) != operatorSet.end())
        return true;

    return false;
}

bool KeywordCompare::InWordSet(std::string s)
{
    if (wordSet.find(s) != wordSet.end())
        return true;

    return false;
}

void KeywordCompare::SetKeywords()
{
    std::array<char, 10> numArr = { '0','1','2','3','4','5','6','7','8','9' };
    numberSet.insert(numArr.begin(),numArr.end());

    std::array<char, 15> operatorArr = { '!','@', '#', '$', '%', '^', '&', '*', '<', '>','+','-','=','(',')'};
    operatorSet.insert(operatorArr.begin(), operatorArr.end());

    std::array<std::string, 4> stringArr = { "int", "char", "double", "float" };
    wordSet.insert(stringArr.begin(), stringArr.end());
}
