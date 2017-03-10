#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <istream>
#include <fstream>

#include "Argument.h"
#include "MachineState.h"

using std::string;
using std::vector;

class CodeGenerator
{


public:

	string _content;
	
	CodeGenerator(string fileToParse);
	~CodeGenerator();

	void WriteInFile(string content);
	
	void WriteFunction(string name, string body, string return_t = "void", const vector<Argument> arguments = vector<Argument>());
	
	void WriteEnum(string name, vector<string> values);

	void WriteInitialization(string varname, string value, bool newline, string type = "");
	
	vector<string> get_states_names(vector<MachineState> states);
	

};

