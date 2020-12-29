#include "IFInterpreter.h"
#include "storytokenizer.h"
#include <iostream>
#include <fstream>
#include <sstream>

IFInterpreter::IFInterpreter(std::string fileName){
	keepLooping = true;

	string line;

	//Open input.txt for reading
	std::ifstream in(fileName);
	if (!in.is_open()){
		cout << "Couldn't open " << fileName << " for reading!\n";
	}

	//Read in the story from input.txt
	getline(in, line);
	while (in && line != "</html>"){
		story += line + '\n';
		getline(in, line);
  	}

	//Construct the StoryTokenizer object
  StoryTokenizer st(story);

  //Iterate through all of the passages in the story
  int pass = 0;
  while (st.hasNextPassage())
  {
    //Use the PassageToken to construct a PassageTokenizer
    PassageToken ptok = st.nextPassage();
    //once the PassageToken has been created, store it into the passages unordered_map and vector

    PassageTokenizer pt(ptok.getText());


    //Iterate through all of the parts of the passage
    while (pt.hasNextPart())
    {
      		PartToken* stok(pt.nextPart());
		ptok.addPart(*stok);
		/*
		if(stok->getType() == SET){
			Set* temp = (Set*) stok;
			variables[temp->getName()] = temp->getValue();

		}
		*/

    }
	passages.push_back(ptok);
	uMapPassages[ptok.getName()] = ptok;


  }
}

void IFInterpreter::print(){
	for(PassageToken passage : passages){
		cout << "Passage " << passage.getName() << endl;
		passage.print();
	}
}

void IFInterpreter::play(){
	//present first passage
	interpretPassage(uMapPassages.at(passages.at(0).getName()));
	while (keepLooping){
		//get information
		if(links.size() == 0){
			keepLooping = false;
			break;
		}
		for (int i = 0; i < links.size(); i++){
			cout << i + 1 << ": " << links.at(i)->getDisplay() << endl;
		}

		int input = -1; //intialize it to fail the condition
		do{
			cin >> input;

			if(!cin.good()){
				cin.clear();
				cin.ignore();
				input = -1;
			}

			if(input > 0 && input <= links.size())
				break;

			cout << "Bad input, please try again." << endl;

		} while (input < 1 || input > links.size());

		Link* link = links.at(input - 1);

		//clear links vector
		links.clear();

		//present next passage
		interpretPassage(uMapPassages.at(link->getPassageName()));


	}
}

void IFInterpreter::interpretPassage(PassageToken passage){
	bool ignoreElse = false;
	bool ignoreElseIf = false;

	//look for goto parttoken first
	for (int i = 0; i < passage.partsSize(); i++){
		const PartToken* part = passage.getToken(i);
		if(part->getType() == GOTO){
			GoTo* temp = (GoTo*) part;
			links.clear();
			interpretPassage(uMapPassages[temp->getName()]);
			return;
		}

	}
	if(passage.getName() != ""){
		cout << "Passage name:" << passage.getName() << endl;;
	}


	for(int i = 0; i < passage.partsSize(); i++){
		const PartToken* part = passage.getToken(i);

		if (part->getType() == SET){
			Set* tempSet = (Set*) part;
			variables[tempSet->getName()] = tempSet->getValue();
		} else if (part->getType() == TEXT){
			Text* tempText = (Text*) part;
			tempText->print();//will need to remove quotation marks eventually

		} else if (part->getType() == LINK){
			Link* tempLink = (Link*) part;
			tempLink->print();
			links.push_back(tempLink);
		} else if(part->getType() == IF){
			ignoreElse = false;
			ignoreElseIf = false;

			IfPart* tempIf = (IfPart*) part;
			if(variables[tempIf->getName()] == tempIf->getvalue()){//if values match
				PartToken* nestedPart = passage.getToken(i + 1);

				determineIf(nestedPart);
				ignoreElse = true;
				ignoreElseIf = true;
			}

		} else if(part->getType() == ELSEIF && !ignoreElseIf){

			ignoreElse = false;
			ignoreElseIf = false;

			IfElse* tempIf = (IfElse*) part;
			if(variables[tempIf->getName()] == tempIf->getvalue()){//if values match
				PartToken* nestedPart = passage.getToken(i + 1);

				determineIf(nestedPart);
				ignoreElse = true;
				ignoreElseIf = true;
			}

		} else if(part->getType() == ELSE && !ignoreElse){
				PartToken* nestedPart = passage.getToken(i + 1);

				determineIf(nestedPart);
		} else if(part->getType() == BLOCK){

		}
	}
	cout << endl;
}

void IFInterpreter::determineIf(PartToken* block){
	bool ignoreElse = false;
	bool ignoreElseIf = false;

	Block* b = (Block*) block;

	//look for goto parttoken first
	for (int i = 0; i < b->getNumParts(); i++){
		const PartToken* part = b->get(i);
		if(part->getType() == GOTO){
			GoTo* temp = (GoTo*) part;
			links.clear();
			interpretPassage(uMapPassages[temp->getName()]);
			return;
		}

	}


	for(int i = 0; i < b->getNumParts(); i++){
		const PartToken* part = b->get(i);

		if (part->getType() == SET){
			Set* tempSet = (Set*) part;
			variables[tempSet->getName()] = tempSet->getValue();
		} else if (part->getType() == TEXT){
			Text* tempText = (Text*) part;
			tempText->print();//will need to remove quotation marks eventually

		} else if (part->getType() == LINK){
			Link* tempLink = (Link*) part;
			tempLink->print();
			links.push_back(tempLink);
		} else if(part->getType() == IF){
			ignoreElse = false;
			ignoreElseIf = false;

			IfPart* tempIf = (IfPart*) part;
			if(variables[tempIf->getName()] == tempIf->getvalue()){//if values match
				PartToken* nestedPart = b->get(i + 1);

				determineIf(nestedPart);
				ignoreElse = true;
				ignoreElseIf = true;
			}

		} else if(part->getType() == ELSEIF && !ignoreElse){

			ignoreElse = false;
			ignoreElseIf = false;

			IfElse* tempIf = (IfElse*) part;
			if(variables[tempIf->getName()] == tempIf->getvalue()){//if values match
				PartToken* nestedPart = b->get(i + 1);

				determineIf(nestedPart);
				ignoreElse = true;
				ignoreElseIf = true;

			}

		} else if(part->getType() == ELSE && !ignoreElseIf){
			PartToken* nestedPart = b->get(i + 1);

			determineIf(nestedPart);
		} else if(part->getType() == BLOCK){

		}
	}
	cout << endl;
}
