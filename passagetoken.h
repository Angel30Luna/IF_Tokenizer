#ifndef _PASSAGETOKEN_H_
#define _PASSAGETOKEN_H_


#include <string>
#include <vector>
#include "parttoken.h"
#include "passagetokenizer.h"

using namespace std;

class PassageToken
{
private:
    string name;
    string text;
    PassageTokenizer passageTokenizer;
    vector<PartToken*> parts;
    vector<PartToken> regParts;
public:
    PassageToken(string name= "", string text= "");
    string getName() const {return name;};
    string getText() const {return text;};
    void setName(string);
    void setText(string);
    void setPassageTokenizer(PassageTokenizer* pasageTokenizer){this->passageTokenizer = passageTokenizer;};//remove
    PartToken* getToken(int index);
    void addPart(PartToken& part);
    void print();
    int partsSize() { return parts.size();};
    //remember that getToken returns a pointer
};

#endif