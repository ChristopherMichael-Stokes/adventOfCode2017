#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>

class stack {
private:
	int multiplier, _score;
	std::list<char> state;
public:
	int garbage;
	stack() : multiplier{ 0 }, _score{ 0 }, garbage{ 0 }{}
	void push(char c) { 
		state.push_back(c); 
		++multiplier;
	}
	void pop() {
		if (state.empty())
			return;
		state.pop_back();
		_score += multiplier;
		--multiplier;
	}
	int score() const { return _score; }
};

void eval_stream(const std::string & input, stack & st)
{
	std::istringstream iss(input);
	for (char c; iss >> c; ) {
		if ('{' == c) {
			st.push(c);
		} else if ('}' == c) {
			st.pop();	
		} else if ('<' == c) {
			for (char ca; iss >> ca; ) {
				if ('>' == ca)
					break;
				else if ('!' == ca)
					iss >> ca;
				else 
					++st.garbage;
			}	
		} if ('!' == c) {
			iss >> c;
		}
	}
}

int part1(const std::string & input, const stack & st)
{
	return st.score();
}

int part2(const std::string & input, const stack & st)
{
	return st.garbage;
}

void read_input(std::istream & is, std::string & input)
{
	for (char c; is >> c; )
		input += c;
}

int main(int argc, char** argv)
{
	std::ifstream file("input.txt");
	std::string input = " ";
	read_input(file, input);
	file.close();
	stack st;
	eval_stream(input, st);
	std::cout<<"part1: "<<part1(input, st)<<" part2: "<<part2(input, st)<< '\n';
	return 0;
}
