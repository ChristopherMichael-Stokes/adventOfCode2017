#include <iostream>
#include <vector>

int part1(const int cycle_size, const int cycles)
{
	std::vector<int> spin = {0};
	int current_pos = 0;
	for (int i = 1; i <= cycles; ++i) {
		current_pos = (current_pos + (cycle_size+1)) % spin.size();
		spin.insert(spin.begin()+current_pos+1, i);
	}	
	return spin[current_pos+2];
}

int part2(const int cycle_size, const int cycles)
{
	int value = 0, current_pos = 0;
	for (int i = 1; i <= cycles; ++i) {
		current_pos = (current_pos + (cycle_size+1)) % i;
		if (0 == current_pos)
			value = i;
	}
	return value;
}

int main()
{
	const int cycle_size = 304;
	std::cout<<"part1: "<<part1(cycle_size, 2017)<<
		"\tpart2: "<<part2(cycle_size, 5e7)<<'\n';
	return 0;
}
