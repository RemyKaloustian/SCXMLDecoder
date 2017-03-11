#include "MachineState.h"
#include <vector>
using std::vector;




MachineState::MachineState(string name, vector<string> next, string action, string delay):_name(name), _action(action), _delay(delay)
{
	_nextList = next;
}

MachineState::~MachineState()
{
}
