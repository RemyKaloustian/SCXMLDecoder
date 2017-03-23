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

	switch_content += "switch(currentState){ \n";

		for (MachineState s : _states)
		{
			switch_content += "\t case " + s._name + ":\n";

			//for each next
			//If the next state is the not the final point
			for(string next : s._nextList)
			if (next.find("Final") == string::npos)
			{
				
				//switch_content += "\t case " + s._name + ":\n" +
					switch_content+="\t\t if (newState == " + next + "){\n";

				if (s._delay != "")
				{
					switch_content += "\t\t\t sleep_for(seconds(" + s._delay + "));\n";
				}



				switch_content += "\t\t\t std::cout<<\"enter  " + next + "\"<<std::endl;\n" + 
					"\t\t\t In" + next + "();\n" +
					"\t\t \t currentState = " + next + ";\n" +	
					"\t\t}\n";
			}

			switch_content += "\t\t\n\t\tbreak;\n";
		}
		switch_content += "\t}\n";
		


	return switch_content;
}
