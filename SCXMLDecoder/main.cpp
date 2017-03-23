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

	CodeGenerator ACG("AdvancedExample.scxml", "generated_advanced");
	string advanced_content = ACG._content;
	ofstream outputFileAdvanced;
	outputFileAdvanced.open("generated_advanced.h");
	outputFileAdvanced << advanced_content;
	outputFileAdvanced.close();

	string advanced_main_content = ACG._main_content;
	cout << advanced_main_content;
	ofstream outputFileMainAd;
	outputFileMainAd.open("main_advanced.cpp");
	outputFileMainAd << advanced_main_content;
	outputFileMainAd.close();

	//cout << advanced_content;

	return 0;
}

