#pragma once

#include <string>

using std::string;

class CodeLine
{
public:
	unsigned _depth;
	string _body;
	CodeLine(unsigned depth, string body);
	~CodeLine();
};

