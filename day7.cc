#include <string>
#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstring>

class program {
private:
	const std::string name;
	const int weight;
	std::set<program *> children;
	program * parent;
public:
	program(const std::string & name, int weight)
		: name{ name }, weight{ weight }, parent{ nullptr }{}
	program(const std::string & name, int weight, program * parent) 
		: name{ name }, weight{ weight }, parent{ parent }{}

	void add_child(program * p) { p->parent = this; children.insert(p); }
	std::set<program *> &get_children() { return children; }
	
	const std::string &get_name() const { return name; }
	int get_weight() const { return weight; }
	~program() {
		for (auto & p: children) {
			if (p->children.size() == 0)
				delete p;
			else {
				p->~program();
				delete p;
			}
		}
	}

};

class program_tree {
private:
	program * head;
public:
	program_tree() : head{ nullptr }{}
	program_tree(program * p) : head{ p }{} 
	program_tree(const std::string & name, int weight)
		: head{ new program(name, weight, nullptr) }{}
	void add_child(const std::string & name, int weight) {
		program * p = new program(name,weight,head);
		head->add_child(p);
	}
	program * root() { return head; }
	void set_head(const std::string & name, int weight) {
		program * p = new program(name,weight,nullptr);
		if (nullptr != head) 
			p->add_child(head);
		head = p;
	}
};

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

	std::cout << ps.begin()->second->get_name()<< '\n';
				
}

const std::string & part1(program_tree & programs) 
{

	programs.set_head("new head",10);
	return programs.root()->get_name();
}

int main()
{
	std::ifstream file("day7input.txt");
	program_tree programs;
	read_program_tree(file, programs);
	std::cout<<"part1: "<<part1(programs)<<'\n';
	file.close();
	return 0;
}
