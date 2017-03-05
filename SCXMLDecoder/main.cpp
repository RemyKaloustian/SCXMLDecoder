#include <iostream>
#include <string>
#include <vector>
#include <istream>
#include <fstream>

#include "Argument.h"

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



void WriteArgs(vector<Argument> args)
{
	//Writes the arguments
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




int main()
{
	xml_document<> doc;
	xml_node<> * root_node;

	vector<std::string> state_list;
	vector<std::string> event_list;
	vector<string> actions_list;

	string initial;
	string final;

	ifstream theFile("BasicExample.scxml");
	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');

	doc.parse<0>(&buffer[0]);
	root_node = doc.first_node("scxml");
	
	//Getting the states
	for (xml_node<> * tmp_node = root_node->first_node("state"); tmp_node; tmp_node = tmp_node->next_sibling()) {
		state_list.push_back(tmp_node->first_attribute("id")->value());
	}

	for (xml_node<> * tmp_node = root_node->first_node("state"); tmp_node; tmp_node = tmp_node->next_sibling()) {
		actions_list.push_back(tmp_node->first_node("onentry")->first_node("send")->first_attribute("event")->value());
	}

	//getting the initial state

	initial = root_node->first_attribute("initial")->value();

	//getting teh final state
	final = root_node->first_node("final")->first_attribute("id")->value();


	//Displaying the states
	for (string s : state_list) {
		cout << s << "\n";
	}

	//Displaying the actions

	for (string s : actions_list)
	{
		cout << s << "\n";
	}

	/*cout << "The initial state is " << initial <<"\n";
	cout << "The final state is  " << final<<"\n";
*/
	WriteInFile( "Ignorage");


	///VALIDATED
	WriteInFile( "#include <iostream> \n\n");
	WriteEnum("State", state_list);
	for (string s : actions_list)
	{
		///Use codeline, function use a list of codelines
		WriteFunction(s, "cout<<\" " + s + "\" << \"\\n\";\n");
	}

	WriteInitialization("currentState", initial, "State");

	vector<Argument> activateArgs;
	activateArgs.push_back(Argument("State", "newState"));
	WriteFunction("activate","bla","int",activateArgs);

	WriteFunction("main", "cout << \"Hello peasants\\n \";","int");



	


}

