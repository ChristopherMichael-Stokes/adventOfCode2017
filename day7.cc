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
	std::size_t amount_children() { return children.size(); }
	program * get_parent() const { return parent; }
	const std::string &get_name() const { return name; }
	int get_weight() const { return weight; }
	~program() {
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
	void set_head(program * p) {
		if (nullptr != head)
			p->add_child(head);
		head = p;
	}
	~program_tree() {
		head->~program();
		delete head;
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

const std::string & part1(program_tree & programs) 
{

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
