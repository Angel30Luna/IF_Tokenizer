// This has been editd
// Project 2
#include "parttoken.h"
#include "passagetokenizer.h"
#include "passagetoken.h"
#include <sstream>
#include <algorithm>
using namespace std;

//throw the error

PartToken::PartToken(string inPartText, part_t inPartType) : partText(inPartText)
{
    partType = inPartType;
}

//default constructor
PartToken::PartToken() : partText(""), partType(TEXT)
{}


void PartToken::setType(part_t inPartType)
{
    partType = inPartType;
}

void PartToken::setText(string inPartText)
{
    partText = inPartText;
}

void PartToken::print() const{
	cout << "NULL part token.\t" << partText << "\t";
    if (partType == SET)
        cout << "SET" << endl;
    else if (partType == TEXT)
        cout << "TEXT" << endl;
    else if (partType ==GOTO)
        cout << "GOTO" << endl;
    else if (partType == IF)
        cout << "IF" << endl;
    else if (partType == ELSEIF)
        cout << "ELSEIF" << endl;
    else if (partType == ELSE)
        cout << "ELSE" << endl;
    else if (partType == LINK)
        cout << "LINK" << endl;
    else
        cout << "TYPE STORED INCORRECTLY" << endl;

}

//     SET STUFF STARTS HERE    *********************************************************************
Set::Set(string text)
{
	PartToken(text, SET);
	istringstream iss(text);
	string setKeyword;
	string toKeyword; //Just a place holder
	string value;

	//use istringstream to extract parts of the string.
	//I chose a string stream so I can easily ignore blank spaces
	iss >> setKeyword;
	iss >> name; // assign the Set object's name
	iss >> toKeyword;
	iss >> value;

	//since value currently contains "true)" or "false)", remove parenthesis
	value = value.substr(0, value.size() - 1);

	//converts value to lowercase
	transform(text.begin(), text.end(), text.begin(), ::tolower);

	//assign the Set object's value
	if(value == "true"){
		this->value = true;
	} else {
		this->value = false;
	}

}

void Set::print() const{
	if (value == true){
			cout << "Set:\tvar=" << name << ", value=true" << endl;
	} else {
			cout << "Set:\tvar=" << name << ", value=false" << endl;
	}
}


//     GOTO STUFF STARTS HERE    *********************************************************************
GoTo::GoTo(string text){
	PartToken(text, GOTO);
	string temp;
	string quote = "&quot;";
	bool validName= false;

	//parse name out of the text
	if (text.find(quote) == string::npos){
		//first &quot; is not found
		name = "Error - invalid name.";
	} else {
		temp = text.substr(text.find(quote) + quote.size());
		if(temp.find(quote) == string::npos){
			//ending &quot; is not found
		} else {
			validName = true;
			temp = temp.substr(0, temp.find(quote));
		}
	}

	//store the appropriate value for name
	if (validName){
		name = temp;
	} else {
		name = "Error - Invalid name.";
	}

}
void GoTo::print() const{
	//Go-to: target=[target]
	cout << "Go-to: target=" << name << endl;
}

//     BLOCK STUFF STARTS HERE    *********************************************************************
Block::Block(string text)  {
	PartToken(text, BLOCK);
	//cout << "Block: " << text.substr(1, text.size() - 2) << endl;
	text = text.substr(1, text.size() - 2);
	PassageToken ptok("Block", text);

	PassageTokenizer pt(ptok.getText());

	while (pt.hasNextPart())
	{
			PartToken* stok(pt.nextPart());
			parts.push_back(stok);
			//ptok.addPart(*stok);

	}
	//ptok.print();

}

void Block::print() const{
	cout << "START BLOCK" << endl;
	//print out parttokens inside of block
	for (int i = 0; i < parts.size(); i ++){
		parts.at(i)->print();
	}

	cout << "END BLOCK" << endl;

}

PartToken* Block::get(int index){

    //default return values
    return parts.at(index);
}


//     ElsePart STUFF STARTS HERE    *********************************************************************
ElsePart::ElsePart(){
	PartToken("", ELSE);


}
void ElsePart::print() const{
	cout << "Else" << endl;

}

//     IfElse STUFF STARTS HERE    *********************************************************************
IfElse::IfElse(string text){
	PartToken(text, ELSEIF);
	istringstream iss(text);
	string keyword;
	string isKeyword; //Just a place holder
	string value;

	//use istringstream to extract parts of the string.
	//I chose a string stream so I can easily ignore blank spaces
	iss >> keyword;
	iss >> testName; // assign the ELSEIF object's tstName
	iss >> isKeyword;
	iss >> value;

	//since value currently contains "true)" or "false)", remove parenthesis
	value = value.substr(0, value.size() - 1);

	//converts value to lowercase
	transform(text.begin(), text.end(), text.begin(), ::tolower);

	//assign the Set object's value
	if(value == "true"){
		testValue = true;
	} else {
		testValue = false;
	}

}

void IfElse::print() const{

	//Else-if: var=[var], value=[value]
	if (testValue == true){
		cout << "Else-if: var=" << testName << ", value=true" << endl;
	} else {
		cout << "Else-if: var=" << testName << ", value=false" << endl;
	}

}

//     IfPart STUFF STARTS HERE    *********************************************************************
IfPart::IfPart(string text){
	PartToken(text, IF);
	istringstream iss(text);
	string keyword;
	string isKeyword; //Just a place holder
	string value;

	//use istringstream to extract parts of the string.
	//I chose a string stream so I can easily ignore blank spaces
	iss >> keyword;
	iss >> testName; // assign the ELSEIF object's tstName
	iss >> isKeyword;
	iss >> value;

	//since value currently contains "true)" or "false)", remove parenthesis
	value = value.substr(0, value.size() - 1);

	//converts value to lowercase
	transform(text.begin(), text.end(), text.begin(), ::tolower);

	//assign the Set object's value
	if(value == "true"){
		testValue = true;
	} else {
		testValue = false;
	}

}

void IfPart::print() const{
	//If: var=[var], value=[value]
	if (testValue == true){
		cout << "If: var=" << testName << ", value=true" << endl;
	} else {
		cout << "If: var=" << testName << ", value=false" << endl;
	}
}

//     Link STUFF STARTS HERE    *********************************************************************
Link::Link(string text){

	/*
		[[Simple]]
		Displays as “Simple”; links to passage named “Simple”
		[[Take the blue pill-&gt;Bad dream?]]
		Displays as “Take the blue pill”; links to passage named “Bad dream?”
	*/
	PartToken(text, LINK);
	string keyword = "-&gt;";

	if (text.find(keyword) == string::npos){
		//keyword doesn't exist
		display = text.substr(2, text.size() - 4);
		passageName = display;
	} else {
		display = text.substr(2, text.find(keyword) - 2);
		passageName = text.substr(text.find(keyword) + keyword.size());
		passageName = passageName.substr(0, passageName.size() - 2); // remove the last two brackets.
	}



}

void Link::print() const{
	//Link: display=[display], target=[target]
	cout << display;
}


//     Text STUFF STARTS HERE    *********************************************************************
Text::Text(string text){
	PartToken(text, TEXT);
	this->text = text;
}

void Text::print() const{
	cout << text;
}

