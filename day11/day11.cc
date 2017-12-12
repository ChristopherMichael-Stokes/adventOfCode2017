#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

enum direction{NW, N, NE, SE, S, SW};
struct Hex {
	int x, y, z, max_distance;
	int distance() {
		return (abs(x)+abs(y)+abs(z))/2;	
	}
	Hex& operator+=(direction rhs) {
		switch(rhs) {
		case NW:	++y; --x; break;
		case N:		++y; --z; break;
		case NE:	--z; ++x; break;
		case SE:	--y; ++x; break;
		case S:		--y; ++z; break;
		case SW:	++z; --x; break;
		}
		const int current_distance = distance();	
		max_distance = max_distance < current_distance 
			? current_distance : max_distance;
		return *this;
	}

};

void iterate_inputs(const std::string & inputs, Hex & path)
{
	std::istringstream iss(inputs);
	int max_distance = 0;
	for (std::string s; std::getline(iss, s, ','); ) {
		direction d;
		if ("nw" == s) {
			d = direction::NW;
		} else if ("n" == s) {
			d = direction::N;
		} else if ("ne" == s) {
			d = direction::NE;
		} else if ("se" == s) {
			d = direction::SE;
		} else if ("s" == s) {
			d = direction::S;
		} else if ("sw" == s) {
			d = direction::SW;
		}
		path += d;
	}
}

int main()
{
	std::string inputs;
	std::ifstream file("input.txt");
	std::getline(file, inputs);
	file.close();
	Hex path = {0,0,0,0};
	iterate_inputs(inputs, path);
	std::cout<<"part1: "<<path.distance()<<"\tpart2: "<<path.max_distance<<'\n';
	return 0;
}
