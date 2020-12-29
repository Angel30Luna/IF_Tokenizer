//Project 2
#ifndef _PASSAGE_TOKENIZER_H
#define _PASSAGE_TOKENIZER_H

#include "parttoken.h"
#include <vector>
using namespace std;

class PassageTokenizer
{
private:
    PartToken theNextPart;
    PartToken returnPart;
    string currentPassage;
    bool ifNextPart;
    int currPart;
    vector<part_t> parts;
    vector<PartToken> undefinedParts;
    int undefinedPartsIndex;
    vector<Set> setParts;
    int setPartsIndex;
    vector<IfPart> ifParts;
    int ifPartsIndex;
    vector<IfElse> ifElseParts;
    int ifElsePartsIndex;
    vector<ElsePart> elseParts;
    int elsePartsIndex;
    vector<GoTo> gotoParts;
    int gotoPartsIndex;
    vector<Text> textParts;
    int textPartsIndex;
    vector<Link> linkParts;
    int linkPartsIndex;
    vector<Block> blockParts;
    int blockPartsIndex;
    Set* setPart;
    Block* blockPart;
    GoTo* gotoPart;
    ElsePart* elsePart;
    IfElse* ifElsePart;
    IfPart* ifPart;
    Link* linkpart;
    Text* textPart;

public:
    PassageTokenizer();
    PassageTokenizer(string);
    PartToken* nextPart(); //no longer returns a pointer since that doesn't work apparently
    string getCurrentPassage() const;
    bool hasNextPart() const;
    const PartToken* getPartToken(int index) const;
    int getNumParts() const;

    //For testing
    Set getSet(int i) const {return setParts.at(i);}


};

#endif