#include "program_tree.h"
#include <string>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstring>

int program::cumulative_weight() const
{
	int cweight = weight;
	for (program * p : children) {
		if (p->amount_children()>0) {
			cweight += p->cumulative_weight();
		} else {
			cweight += p->get_weight();
		}
	}
	return cweight;
}

program::~program()
{
	std::set<program *>::iterator it = children.begin();
	program *p;
	while (children.size()>0) {
		p = *it;
		it = children.erase(it);
		if (p->amount_children()>0)
			p->~program();
		delete p;
	}
}

void read_program_tree(std::istream & is, program_tree & programs)
{
	std::vector<std::string> lines;
	for (std::string s; std::getline(is, s); )
		lines.push_back(s);	
	std::map<std::string, program*> ps;

	for (const std::string & s : lines) {
		char name_buffer[100];
		int weight;
		sscanf(s.c_str(), "%s (%d)",name_buffer,&weight);
		ps[name_buffer] = new program(name_buffer,weight);
	}

	for (const std::string & s : lines) {
		char buffer[500], name_buffer[100];
		memset(buffer, '\0', 500);
		sscanf(s.c_str(), "%s (%*d) -> %[^\n]",name_buffer,buffer);
		std::vector<std::string> tokens;
		if (strlen(buffer) == 0)
			continue;
		std::string children = buffer;
		const std::string delim = ", ";
		std::size_t start = 0, end;	
		do {
			end = children.find(delim, start);
			std::size_t altend = end == std::string::npos 
						? children.size() : end;
			tokens.push_back(std::string(children.cbegin()+start,children.cbegin()+altend));
			start = end+delim.size();
		} while (end != std::string::npos);
		for (std::string & tok : tokens) {
			ps.at(name_buffer)->add_child(ps.at(tok));
		}
	}
	for(auto& p : ps) {
		program* cp = p.second;
		if (cp->get_parent() == nullptr) {
			programs.set_head(cp);
			break;
		}
	}
}

const std::string & part1(const program_tree & programs) 
{

	return programs.root()->get_name();
}

program * unbalanced(program *disk) 
{
	std::set<program *> ps = disk->get_children();
	program * odd = nullptr;
	for (program * p : ps) {
		std::set<program *> nset = ps;
		nset.erase(p);
		if (std::find_if(nset.begin(),nset.end(),
			[p](program * current) {
				return current->cumulative_weight()==p->cumulative_weight();
			}) == nset.end())
			return odd = p;
	}
	return odd;
}
int part2(program_tree & programs)
{
	program * odd = unbalanced(programs.root());
	std::set<program *> ps = programs.root()->get_children();
	program * _odd = *std::find_if_not(ps.begin(),ps.end(),
		[odd](program * cmp){ return cmp == odd; });
	int diff = _odd->cumulative_weight()-odd->cumulative_weight();
	for (program * compare = odd; compare != nullptr; compare = unbalanced(odd)) {
		odd = compare;
	}
	return odd->get_weight()+diff;
}

int main()
{
	std::ifstream file("day7input.txt");
	program_tree programs;
	read_program_tree(file, programs);
	std::cout<<"part1: "<<part1(programs)<<"\n"<<part2(programs)<<'\n';
	file.close();
	return 0;
}
