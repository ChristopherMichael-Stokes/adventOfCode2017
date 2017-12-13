#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <queue>
#include <cstdlib>
#include <fstream>
#include <sstream>

std::set<int> group(const std::map<int,std::vector<int>> & inputs,
		const int id)
{
	std::set<int> visited_nodes;
	std::queue<int> visiting_nodes;
	const auto& programs = inputs.at(id);
	for (int i : programs) {
		visited_nodes.insert(i);
		visiting_nodes.push(i);
	}
	while (!visiting_nodes.empty()) {
		for (int i : inputs.at(visiting_nodes.front())) {
			if (visited_nodes.insert(i).second)
				visiting_nodes.push(i);
		}	
		visiting_nodes.pop();
	}
	return visited_nodes;
}

int part1(const std::map<int,std::vector<int>> & inputs)
{
	return group(inputs,0).size();
}

int part2(const std::map<int,std::vector<int>> & inputs)
{
	std::vector<std::set<int>> groups;
	for (const auto& it : inputs) {
		bool newgroup = true;
		for (const auto & g : groups) {
			if (g.find(it.first) != g.end()) {
				newgroup = false;	
				break;
			}
		}
		if (newgroup)
			groups.push_back(group(inputs, it.first));	
	}
	return groups.size();
}

void read_inputs(std::istream & is,  
		std::map<int,std::vector<int>> & inputs)
{
	for (std::string s; std::getline(is, s); ) {
		std::istringstream iss(s);
		int id, next;
		std::string _s;
		iss >> id >> _s;
		std::vector<int> group;
		for (std::string x; std::getline(iss, x, ','); ) {
			group.push_back(atoi(x.c_str()));	
		}
		inputs[id]=group;
	}
}

int main()
{
	std::ifstream file("input.txt");
	std::map<int,std::vector<int>> inputs;
	read_inputs(file, inputs);
	file.close();
	std::cout<<"part1: "<<part1(inputs)<<"\tpart2: "<<part2(inputs)<<'\n';
	return 0;	
}
