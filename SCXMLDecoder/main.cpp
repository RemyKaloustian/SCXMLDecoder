#include <iostream>
#include <string>
#include <vector>
#include <istream>
#include <fstream>
#include <unistd.h>
#include <sys/stat.h>

#include "CodeGenerator.h"

#include "rapidxml/rapidxml.hpp"



using namespace rapidxml;
using namespace std;


int main()
{
	mkdir("Result", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);	//Generating code from basic example
	CodeGenerator CG("BasicExample.scxml", "generated_basic.h", "Result/main_basic.cpp");
	//Generating code from Advanced example (with delay)
	CodeGenerator ACG("AdvancedExample.scxml", "generated_advanced.h", "Result/main_advanced.cpp");

	return 0;
}
