#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <sstream>
#include <iomanip>

int part1(std::istream & is, size_t elements)
{
	std::vector<int> inputs;
	int x; is >> x;
	inputs.push_back(x);
	for (char c; is >> c >> x; )
		inputs.push_back(x);
	unsigned char list[elements];
	for (int i = 0; i < elements; ++i)
		list[i] = i;
	int loopstart = 0, skipsize = 0;
	for (int i = 0; i < inputs.size(); ++i) {
		const int length = inputs[i], 
		      loopend = (loopstart + length - 1) % elements;
		if (0 != length) {
			for (int j = 0; j < length/2; ++j) {
				const int start = (loopstart + j) % elements,
				      end = (loopend - j) % elements,
				      swap = list[start];
				list[start] = list[end];
				list[end] = swap;
			}
		}
		loopstart = (loopstart + length + skipsize++) % elements;
	}
	return list[0]*list[1]; 
}

std::string part2(std::string lengths) 
{
	size_t elements = 256, rounds = 64, dense = 16;
	const char std_suffix[] = {17, 31, 73, 47, 23};
	lengths += std_suffix;

	unsigned char sparse_hash[elements];
	for (int i = 0; i < elements; ++i)
		sparse_hash[i] = i;

	int loopstart = 0, skipsize = 0;
	for (int r = 0; r < rounds; ++r) {
		for (int i = 0; i < lengths.size(); ++i) {
			const int length = lengths[i], 
			      loopend = (loopstart + length - 1) % elements;

			if (0 != length) {
				for (int j = 0; j < length/2; ++j) {
					const int start = (loopstart + j) % elements,
					      end = (loopend - j) % elements,
					      swap = sparse_hash[start];
					sparse_hash[start] = sparse_hash[end];
					sparse_hash[end] = swap;
				}
			}
			loopstart = (loopstart + length + skipsize++) % elements;
		}
	}
	short dense_hash[dense];
	std::stringstream hexstring;
	for (int i = 0; i < dense; ++i) {
		int idx = i*dense;
		dense_hash[i] = sparse_hash[idx]; 
		for (int j = 1; j < dense; ++j) {
			dense_hash[i] ^= sparse_hash[j+idx];
		}
		hexstring<<std::setfill('0')<<std::setw(sizeof(char)*2)
			<<std::hex<<dense_hash[i];
	}
	return hexstring.str(); 
}

int main()
{
	std::ifstream file("input.txt");
	std::string inputs;
	std::getline(file, inputs);
	file.close();
	std::istringstream iss(inputs);
	std::cout<<"part1: "<<part1(iss, 256)<<
		"\tpart2: "<<part2(inputs)<<'\n';
	return 0;
}
