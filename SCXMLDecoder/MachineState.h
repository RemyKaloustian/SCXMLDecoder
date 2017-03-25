#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

//We get the states from the scxml file and put them in this object form, for easier code generating
class MachineState
{
public:
	string _name; //name of the state
	vector<string> _nextList; //all the states it can go to
	string _action; //the function executed when in the state
	string _delay; //optional delay when enetring the state
	MachineState(string name, vector<string> next, string action, string delay = "");
	~MachineState();
};

