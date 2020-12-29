//Project 2
#include "passagetokenizer.h"

PassageTokenizer::PassageTokenizer(){

}
PassageTokenizer::PassageTokenizer(string passage) : theNextPart("", TEXT)
{
    if (passage != "")
    {
        //use to initialize part token at end of constructor
        string forNextPart;
        part_t forNextPartType = TEXT;

        //first, check if start of passage is not text
        if (passage.at(0) == '[')
        {
            //first part from the passage can't be a block, so not looking for it
            if (passage.find("[[") == 0 && passage.find("]]") != -1)
            {
                forNextPart = passage.substr(0, passage.find("]]")-passage.find("[[") + 2);
                // passage.find("]]")-passage.find("[[") + 1 should give the size of the link
                forNextPartType = LINK;
                currentPassage = passage.substr(passage.find("]]") + 2);
            }
        } //end if for link part
        else if (passage.at(0) == '(')
        {
            if (passage.find("go-to:") == 1)
            {
                forNextPartType = GOTO;
                forNextPart = passage.substr(0, passage.find(")") + 1);
                currentPassage = passage.substr(passage.find(")") + 1);
            }
            else if (passage.find("set:") == 1)
            {
                forNextPartType = SET;
                forNextPart = passage.substr(0, passage.find(")") + 1);
                currentPassage = passage.substr(passage.find(")") + 1);
            }
            else if (passage.find("if:") == 1)
            {
                forNextPartType = IF;
                forNextPart = passage.substr(0, passage.find(")") + 1);
                currentPassage = passage.substr(passage.find(")") + 1);
            }
            else if (passage.find("else-if:") == 1)
            {
                forNextPartType = ELSEIF;
                forNextPart = passage.substr(0, passage.find(")") + 1);
                currentPassage = passage.substr(passage.find(")") + 1);
            }
            else if (passage.find("else:") == 1)
            {
                forNextPartType = ELSE;
                forNextPart = passage.substr(0, passage.find(")") + 1);
                currentPassage = passage.substr(passage.find(")") + 1);
            }
        } //end if for command part
        /* First part must be text if not a command or link. Need to find where the part ends and if there is
            * a part after it */
        if (forNextPartType == TEXT) //part type was not changed
        {
            forNextPartType = TEXT;
            bool keepLooping = true;
            int i;  //i will be the index of the next part
            for (i = 0; i < passage.size() && keepLooping; i++)
            {
                if (passage.at(i) == '[')
                {
                    //first part from the passage can't be a block, so not looking for it
                    if (passage.find("[[") == i && passage.find("]]") != -1)
                    {
                        keepLooping = false;
                    }
                }
                else if (passage.at(i) == '(')
                {
                    if (passage.find("go-to:") == i + 1)
                    {
                        keepLooping = false;
                    }
                    else if (passage.find("set:") == i + 1)
                    {
                        keepLooping = false;
                    }
                    else if (passage.find("if:") == i + 1)
                    {
                        keepLooping = false;
                    }
                    else if (passage.find("else-if:") == i + 1)
                    {
                        keepLooping = false;
                    }
                    else if (passage.find("else:") == i + 1)
                    {
                        keepLooping = false;
                    }
                }
            }
            //now have index of next part, i, which is also the size of this text part
            if (keepLooping == true)
            {
                forNextPart = passage;
                currentPassage = "";
            }
            else
            {
            forNextPart = passage.substr(0, i - 1);
            currentPassage = passage.substr(i - 1);
            }
        } //end if for text part
        theNextPart = PartToken(forNextPart, forNextPartType);
        ifNextPart = true;
    }
    else
        ifNextPart = false;
}

PartToken* PassageTokenizer::nextPart()
{
    //if no next part
    if (ifNextPart == false)
    {
	    PartToken x("", TEXT);
	    theNextPart = x;
        return nullptr;
    }
    /*make a copy of "theNextPart" to return at end, because theNextPart will
     *be modified to be the new next part */
    PartToken toReturn = theNextPart;
    //to create new theNextPart token
    string forNextPart;
    part_t forNextPartType = TEXT;

    if (currentPassage == "")
    {
        ifNextPart = false;
    } //there is no next part if the remaining passage text is empty
    else if (theNextPart.getType() == IF || theNextPart.getType() == ELSEIF || theNextPart.getType() == ELSE)
    {
        //assume there must be a block following and that it is set up correctly
        forNextPartType = BLOCK;
        int brackets = 1; //number of open brackets. Starting with 1 at the start of the remaining passage text
        int i;
        for (i = 1; i < currentPassage.size() && brackets > 0; i++)
        {
            if (currentPassage.at(i) == '[')
                brackets++;
            if (currentPassage.at(i) == ']')
                brackets--;
        }
        forNextPart = currentPassage.substr(0, i);
        currentPassage = currentPassage.substr(i);
    } //end if for if the current part is a command, to make the next part a block
    else if (currentPassage.at(0) == '[')
    {
        if (currentPassage.find("[[") == 0 && currentPassage.find("]]") != -1)
        {
            forNextPart = currentPassage.substr(0, currentPassage.find("]]")-currentPassage.find("[[") + 2);
            forNextPartType = LINK;
            currentPassage = currentPassage.substr(currentPassage.find("]]") + 2);
        }
    } //end if for if the next passage may be a link
    else if (currentPassage.at(0) == '(')
    {
        if (currentPassage.find("go-to:") == 1)
        {
            forNextPartType = GOTO;
            forNextPart = currentPassage.substr(0, currentPassage.find(")") + 1);
            currentPassage = currentPassage.substr(currentPassage.find(")") + 1);
        }
        else if (currentPassage.find("set:") == 1)
        {
            forNextPartType = SET;
            forNextPart = currentPassage.substr(0, currentPassage.find(")") + 1);
            currentPassage = currentPassage.substr(currentPassage.find(")") + 1);
        }
        else if (currentPassage.find("if:") == 1)
        {
            forNextPartType = IF;
            forNextPart = currentPassage.substr(0, currentPassage.find(")") + 1);
            currentPassage = currentPassage.substr(currentPassage.find(")") + 1);
        }
        else if (currentPassage.find("else-if:") == 1)
        {
            forNextPartType = ELSEIF;
            forNextPart = currentPassage.substr(0, currentPassage.find(")") + 1);
            currentPassage = currentPassage.substr(currentPassage.find(")") + 1);
        }
        else if (currentPassage.find("else:") == 1)
        {
            forNextPartType = ELSE;
            forNextPart = currentPassage.substr(0, currentPassage.find(")") + 1);
            currentPassage = currentPassage.substr(currentPassage.find(")") + 1);
        }
    } //end if for if the next passage may be a command
    if (forNextPartType == TEXT)
    {
        bool keepLooping = true;
        int i;
        for (i = 0; i < currentPassage.size() && keepLooping; i++)
        {
            if (currentPassage.at(i) == '[')
            {
                if (currentPassage.find("[[") == i && currentPassage.find("]]") != -1)
                {
                    keepLooping = false;
                }
            }
            else if (currentPassage.at(i) == '(')
            {
                if (currentPassage.find("go-to:") == i + 1)
                {
                    keepLooping = false;
                }
                else if (currentPassage.find("set:") == i + 1)
                {
                    keepLooping = false;
                }
                else if (currentPassage.find("if:") == i + 1)
                {
                    keepLooping = false;
                }
                else if (currentPassage.find("else-if:") == i + 1)
                {
                    keepLooping = false;
                }
                else if (currentPassage.find("else:") == i + 1)
                {
                    keepLooping = false;
                }
            }
        } //end of for loop to find i
        if (keepLooping == true)
        {
            forNextPart = currentPassage;
            currentPassage = "";
        }
        else
        {
        forNextPart = currentPassage.substr(0, i - 1);
        currentPassage = currentPassage.substr(i - 1);
        }
    } //end if for if the next passage is text
    theNextPart = PartToken(forNextPart, forNextPartType);
    returnPart = toReturn;
	switch (returnPart.getType()){
		case SET:{
			setPart = new Set(returnPart.getText());
			setPart->setType(SET);
			return setPart;
			break;
			}
		case BLOCK:{
			blockPart = new Block(returnPart.getText());
			blockPart->setType(BLOCK);
			return blockPart;
			break;
		}
		case GOTO:{
			gotoPart = new GoTo(returnPart.getText());
			gotoPart->setType(GOTO);
			return gotoPart;
			break;
		}
		case ELSE:{
			elsePart = new ElsePart();
			elsePart->setType(ELSE);
			return elsePart;
			break;
		}
		case ELSEIF:{
			ifElsePart = new IfElse(returnPart.getText());
			ifElsePart->setType(ELSEIF);
			return ifElsePart;
			break;
		}
		case IF:{
			ifPart = new IfPart(returnPart.getText());
			ifPart->setType(IF);
			return ifPart;
			break;
		}
		case LINK:{
			linkpart = new Link(returnPart.getText());
			linkpart->setType(LINK);
			return linkpart;
			break;
		}
		case TEXT:{
			textPart = new Text(returnPart.getText());
			textPart->setType(TEXT);
			return textPart;
			break;
		}
		default:
    			return &returnPart;
			break;
	}


}

bool PassageTokenizer::hasNextPart() const
{
    return ifNextPart;
}

string PassageTokenizer::getCurrentPassage() const
{
    return currentPassage;
}

const PartToken* PassageTokenizer::getPartToken(int index) const
{
    const PartToken* ret;
    //cout << "Called getPartToken with index " << index <<  endl;
    if (parts.at(index) == SET)
    {
        //cout << "looping index" << endl;
        int setIndex = 0;
        for (int i = 0; i <= index && i < parts.size(); i++)
            if (parts.at(i) == SET)
                setIndex++;
        ret = &setParts.at(setIndex - 1);
    }
    else if(parts.at(index) == IF)
    {
        int ifIndex = 0;
        for (int i = 0; i <= index && i < parts.size(); i++)
            if (parts.at(i) == IF)
                ifIndex++;
        ret = &ifParts.at(ifIndex - 1);
    }
    else if(parts.at(index) == ELSEIF)
    {
        int ifElseIndex = 0;
        for (int i = 0; i <= index && i < parts.size(); i++)
            if (parts.at(i) == ELSEIF)
                ifElseIndex++;
        ret = &ifElseParts.at(ifElseIndex - 1);
    }
    else if(parts.at(index) == ELSE)
    {
        int elseIndex = 0;
        for (int i = 0; i <= index && i < parts.size(); i++)
            if (parts.at(i) == ELSE)
                elseIndex++;
        ret = &elseParts.at(elseIndex - 1);
    }
    else if(parts.at(index) == GOTO)
    {
        int gotoIndex = 0;
        for (int i = 0; i <= index && i < parts.size(); i++)
            if (parts.at(i) == GOTO)
                gotoIndex++;
        ret = &gotoParts.at(gotoIndex - 1);
    }
    else if(parts.at(index) == LINK)
    {
        int linkIndex = 0;
        for (int i = 0; i <= index && i < parts.size(); i++)
            if (parts.at(i) == LINK)
                linkIndex++;
        ret = &linkParts.at(linkIndex - 1);
    }
    else if(parts.at(index) == BLOCK)
    {
        int blockIndex = 0;
        for (int i = 0; i <= index && i < parts.size(); i++)
            if (parts.at(i) == BLOCK)
                blockIndex++;
        ret = &blockParts.at(blockIndex - 1);
    }
    else if(parts.at(index) == TEXT)
    {
        int textIndex = 0;
        for (int i = 0; i <= index && i < parts.size(); i++)
            if (parts.at(i) == TEXT)
                textIndex++;
        ret = &textParts.at(textIndex - 1);
    }
    else if(parts.at(index) == UNDEFINED)
    {
        //cout << "looping undefined" << endl;
        int undefinedIndex = 0;
        for (int i = 0; i <= index && i < parts.size(); i++)
            if (parts.at(i) == UNDEFINED)
                undefinedIndex++;
        ret = &undefinedParts.at(undefinedIndex - 1);
    }
    else
    {
        cout << "Something went wrong." << endl;
        PartToken broken = PartToken("", TEXT);
        ret = &broken;
    }
    return ret;

}

int PassageTokenizer::getNumParts() const
{
    return parts.size();
}