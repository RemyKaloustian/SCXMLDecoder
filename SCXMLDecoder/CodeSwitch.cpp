#include "CodeSwitch.h"




CodeSwitch::CodeSwitch(string target, vector<MachineState> states):_target(target), _states(states)
{
}

CodeSwitch::~CodeSwitch()
{
}



string CodeSwitch::to_string()
{
	string switch_content = "";

	switch_content += "switch(newState){ \n";

		for (MachineState s : _states)
		{
			if(s._next.find("Final") == string::npos)
			switch_content += "\t case " + s._name + ":\n" +
				"\t\t if (newState == " + s._next + "){\n"
				+ "\t\t\t In" + s._next + "();\n" +
				"\t\t \t currentState = " + s._next + ";\n" +
				"\t\t\t std::cout<<\"enter  " + s._next + "\"<<std::endl;\n" +
				"\t\t}\n\t\tbreak;\n" +
				"\t}\n";
				
			
		}
		


	return switch_content;
}