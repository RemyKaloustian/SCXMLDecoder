#pragma once

#include <string>

using std::string;

class MachineState
{
public:
	string _name;
	string _next;
	string _action;
	string _delay;
	MachineState(string name, string next, string action, string delay = "");
	~MachineState();
};

