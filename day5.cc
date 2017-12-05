#include <iostream>
#include <fstream>
#include <vector>

void read_input(std::istream &is, std::vector<int> & inputs)
{
	for (int i; is >> i; )
		inputs.push_back(i);
}

int part1(std::vector<int> inputs) 
{
	int steps = 0;
	for (int i = 0; i >= 0 && i < inputs.size(); ) {
		++inputs[i];
		i += inputs[i] - 1;
		++steps;
	}
	return steps;
}

int part2(std::vector<int> inputs)
{
	int steps = 0;
	for (int i = 0; i >= 0 && i < inputs.size(); ) {
		int offset = inputs[i];
		inputs[i] = inputs[i] >= 3 ? inputs[i]-1 : inputs[i]+1;
		i += offset;
		++steps;
	}
	return steps;
}

int main()
{
	std::vector<int> inputs;
	std::ifstream file("day5input.txt");
	read_input(file, inputs);
	file.close();
	std::cout << "part1: " << part1(inputs) << " part2: " << part2(inputs) << '\n';
	return 0;
}
