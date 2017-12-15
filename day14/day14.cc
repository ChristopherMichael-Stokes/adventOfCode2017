#include "knot_hash.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <cinttypes>
#include <cstring>
#include <array>
#include <stack>
#include <utility>

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

void clear_group(_grid & grid, int i, int j)
{
	grid[i][j] = 0;
	if (i > 0) {
		if (1 == grid[i-1][j])
			clear_group(grid, i-1, j);
	}
	if (i < grid_size - 1) {
		if (1 == grid[i+1][j]) 
			clear_group(grid, i+1, j);
	}
	if (j > 0) {
		if (1 == grid[i][j-1])
			clear_group(grid, i, j-1);
	}
	if (j < grid_size - 1) {
		if (1 == grid[i][j+1])
			clear_group(grid, i, j+1);
	}
}

int part2(_grid grid)
{
	int groups = 0;
	for (int i = 0; i < grid_size; ++i) {
		for (int j = 0; j < grid_size; ++j) {
			if (1 == grid[i][j]) {
				clear_group(grid,i,j);
				++groups;
			}

		}
	}
	return groups;
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
	std::cout<<"part1: "<<part1(grid)<<"\tpart2: "<<part2(grid)<<'\n';
	return 0;
}
