#include<iostream>

#include "CodeGenerator.h"
#include "CodeSwitch.h"

#include "rapidxml/rapidxml.hpp"

using namespace rapidxml;
using namespace std;

CodeGenerator::CodeGenerator(string fileToParse, string generated, string main):_generated(generated), _main(main)
{

#pragma region PARSING_VARIABLES
	xml_document<> doc; //the scxml document
	xml_node<> * root_node; //the root node of the document

	vector<std::string> state_list;
	vector<std::string> event_list;
	vector<string> actions_list;

	//I have a states list with MachineState because it is easier to manipulate in order to generate code
	vector<MachineState> states;

	string initial;
	string final;
#pragma endregion


	//We use iterators and black magic to go through the file
	ifstream theFile(fileToParse);
	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');

	doc.parse<0>(&buffer[0]);
	root_node = doc.first_node("scxml");




#pragma region DATASEARCH
	//Getting the states
	for (xml_node<> * tmp_node = root_node->first_node("state"); tmp_node; tmp_node = tmp_node->next_sibling())
	{
		//getting teh name of the state
		string id = tmp_node->first_attribute("id")->value();
		vector<string> nextList;

		for (xml_node<> * trans_node = tmp_node->first_node("transition"); trans_node; trans_node = trans_node->next_sibling())
		{
			//getting the states the current state can go to
			if (trans_node->first_attribute("target") != nullptr)
			{
				nextList.push_back(trans_node->first_attribute("target")->value());
			}
		}
		//getting the function executed when in the state
		string action = tmp_node->first_node("onentry")->first_node("send")->first_attribute("event")->value();
		string delay;
		//getting the delay (if there is one)
		if (tmp_node->first_node("onentry")->first_node("send")->first_attribute("delay") != nullptr)
		{
			 delay = tmp_node->first_node("onentry")->first_node("send")->first_attribute("delay")->value();
			 states.push_back(MachineState(id, nextList, action, delay));
		}
		else
		{
			states.push_back(MachineState(id, nextList, action));
		}

	}


	//getting the initial state
	initial = root_node->first_attribute("initial")->value();

	//getting the final state (for the moment, just in case)
	final = root_node->first_node("final")->first_attribute("id")->value();

#pragma endregion DATASEARCH

#pragma region CODE_WRITING

	//WRITING IN THE GENERATED FILE

	WriteIncludes(states,_content);
	WriteEnum("State",_content, get_states_names(states));

	//Writing the transition function for each state
	for (unsigned i = 0; i < states.size(); ++i)
	{
		cout << "\nWritting function " << states[i]._name, _content;
		if (states[i]._delay != "")
		{
			WriteFunction("In" + states[i]._name, "sleep_for(seconds("+ states[i]._delay + "));\n  \tcout<<\" " + states[i]._action + "\" << \"\\n\";\n", _content);
		}

		else
		{
			WriteFunction("In" + states[i]._name, "cout<<\" " + states[i]._action + "\" << \"\\n\";\n", _content);

		}
	}

	//Setting the initial state
	WriteInitialization("currentState", initial, true,_content, "State");


	//Argument for the code switch
	vector<Argument> activateArgs;
	activateArgs.push_back(Argument("State", "newState"));
	//Creating the activate() function and writing it
	CodeSwitch activateSwitch("currentState", states);
	WriteFunction("activate", activateSwitch.to_string(),_content, "int", activateArgs);



	//WRITING THE MAIN

	string main_content= "";
	Write("#include <iostream> //c++ 11\n", _main_content);
	Write("#include <chrono> //c++ 11\n", _main_content);
	Write("#include <thread> //c++ 11\n", _main_content);
	Write("#include  \"" +_generated + "\" \n", _main_content);

	Write("\nusing std::chrono::seconds;\n", _main_content);
	Write("using std::this_thread::sleep_for;\n", _main_content);

	Write("using  namespace std; \n\n", _main_content);

	for (MachineState s : states)
	{
		if(states.size() > 2)
		{
			string state3 = states.at(2);
			states[2] = states[0];
			states[0] = state3;
		}
		for (string next : s._nextList)
		{
			cout << "\nactivating " << next;
			main_content += "activate(" + next + ");\n\t";
		}
	}

	WriteFunction("main", main_content,_main_content, "int");

	//Writing in the files
	PutInFile(_content, _generated);
	PutInFile(_main_content, _main);

#pragma endregion CODE_WRITING
}


CodeGenerator::~CodeGenerator()
{}


void CodeGenerator::Write( string content, string & target)
{
	target += content;
}

void CodeGenerator::WriteIncludes(vector<MachineState> states, string& target)
{
	Write("#pragma once \n#include <iostream> \n",target);
	bool hasDelay = false;
	for (MachineState s : states)
	{
		if (s._delay != "")
			hasDelay = true;
	}

	if (hasDelay) //the use of sleep_for(seconds()) requires all this stuff
	{
		Write("#include <chrono> //c++ 11\n",target);
		Write("#include <thread> //c++ 11\n",target);
		Write("\nusing std::chrono::seconds;\n",target);
		Write("using std::this_thread::sleep_for;\n",target);
	}

	Write("using  namespace std; \n\n",target);
}//WriteIncludes()

void CodeGenerator::WriteFunction( string name, string body,string& target, string return_t , const vector<Argument> arguments)
{
	//Writing the signature
	Write("\n"+ return_t,target);
	Write(" " + name + "(",target);

	if (arguments.size() > 0)
	{
		//Writing the arguments
		for (size_t i = 0; i < arguments.size() - 1; i++)
		{
			Write(arguments[i]._type + " " + arguments[i]._name + ", ",target);
		}
		Write(arguments[arguments.size() - 1]._type + " " + arguments[arguments.size() - 1]._name,target);

	}

	//Writing the body
	Write(")\n{ \n",target);
	Write( "\t" + body,target);
	Write( "\n}\n\n",target);
}//WriteFunction()



void CodeGenerator::WriteEnum(string name,string& target, vector<string> values)
{
	//Now, we just use an enum State, for further improvement, we should pass "State" in parameter
	Write( "enum State{ ", target);

	for(unsigned i = 0; i< values.size() -1; ++i)
	{
		Write( values[i] + "= " + to_string(i)+", ",target);
	}
	Write( values[values.size()-1] + "= " + to_string(values.size()-1),target);

	Write( "};\n\n",target);
}//WriteEnum()

void CodeGenerator::WriteInitialization(string varname, string value, bool newline,string& target, string type)
{
	if(newline)
		Write(type + " " + varname + " = " + value + ";\n",target);
	else
		Write(type + " " + varname + " = " + value + ";",target);

}//WriteInitialization()

//used for the State enum
vector<string> CodeGenerator::get_states_names(vector<MachineState> states)
{
	vector<string> names;

	for (MachineState s : states)
	{
		names.push_back(s._name);
	}

	return names;
}//get_states_names

void CodeGenerator::PutInFile(string content, string fileName)
{
	//Write the content in the file
	ofstream outputFile;
	outputFile.open("Result/"+fileName);
	outputFile << content;
	outputFile.close();
}
