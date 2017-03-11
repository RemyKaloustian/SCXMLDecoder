

#include<iostream>


#include "CodeGenerator.h"
#include "CodeSwitch.h"

#include "rapidxml\rapidxml.hpp"



using namespace rapidxml;
using namespace std;

CodeGenerator::CodeGenerator(string fileToParse)
{

	xml_document<> doc;
	xml_node<> * root_node;

	vector<std::string> state_list;
	vector<std::string> event_list;
	vector<string> actions_list;

	vector<MachineState> states;

	string initial;
	string final;

	ifstream theFile(fileToParse);
	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');

	doc.parse<0>(&buffer[0]);
	root_node = doc.first_node("scxml");

#pragma endregion DECLARATIONS


#pragma region DATASEARCH
	//Getting the states
	for (xml_node<> * tmp_node = root_node->first_node("state"); tmp_node; tmp_node = tmp_node->next_sibling()) 
	{
		//state_list.push_back(tmp_node->first_attribute("id")->value());
		string id = tmp_node->first_attribute("id")->value();

		vector<string> nextList;

		for (xml_node<> * trans_node = tmp_node->first_node("transition"); trans_node; trans_node = trans_node->next_sibling()) 
		{
			if (trans_node->first_attribute("target") != nullptr)
			{
				nextList.push_back(trans_node->first_attribute("target")->value());
				cout << "id =" << id << "  , The target is  " << trans_node->first_attribute("target")->value();
			}
			
		}
		//string next = tmp_node->first_node("transition")->first_attribute("target")->value();
		string action = tmp_node->first_node("onentry")->first_node("send")->first_attribute("event")->value();
		string delay;
		if (tmp_node->first_node("onentry")->first_node("send")->first_attribute("delay") != nullptr)
		{
			 delay = tmp_node->first_node("onentry")->first_node("send")->first_attribute("delay")->value();
			 states.push_back(MachineState(id, nextList, action, delay));

			 cout << "\nCreating a state with \n " << id << "\n action = " << action << "\n nextlist : ";
			 for (string n : nextList)
			 {
				 cout << n << ", ";
			 }


		}
		else
		{
			states.push_back(MachineState(id, nextList, action));

			cout << "\nCreating a state with \n " << id << "\n action = " << action << "\n nextlist : ";
			for (string n : nextList)
			{
				cout << n << ", ";
			}
		}

	}

	/*for (xml_node<> * tmp_node = root_node->first_node("state"); tmp_node; tmp_node = tmp_node->next_sibling()) {
	actions_list.push_back(tmp_node->first_node("onentry")->first_node("send")->first_attribute("event")->value());
	}*/

	//getting the initial state

	initial = root_node->first_attribute("initial")->value();

	//getting teh final state
	//final = root_node->first_node("final")->first_attribute("id")->value();

#pragma endregion DATASEARCH



	WriteIncludes(states);

	WriteEnum("State", get_states_names(states));
	for (unsigned i = 0; i < states.size(); ++i)
	{
		//Use codeline, function use a list of codelines
		WriteFunction("In" + states[i]._name, "cout<<\" " + states[i]._action + "\" << \"\\n\";\n");
	}

	WriteInitialization("currentState", initial, true, "State");


	//USEFUL ????
	vector<Argument> activateArgs;
	activateArgs.push_back(Argument("State", "newState"));

	CodeSwitch activateSwitch("currentState", states);
	WriteFunction("activate", activateSwitch.to_string(), "int", activateArgs);

	string main_content= "";

	for (MachineState s : states)
	{
		for (string next : s._nextList)
		{
			main_content += "activate(" + next + ");\n\t";
		}
	}

	WriteFunction("main", main_content, "int");

}


CodeGenerator::~CodeGenerator()
{}


void CodeGenerator::WriteInFile( string content)
{
	/*myfile.open(fn, std::ios_base::app);
	myfile << content;
	myfile.close();*/

	_content += content;
}

void CodeGenerator::WriteIncludes(vector<MachineState> states)
{
	WriteInFile("#include <iostream> \n");
	bool hasDelay = false;
	for (MachineState s : states)
	{
		if (s._delay != "")
			hasDelay = true;
	}

	if (hasDelay)
	{
		WriteInFile("#include <chrono> //c++ 11\n");
		WriteInFile("#include <thread> //c++ 11\n");
	}

	WriteInFile("using  namespace std; \n\n");
}

void CodeGenerator::WriteFunction( string name, string body, string return_t , const vector<Argument> arguments)
{
	WriteInFile("\n"+ return_t);
	WriteInFile(" " + name + "(");

	if (arguments.size() > 0)
	{
		for (size_t i = 0; i < arguments.size() - 1; i++)
		{
			WriteInFile(arguments[i]._type + " " + arguments[i]._name + ", ");
		}
		WriteInFile(arguments[arguments.size() - 1]._type + " " + arguments[arguments.size() - 1]._name);

	}
	
	WriteInFile(")\n{ \n");
	WriteInFile( "\t" + body);
	WriteInFile( "\n}\n\n");
}



void CodeGenerator::WriteEnum(string name, vector<string> values)
{
	WriteInFile( "enum State{ ");

	for(unsigned i = 0; i< values.size() -1; ++i)
	{
		WriteInFile( values[i] + ", ");
	}
	WriteInFile( values[values.size()-1]);

	WriteInFile( "};\n\n");
}

void CodeGenerator::WriteInitialization(string varname, string value, bool newline, string type)
{
	if(newline)
		WriteInFile(type + " " + varname + " = " + value + ";\n");
	else
		WriteInFile(type + " " + varname + " = " + value + ";");

}

vector<string> CodeGenerator::get_states_names(vector<MachineState> states)
{
	vector<string> names;

	for (MachineState s : states)
	{
		names.push_back(s._name);
	}

	return names;
}

