#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

void read_input(std::istream &is, std::vector<int> & inputs)
{
	for (int i; is >> i; )
		inputs.push_back(i);
}

int part1(std::vector<int> inputs)
{
	std::vector<std::vector<int>> before;
	int cycles = 0;
	do {
		before.push_back(inputs);	
		++cycles;
		int idx =  0;
		for (int i = 0 ; i < inputs.size(); ++i)
			if (inputs[i] > inputs[idx])
				idx = i;

		int blocks = inputs[idx];
		inputs[idx] = 0;
		for (int i = idx; blocks > 0; --blocks)
			++inputs[i%inputs.size()];
	} while (std::find(before.cbegin(), before.cend(), inputs) == before.cend());
	return cycles;
}

int main()
{
	std::vector<int> inputs;
	std::ifstream file("day6input.txt");
	read_input(file, inputs);
	std::cout << "part1: " << part1(inputs) << '\n';
	return 0;
}
