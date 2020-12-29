#include "passagetoken.h"
#include <iostream>
#include <sstream>

PassageToken::PassageToken(string name, string text)
{
    this->name = name;
    this->text = text;
}
void PassageToken::addPart(PartToken& part){
	parts.push_back(&part);
	regParts.push_back(part);
}

void PassageToken::setName(string newName)
{
    name = newName;
}

void PassageToken::setText(string newText)
{
    text = newText;
}


PartToken* PassageToken::getToken(int index)
{
	return parts.at(index);
}
 void PassageToken::print(){
	 for(int i = 0; i < parts.size(); i++){
		 parts.at(i)->print();
	 }
 }


