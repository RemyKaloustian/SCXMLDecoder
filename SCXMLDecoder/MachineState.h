#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

class MachineState
{
public:
	string _name;
	vector<string> _nextList;
	string _action;
	string _delay;
	MachineState(string name, vector<string> next, string action, string delay = "");
	~MachineState();
};

