#include <iostream>
#include <map>
#include <fstream>

bool caught(const std::map<int, int> & inputs, int delay)
{
	for (const auto& p : inputs)
		if ((p.first+delay)%(2*(p.second-1))==0)
			return true;
	return false;
}

int part1(const std::map<int, int> & inputs)
{
	int cost = 0;
	for (const auto& p : inputs) {
		if ((p.first)%(2*(p.second-1))==0)
			cost += p.first*p.second;
	}
	return cost;
}

int part2(const std::map<int, int> & inputs)
{
	int delay = 0;
	for ( ; caught(inputs,delay); ++delay);
	return delay;
}

void read_inputs(std::istream & is, std::map<int, int> & inputs)
{
	int depth, range;
	for (char _c; is >> depth >> _c >> range; ) {
		inputs[depth] = range;	
	}
}

int main()
{
	std::map<int, int> inputs;
	std::ifstream file("input.txt");
	read_inputs(file, inputs);
	file.close();
	std::cout<<"part1: "<<part1(inputs)<<"\tpart2:" <<part2(inputs)<<'\n';
	return 0;
}
