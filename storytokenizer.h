#ifndef _STORYTOKENIZER_H_
#define _STORYTOKENIZER_H_


#include <string>
#include <sstream>
#include "passagetoken.h"
#include "passagetokenizer.h"

using namespace std;

class StoryTokenizer
{
private:
    string currLine;
    string story;
    bool ifNextPassage;
    PassageToken theNextPassage;
public:
    bool hasNextPassage();
    PassageToken nextPassage();
    StoryTokenizer(string = "");
    void newStory(string);

};

#endif