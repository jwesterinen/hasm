/*
 * Parser class definition
 */

#pragma once

#include <iostream>
#include <fstream>
#include <string>

enum CmdType{A_COMMAND, C_COMMAND, L_COMMAND};

class Parser
{
public:
	Parser(std::ifstream& _inputFile);
	~Parser();
	bool HasMoreCommands();
	bool Advance();
	CmdType CommandType();
	const std::string& Symbol()
	{
		return symbol;
	}
	const std::string& Dest()
	{
		return dest;
	}
	const std::string& Comp()
	{
		return comp;
	}
	const std::string& Jump()
	{
		return jump;
	}

private:
	std::ifstream& inputFile;
	std::string curInstr;
	std::string symbol, dest, comp, jump;
};
