#include <iostream>
#include <string>
#include <vector>
#include <istream>
#include <fstream>

#include "Argument.h"
#include "CodeSwitch.h"
#include "MachineState.h"	

#include "rapidxml\rapidxml.hpp"


using std::cout;
using std::string;
using std::vector;
using std::ifstream;
using namespace rapidxml;
using namespace std;

string fn = "generated.cpp";
ofstream myfile(fn);

void WriteInFile( string content)
{
	myfile.open(fn, std::ios_base::app);
	myfile << content;
	myfile.close();
}

void WriteFunction( string name, string body, string return_t = "void", const vector<Argument> arguments = vector<Argument>() )
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



void WriteEnum(string name, vector<string> values)
{
	WriteInFile( "enum State{ ");

	for(unsigned i = 0; i< values.size() -1; ++i)
	{
		WriteInFile( values[i] + ", ");
	}
	WriteInFile( values[values.size()-1]);

	WriteInFile( "};\n\n");
}

void WriteInitialization(string varname, string value, string type = "")
{
	WriteInFile(type + " " + varname + " = " + value + ";");
}

vector<string> get_states_names(vector<MachineState> states)
{
	vector<string> names;

	for (MachineState s : states)
	{
		names.push_back(s._name);
	}

	return names;
}




int main()
{

#pragma region DECLARATIONS
	xml_document<> doc;
	xml_node<> * root_node;

	vector<std::string> state_list;
	vector<std::string> event_list;
	vector<string> actions_list;

	vector<MachineState> states;

	string initial;
	string final;

	ifstream theFile("BasicExample.scxml");
	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');

	doc.parse<0>(&buffer[0]);
	root_node = doc.first_node("scxml");

#pragma endregion DECLARATIONS
	

#pragma region DATASEARCH
	//Getting the states
	for (xml_node<> * tmp_node = root_node->first_node("state"); tmp_node; tmp_node = tmp_node->next_sibling()) {
		//state_list.push_back(tmp_node->first_attribute("id")->value());
		string id = tmp_node->first_attribute("id")->value();
		string next = tmp_node->first_node("transition")->first_attribute("target")->value();
		string action = tmp_node->first_node("onentry")->first_node("send")->first_attribute("event")->value();

		states.push_back(MachineState(id, next, action));

		cout << "\n Would create a state with : name = " << id << " || next = " << next << "  ||  action = " << action << "\n";

	}

	/*for (xml_node<> * tmp_node = root_node->first_node("state"); tmp_node; tmp_node = tmp_node->next_sibling()) {
		actions_list.push_back(tmp_node->first_node("onentry")->first_node("send")->first_attribute("event")->value());
	}*/

	//getting the initial state

	initial = root_node->first_attribute("initial")->value();

	//getting teh final state
	final = root_node->first_node("final")->first_attribute("id")->value();

#pragma endregion DATASEARCH
	
	WriteInFile( "Ignorage");


	///VALIDATED
	WriteInFile( "#include <iostream> \n\n");

	
	WriteEnum("State", get_states_names(states));
	for (unsigned i = 0; i < states.size() ; ++i)
	{
		//Use codeline, function use a list of codelines
		WriteFunction(states[i]._action, "cout<<\" " + states[i]._action + "\" << \"\\n\";\n");
	}

	WriteInitialization("currentState", initial, "State");

	vector<Argument> activateArgs;
	activateArgs.push_back(Argument("State", "newState"));


	vector<CodeCase> caseList;
	
	CodeSwitch activateSwitch("currentState",states);
	WriteFunction("activate",activateSwitch.to_string(),"int",activateArgs);



	WriteFunction("main", "cout << \"Hello peasants\\n \";","int");



}

