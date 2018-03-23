#pragma once
#include <iostream>
#include <fstream>

class Debug
{
public:
	void OutputDebugText(char* outText);
private:
	std::string filepath = "./data/debug/debug.txt";
}debug;