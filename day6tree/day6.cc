#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <memory>
#include <list>

using namespace std;

class Node {
private:
	list<Node *> children;
	list<Node *>::iterator child(int b)	{
		return find_if(children.begin(),children.end(),
		[&](Node * child){
			return child->blocks == b;
		});
	}

public:
	int blocks;
	Node(int b) : blocks{ b }{}
	~Node() { delete this; }
	//false if child is already false
	bool add_child(int b) {
		Node * n = new Node(b);
		if (child(b) == children.end()) {
			children.push_back(n);
			return true;
		}
        return false;
	}
    list<Node *> get_child() {
		return children;
	}
};

class tree {
private:
	Node* head;
public:


};

void read_input(istream &is, vector<int> & inputs)
{
	for (int i; is >> i; )
		inputs.push_back(i);
}

void print_vector(const std::vector<int> & v)
{
	for (int i : v)
		cout << i << '\t';
	cout << '\n';
}

int part1(vector<int> & inputs)
{
	return 0;
}

int main()
{
	vector<int> inputs;
	ifstream file("~/programming/day6/day6input.txt");
	read_input(file, inputs);
	cout << "part1: " << part1(inputs) << '\n';
	return 0;
}
