#pragma once

#include <string>

using std::string;

class MachineState
{
public:
	string _name;
	string _next;
	string _action;
	MachineState(string name, string next, string action);
	~MachineState();
};

