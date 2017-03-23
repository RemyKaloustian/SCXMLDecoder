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
	string _main_content;
	string _generated;
	string _main;
	
	CodeGenerator(string fileToParse, string generated, string main);
	~CodeGenerator();

	void WriteInFile(string content, string & target);

	void WriteIncludes(vector<MachineState>, string& target);
	
	void WriteFunction(string name, string body,string& target, string return_t = "void", const vector<Argument> arguments = vector<Argument>());
	
	void WriteEnum(string name,string& target, vector<string> values);

	void WriteInitialization(string varname, string value, bool newline,string& target, string type = "");
	
	vector<string> get_states_names(vector<MachineState> states);

	void PutInFile(string content, string fileName);
	

};

