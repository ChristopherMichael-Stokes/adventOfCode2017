#include <iostream>
#include <fstream>
#include <utility>
#include <string>
#include <sstream>
#include <cinttypes>
#include <cstdio>

int part1(const std::pair<int, int> & input)
{
	const uint32_t divisor = 0x7FFFFFFF;
	const uint16_t mask = 0xFFFF, 
	      a_factor = 16807, b_factor = 48271;
	uint64_t a_value = input.first, b_value = input.second;
	int matches = 0;
	for (int i = 0; i < 4e7; ++i) {
		a_value = (a_factor*a_value) % divisor;
		b_value = (b_factor*b_value) % divisor;
		matches += ((a_value&mask)==(b_value&mask));
	}
	return matches;
}

int part2(const std::pair<int, int> & input)
{
	const uint32_t divisor = 0x7FFFFFFF;
	const uint16_t mask = 0xFFFF, 
	      a_factor = 16807, b_factor = 48271,
	      a_multiple = 4, b_multiple = 8;
	uint64_t a_value = (input.first*a_factor)%divisor,
		 b_value = (input.second*b_factor)%divisor;
	int matches = 0;
	for (int pairs = 0; pairs < 5e6; ++pairs) {
		do a_value = (a_factor*a_value) % divisor;
		while (a_value % a_multiple != 0);

		do b_value = (b_factor*b_value) % divisor;
		while (b_value % b_multiple != 0) ;

		matches += ((a_value&mask)==(b_value&mask));

	}
	return matches;
}

void read_input(std::istream& is, std::pair<int, int> & input)
{
	int x;
	std::string s;
	std::getline(is, s);
	sscanf(s.c_str(), "%*[^0-9]%d", &x);
	input.first = x;
	std::getline(is, s);
	sscanf(s.c_str(), "%*[^0-9]%d", &x);
	input.second = x;
}

int main()
{
	std::pair<int, int> input;
	std::ifstream file("input.txt");
	read_input(file, input);
	file.close();
	std::cout<<"part1: "<<part1(input)<<"\tpart2: "<<part2(input)<<'\n';	
	return 0;
}
