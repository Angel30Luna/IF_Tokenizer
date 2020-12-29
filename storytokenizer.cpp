#include "storytokenizer.h"
#include <sstream>
#include <iostream>

	const string openingTag("<tw-passagedata");
	const string endingTag("</tw-passagedata>");

/* Constructor */
StoryTokenizer::StoryTokenizer(string story)
{
		this->story = story;
}

	bool StoryTokenizer::hasNextPassage(){
		//if the find function cannot find the next begginning tag, return false
		if(story.find(openingTag) == string::npos){
			return false;
		} else {
			return true;
		}
	}
	PassageToken StoryTokenizer::nextPassage(){

		//find inital passage of whole passage
		int openingTagIndex = story.find(openingTag);

		//extract the name of the first token
		story = story.substr(openingTagIndex + openingTag.size());
		string name = story;
		name = name.substr(story.find("name") + 6);
		name = name.substr(0, name.find("\""));

		//extract the passage
		string passage = story;
		passage = passage.substr(passage.find("position=") + 10);
		//cout << passage << endl;
		passage = passage.substr(passage.find(">") + 1);
		passage = passage.substr(0, passage.find(endingTag));


		PassageToken passageToken(name, passage);
		return passageToken;
	}



