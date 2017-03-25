#include "CodeSwitch.h"

CodeSwitch::CodeSwitch(string target, vector<MachineState> states):_target(target), _states(states)
{
}

CodeSwitch::~CodeSwitch()
{
}

//puts the sitch content in string form
string CodeSwitch::to_string()
{
	string switch_content = "";

	switch_content += "switch(currentState){ \n";

		for (MachineState s : _states)
		{
			switch_content += "\t case " + s._name + ":\n";

			//for each next state			
			for(string next : s._nextList)
				if (next.find("Final") == string::npos)//If the next state is the not the final point
				{
					switch_content += "\t\t if (newState == " + next + "){\n";
					switch_content += "\t\t\t std::cout<<\"enter  " + next + "\"<<std::endl;\n" +
						"\t\t\t In" + next + "();\n" +
						"\t\t \t currentState = " + next + ";\n" +
						"\t\t}\n";
				}

			switch_content += "\t\t\n\t\tbreak;\n";
		}
		switch_content += "\t}\n";
		
	return switch_content;
}//to_string()
