#ifndef PROGRAM_TREE_H
#define PROGRAM_TREE_H

#include <string>
#include <set>

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
	int cumulative_weight() const;
	~program();
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
	program * root() const { return head; }
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

#endif
