#ifndef __IF_INTERPRETER__
#define __IF_INTERPRETER__

#include <string>
#include <unordered_map>
#include "passagetoken.h"
#include "parttoken.h"
#include <vector>


class IFInterpreter{
private:
	std::string story;
	std::unordered_map<std::string, bool> variables;
	//shoudn't have to make PassageToken pointers like with PartToken since there's only one type/no subclasses
	//I think
	std::unordered_map<std::string, PassageToken> uMapPassages;
	vector<PassageToken> passages;
	bool keepLooping;
	vector<Link*> links;


public:
	IFInterpreter(std::string fileName);
	void play();
	void print();
	void interpretPassage(PassageToken passage);
	void updateVariables(unordered_map<string, bool> var);
	void determineIf(PartToken* block);
};


#endif