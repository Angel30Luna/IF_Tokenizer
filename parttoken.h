//Project 2
#ifndef _PART_TOKEN_H
#define _PART_TOKEN_H

#include <string>
#include <iostream>
#include <vector>
using namespace std;

enum part_t {LINK, SET, GOTO, IF, ELSEIF, ELSE, BLOCK, TEXT, UNDEFINED}; //undefined type for testing. Get rid of later

class PartToken
{
private:
    string partText;
    part_t partType;

public:
    PartToken();
    PartToken(string, part_t);
    part_t getType() const {return partType; }
    string getText() const {return partText; }
    void setType(part_t);
    void setText(string);
    virtual void print() const;

};


class Set : public PartToken{
	private:
		std::string name;
		bool value;

	public:
		Set(string text);
		virtual void print() const override;
		string getName() {return name;};
		bool getValue() {return value;};
};

class Block : public PartToken{
    private:
        string text;
	vector<PartToken*> parts;
    public:
        Block(string text);
        virtual void print() const override;
        string getText() {return text;};
        PartToken* get(int index);
        int getNumParts() {return parts.size();};
};

class GoTo : public PartToken{
    private:
        string name;
    public:
        GoTo(string text);
        virtual void print() const override;
        string getName() { return name;};
};

class ElsePart : public PartToken{
    public:
        ElsePart();
        virtual void print() const override;
};

class IfElse : public PartToken{
    private:
        string testName;
        bool testValue;
    public:
        IfElse(string text);
        virtual void print() const override;
        string getName(){ return testName;};
        bool getvalue() { return testValue;};
};

class IfPart : public PartToken{
    private:
        string testName;
        bool testValue;
    public:
        IfPart(string text);
        virtual void print() const override;
        string getName() { return testName;};
        bool getvalue() { return testValue;};
};

class Link : public PartToken{
    private:
        string display;
        string passageName;
    public:
        Link(string text);
        virtual void print() const override;
        string getPassageName() { return passageName;};
        string getDisplay() { return display;};
};

class Text : public PartToken{
    private:
        string text;
    public:
        Text(string text);
        virtual void print() const override;
        string getText() { return text;};
};


#endif