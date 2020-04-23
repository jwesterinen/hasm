/*
// Code class definition
 */

#pragma once

#include <string>

class Code
{
public:
	Code();
	~Code();
	const std::string& Symbol(const std::string& symbol);
	const std::string& Dest(const std::string& dest) const;
	const std::string& Comp(const std::string& comp) const;
	const std::string& Jump(const std::string& jump) const;

private:
	std::string symbolBin;
	std::string errMsg;
};
