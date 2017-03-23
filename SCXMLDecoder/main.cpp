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

	CodeGenerator CG("BasicExample.scxml", "generated_basic.h");
	string basic_content = CG._content;
	//cout << basic_content;

	string main_content = CG._main_content;

	ofstream outputFile;
	outputFile.open("generated_basic.h");
	outputFile << basic_content;
	outputFile.close();

	ofstream outputFileMain;
	outputFileMain.open("main_basic.cpp");
	outputFileMain << main_content;
	outputFileMain.close();

	cout << "\n\n ----------------------------------------------------\n\n";

	string advanced_content = CodeGenerator("AdvancedExample.scxml","generated_advanced")._content;
	ofstream outputFileAdvanced;
	outputFileAdvanced.open("generated_advanced.h");
	outputFileAdvanced << advanced_content;
	outputFileAdvanced.close();

	//cout << advanced_content;

	return 0;
}

