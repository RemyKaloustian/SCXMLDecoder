#include "CodeSwitch.h"




CodeSwitch::CodeSwitch(string target, vector<MachineState> states):_target(target), _states(states)
{
}

CodeSwitch::~CodeSwitch()
{
}



string CodeSwitch::to_string()
{
	return "switch";
}
