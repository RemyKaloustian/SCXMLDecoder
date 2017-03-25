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
	//Generating code from basic example
	CodeGenerator CG("BasicExample.scxml", "generated_basic.h", "main_basic.cpp");
	//Generating code from Advanced example (with delay)
	CodeGenerator ACG("AdvancedExample.scxml", "generated_advanced.h", "main_advanced.cpp");	

	return 0;
}

