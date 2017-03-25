#pragma once

#include <string>

using std::string;

//Represents a function argument, handy because a function generator takes a vector of arguments
class Argument
{
public:
	string _type;
	string _name;
	Argument(string type,string name);
	~Argument();
};

