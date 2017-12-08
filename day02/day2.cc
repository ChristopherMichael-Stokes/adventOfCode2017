#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <sstream>
#include <algorithm>

using namespace std;

void read_input(istream &in, vector<vector<int>> &inputs) 
{
        for (string str; getline(in, str); ) {
                stringstream s(str);
                vector<int> row;
                for (int i; s >> i; )
                        row.push_back(i);
                inputs.push_back(row);
        }        
}

int part1(vector<vector<int>> & inputs)
{
        int sum = 0;
        for (vector<int> row : inputs) {
                int a = row[0], b = row[1], min, max;
                min = a < b ? a : b;
                max = a > b ? a : b;
                for (int i = 2; i < row.size(); ++i) {
                        if (row[i] > max)
                                max = row[i];
                        else if (row[i] < min)
                                min = row[i];
                }
                sum += max-min;
        }
        return sum;
}

int part2(vector<vector<int>> & inputs)
{
        int sum = 0;
        for (vector<int> row : inputs) {
                bool match = false;
                for (int i = 0; i < inputs.size() && !match; ++i) {
                        for (int j = i+1; j < inputs.size() && !match; ++j) {
                                int max = row[i] > row[j] ? row[i] : row[j];
                                int min = row[i] < row[j] ? row[i] : row[j];
                                if (max % min == 0) {
                                        sum += max / min;
                                        match = true;
                                }
                        }
                }
        }
        return sum;
}

int main()
{
        vector<vector<int>> inputs;
        read_input(ifstream("day2input.txt"), inputs); 
        cout << "part1: " << part1(inputs) << "\tpart2: " << part2(inputs) << '\n';
        return 0;
}