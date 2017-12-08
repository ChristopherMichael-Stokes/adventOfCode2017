#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>


void read_inputs(std::istream &is, std::vector<std::string> & inputs)
{
	for (std::string s; std::getline(is, s); )
		inputs.push_back(s);
}

std::string helper(std::string line, std::map<std::string, int> & registers)
{
	struct { std::string cmp; int value; } condition;
	std::istringstream iss(line);
	std::string tokens[3], trash;
	int count;
	iss >> tokens[0] >> tokens[1] >> count >> trash 
		>> condition.cmp >> tokens[2] >> condition.value;
	if (tokens[1] == "dec")
		count = -count;	
	bool ifcond;
	if (tokens[2] == "<") {
		ifcond = registers[condition.cmp] < condition.value;
	} else if (tokens[2] == ">") {
		ifcond = registers[condition.cmp] > condition.value; 
	} else if (tokens[2] == ">=") {
		ifcond = registers[condition.cmp] >= condition.value; 
	} else if (tokens[2] == "==") {
		ifcond = registers[condition.cmp] == condition.value;
	} else if (tokens[2] == "<=") {
		ifcond = registers[condition.cmp] <= condition.value; 
	} else if (tokens[2] == "!=") {
		ifcond = registers[condition.cmp] != condition.value;
	}
	registers[tokens[0]] += ifcond ? count : 0;
	return tokens[0];
}

int part1(const std::vector<std::string> & inputs)
{
	std::map<std::string, int> registers;

	for (const std::string & line : inputs) {
		helper(line, registers);
	}
	int max = registers.cbegin()->second;
	for (auto reg = ++registers.cbegin(); reg != registers.cend(); ++reg) 
		if (reg->second > max)
			max = reg->second;

	return max;
}

int part2(const std::vector<std::string> & inputs) 
{
	std::map<std::string, int> registers;
	int max = 0;
	for (const std::string & line : inputs) {
		std::string reg = helper(line, registers);	
		if (registers[reg] > max)
			max = registers[reg];
	}	
	return max;
}

int main()
{
	std::vector<std::string> inputs;
	std::ifstream file("input.txt");
	read_inputs(file, inputs);
	file.close();
	std::cout<<"part1: "<<part1(inputs)<<" part2: "<<part2(inputs)<<'\n';
	return 0;
}
