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

void WriteInFile(string file, string content)
{
	myfile.open(file, std::ios_base::app);
	myfile << content;
	myfile.close();
}

void WriteFunction(string return_t, string name, string body)
{
	WriteInFile(fn,"\n"+ return_t);
	WriteInFile(fn, " " + name + "()\n{\n");
	WriteInFile(fn, "\t" + body);
	WriteInFile(fn, "\n}");

}

void WriteArgs(vector<Argument> args)
{
	//Writes the arguments
}




int main()
{
	xml_document<> doc;
	xml_node<> * root_node;

	vector<std::string> state_list;
	vector<std::string> event_list;

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

	//getting the initial state

	initial = root_node->first_attribute("initial")->value();

	//getting teh final state
	final = root_node->first_node("final")->first_attribute("id")->value();


	//Displaying the states
	for (string s : state_list) {
		cout << s << "\n";
	}

	cout << "The initial state is " << initial <<"\n";
	cout << "The final state is  " << final<<"\n";

	WriteInFile(fn, "Ignorage");
	WriteInFile(fn, "#include <iostream> \n\n");


	WriteInFile(fn, "enum State{ ");

	for each (string state in state_list)
	{
		WriteInFile(fn, state);
	}
	WriteInFile(fn, "};\n\n");

	WriteFunction("int", "main", "cout<<hello peasants \n");



	


}

