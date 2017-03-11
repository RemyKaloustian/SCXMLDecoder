#include <iostream>
#include <string>
#include <vector>
#include <istream>
#include <fstream>

#include "CodeGenerator.h"

#include "rapidxml\rapidxml.hpp"



using namespace rapidxml;
using namespace std;


int main()
{

	string basic_content = CodeGenerator("BasicExample.scxml")._content;
	cout << basic_content;

	ofstream outputFile;
	outputFile.open("generated_basic.cpp");
	outputFile << basic_content;
	outputFile.close();

	string advanced_content = CodeGenerator("AdvancedExample.scxml")._content;
	ofstream outputFileAdvanced;
	outputFileAdvanced.open("generated_advanced.cpp");
	outputFileAdvanced << advanced_content;
	outputFileAdvanced.close();

	return 0;
}

