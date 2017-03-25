#pragma once
#include<string>
#include <vector>

#include "MachineState.h"


using std::string;
using std::vector;

//A code generator for switch case, directly used by the CodeGenerator (we thus break responsibilities)
class CodeSwitch
{
public:

	string _target; //What we're doing the switch on
	vector<MachineState> _states; //all the cases
	CodeSwitch(string target, vector<MachineState> states);
	~CodeSwitch();

	string to_string();
};

