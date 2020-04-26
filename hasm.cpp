/*
 * Main control module for the HACK assembler
 */

#include <iostream>
#include <fstream>
#include <string>
#include "parser.h"
#include "code.h"
#include "symbolTable.h"

// global input file name and line number for error reporting
char *inputFileName;
unsigned line;

// return true if a string represents a number, else return false
bool IsNumber(const std::string& s)
{
	// check for an actual zero numeral
	if (s == "0")
		return true;

	// if the string can be converted return true
	char* p;
	strtol(s.c_str(), &p, 10);
	return *p == 0;
}

int main(int argc, char** argv)
{
	if (argc < 2)
		return 1;

	// open the input file
	inputFileName = argv[1];
	std::ifstream inputFile(inputFileName);
	if (!inputFile.is_open())
	{
		std::cout << "hasm: cannot open file " << argv[1] << std::endl;
	}

	// create the output file
	size_t pos = 0;
	std::string delimiter(".");
	std::string outfileName(argv[1]);
	if ((pos = outfileName.find_last_of(delimiter)) != std::string::npos)
	{
		outfileName = outfileName.substr(0, pos) + ".hack";
	}
	std::ofstream outputFile(outfileName);

	// init the parser and code generator
	Parser parser(inputFile);
	Code code;
	SymbolTable symbolTable;

	// first pass -- create the symbol table
	std::string symbol;
	int romAddr = 0;
	int ramAddr = 16;
	line = 0;
	while (parser.HasMoreCommands() && parser.Advance())
	{
		switch (parser.CommandType())
		{
			case A_COMMAND:
				romAddr++;
				break;

			case C_COMMAND:
				romAddr++;
				break;

			case L_COMMAND:
				symbol = parser.Symbol();
				if (!symbolTable.Contains(symbol))
				{
					symbolTable.AddEntry(symbol, romAddr);
				}
				break;

			case E_COMMAND:
				symbol = parser.Symbol();
				if (!symbolTable.Contains(symbol))
				{
					symbolTable.AddEntry(symbol, parser.EquValue());
				}
				else
				{
				    std::cout << "Duplicate equ" << symbol << std::endl;
				}
				break;

			default:
				std::cout << "Unimplemented instruction (pass 1)" << std::endl;
				break;
		}
	}

	// pass 2 -- convert assembly file to hack file line by line
	inputFile.clear();
	inputFile.seekg(0, inputFile.beg);
	char symbolBuffer[80];
	line = 0;
	while (parser.HasMoreCommands() && parser.Advance())
	{
		switch (parser.CommandType())
		{
			case A_COMMAND:
				symbol = parser.Symbol();
				if (!IsNumber(symbol))
				{
					// determine whether the symbol has been defined yet
					int address;
					if (symbolTable.Contains(symbol))
					{
						// get the defined symbol's corresponding value
						address = symbolTable.GetAddress(symbol);
					}
					else
					{
						// this is an undefined variable so allocate the next RAM address and add to symbol table
						address = ramAddr++;
						symbolTable.AddEntry(symbol, address);
					}
					sprintf(symbolBuffer, "%d", address);
					symbol = symbolBuffer;
				}
				outputFile << "0" << code.Symbol(symbol) << std::endl;
				break;

			case C_COMMAND:
				outputFile << "111" << code.Comp(parser.Comp()) << code.Dest(parser.Dest()) << code.Jump(parser.Jump()) << std::endl;
				break;

            // labels and equates are only used in the first pass so ignore them in the second pass
			case L_COMMAND:
			case E_COMMAND:
				break;

			default:
				std::cout << "Unimplemented instruction (pass 2)" << std::endl;
				break;
		}
	}

    return 0;
}


// end of hasm.cpp

    
