#pragma once

#include <string>

using std::string;
class Argument
{
public:
	string _type;
	string _name;
	Argument(string type,string name);
	~Argument();
};

