#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void read_input(istream &in, string & input)
{
    for (string s; in >> s; )
        input += s;
}

int part1(const string & input)
{
    int sum = 0;
    if (input[0] == input[input.size() - 1])
        sum += input[0] - '0';
    for (int i = 1; i < input.size(); ++i) {
        if (input[i] == input[i - 1])
            sum += input[i] - '0';
    }
    return sum;
}

int part2(const string & input)
{
    int sum = 0, offset = input.size()/2;
    for (int i = 0; i < offset; ++i) {
        if (input[i] == input[i+offset])
            sum += input[i] - '0';
    }
    return sum * 2;
}

int main() 
{
    string input;
    read_input(ifstream("day1input.txt"), input); 
    //cout << input << '\n';
    cout << "part 1: " << part1(input) << "\tpart 2:" << part2(input) << '\n';
    return 0;
}