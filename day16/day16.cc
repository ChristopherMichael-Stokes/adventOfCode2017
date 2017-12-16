#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <vector>

inline std::string dance(const std::string & inputs, 
		std::string programs)
{
		std::istringstream iss(inputs);
	for (std::string command; std::getline(iss, command, ','); ) {
		const char dance_type = command[0];
		if ('s' == dance_type) {
			int x;
			sscanf(command.c_str(), "%*c%d", &x);	
			const auto begin = programs.end()-x, end = programs.end();
			std::string copy(begin, end);
			programs.erase(begin, end);
			programs.insert(0, copy);
		} else if ('x' == dance_type) {
			int begin, end;
			sscanf(command.c_str(), "%*c%d%*c%d", &begin, &end);
			const char c = programs[begin];
			programs[begin] = programs[end];
			programs[end] = c;
		} else if ('p' == dance_type) {
			char begin, end;
			sscanf(command.c_str(), "%*c%c%*c%c", &begin, &end);
			size_t a = programs.find(begin), b = programs.find(end);
			char c = programs[a];
			programs[a] = programs[b];
			programs[b] = c;
		}
	}
	return programs; 
}

std::string part1(const std::string & inputs)
{
	size_t plen = 16;
	std::string programs(plen,'a');
	for (int i = 0; i < plen; ++i)
		programs[i]+=i;

	return dance(inputs, programs);
}

std::string part2(const std::string & inputs)
{
	const int cycles = 1e9;
	std::vector<std::string> programs;
	std::string current = part1(inputs);
	programs.push_back(current);
	int i = 0;
	for ( ; i < cycles-1; ++i) {
		current = dance(inputs, current);	
		if (std::find(programs.cbegin(), 
			programs.cend(), current)!= programs.cend())
			break;
		programs.push_back(current);
	}
	return programs[(cycles-1)%programs.size()]; 
}

int main()
{
	std::ifstream file("input.txt");
	std::string inputs;
	std::getline(file, inputs);
	//std::cout<<"part1: "<<part1(inputs)<<'\n';
	std::cout<<"part1: "<<part1(inputs)<<"\tpart2: "<<part2(inputs)<<'\n';
	return 0;
}
