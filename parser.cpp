/*
 * Parser class implementation
 */

#include <cctype> 
#include "parser.h"

extern unsigned line;

Parser::Parser(std::ifstream& _inputFile) : inputFile(_inputFile)
{
}

Parser::~Parser()
{
}

// returns whether there are more instructions in the input
bool Parser::HasMoreCommands()
{
	std::getline(inputFile, curInstr);
	line++;
	return !inputFile.eof();
}

bool Parser::Advance()
{
	while (curInstr == "    " || curInstr == "\t" || curInstr == "" || curInstr[0] == '/')
	{
		std::getline(inputFile, curInstr);
		line++;
		if (inputFile.eof())
		    return false;
	}
	return true;
}

CmdType Parser::CommandType()
{
	size_t pos;

	// parse each instruction:
	// <hasm program> ::= <instruction>+
	// <instruction> ::= <A-instruction> | <D-instruction> | <L-instruction> | <comment>
	// <A-instruction> ::= @<symbol>
	// <D-instruction> ::= [<dest>=]<comp>[;<jump>]
	// <L-instruction> ::= (<symbol>)
	// <comment> ::= //<any text>

	// strip off whitespace and in-line comments
	if ((pos = curInstr.find_first_not_of(' ')) != std::string::npos)
	{
		curInstr = curInstr.substr(pos);
	}
	if ((pos = curInstr.find_first_of(" \t")) != std::string::npos)
	{
		curInstr = curInstr.substr(0, pos);
	}

	symbol.clear();
	if ((pos = curInstr.find("@")) != std::string::npos)
	{
		// A-instruction so parse the symbol
		symbol = curInstr.substr(pos+1);

		curInstr.clear();
		return A_COMMAND;
	}
	else if ((pos = curInstr.find("(")) != std::string::npos)
	{
		// L-instruction so parse the symbol
		curInstr.erase(0, pos + 1);
		if ((pos = curInstr.find(')')) != std::string::npos)
		{
			symbol = curInstr.substr(0, pos);
		}

		curInstr.clear();
		return L_COMMAND;
	}
	else
	{
		// D-instruction so parse as: [<dest>=]<comp>[;<jump>]

		// parse the optional dest
		dest = "";
		if ((pos = curInstr.find('=')) != std::string::npos)
		{
			dest = curInstr.substr(0, pos);
			curInstr.erase(0, pos+1);
		}

		// parse the comp
		jump = "";
		if ((pos = curInstr.find(';')) != std::string::npos)
		{
			comp = curInstr.substr(0, pos);

			// parse the optional jump
			jump = curInstr.substr(pos+1);
		}
		else
		{
			comp = curInstr;
		}

		curInstr.clear();
		return C_COMMAND;
	}
}
