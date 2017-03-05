#pragma once
#include<string>
#include <vector>

#include "CodeCase.h"
#include "MachineState.h"


using std::string;
using std::vector;

class CodeSwitch
{
public:

	string _target;
	vector<MachineState> _states;
	CodeSwitch(string target, vector<MachineState> states);
	~CodeSwitch();

	string to_string();
};

