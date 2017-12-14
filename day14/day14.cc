#include "knot_hash.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <cinttypes>
#include <cstring>
#include <array>

const int grid_size = 128;
typedef std::array<std::array<int,grid_size>,grid_size> _grid;

int part1(_grid & grid)
{
	int count = 0;
	for (int i = 0; i < grid_size; ++i) {
		for (int j = 0; j < grid_size; ++j) {
			count += grid[i][j];
		}
	}


	return count;
}

void fill_array(const std::string & input, _grid & grid)
{
	const int strsize = 16;
	for (int i = 0; i < grid_size; ++i) {
		std::string hash_value = hash(input+"-"+std::to_string(i));
		for (int j = 0; j < grid_size/64; ++j) {

			char hexes[strsize+1];
			memset(hexes, '\0', strsize+1);
			for (int k = 0; k < strsize; ++k) {
				hexes[k] = hash_value[k+(j*strsize)];
			}
			uint64_t hex = strtoull(hexes,nullptr,16);
			for (int k = 63; k >= 0; --k) {
				grid[i][k+(j*64)] = hex & 1;
				hex >>= 1;

			}
		}
	}

}

int main()
{
	const std::string input = "stpzcrnm";
	_grid grid;
	fill_array(input, grid);	
	std::cout<<"part1: "<<part1(grid)<<'\n';
	return 0;
}
