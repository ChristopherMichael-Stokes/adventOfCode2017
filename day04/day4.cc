#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

void read_input(istream &is, vector<vector<string>> &inputs) 
{
        for (string str; getline(is, str); ) {
                stringstream s(str);
                vector<string> line;
                for (string word; s >> word; ) 
                        line.push_back(word);
                inputs.push_back(line);
        }
}

int part1(const vector<vector<string>> &inputs)
{
        int valid_phrases = 0;
        for (const vector<string>& line : inputs) {
                int is_valid = 1;
                for (const string & word : line) {
                        int occurences = count_if(line.cbegin(),line.cend(),[word](string in) { return in==word; });
                        if (occurences > 1) {
                                is_valid = 0;
                                break;
                        }
                }
                valid_phrases += is_valid;
        }
        return valid_phrases;
}

bool same_chars(const string& source, const string& comp)
{
        if (comp.size() != source.size())
                return false;
        for (int i = 0; i < source.size(); ++i) {
                if (count(source.cbegin(),source.cend(),source[i]) != count(comp.cbegin(),comp.cend(),source[i]))
                        return false;
        } 
}

int part2(const vector<vector<string>> &inputs)
{
        int valid_phrases = 0;
        for (const vector<string>& line : inputs) {
                int is_valid = 1;
                for (const string & word : line) {
                        int anagrams = 0;
                        for (const string & other : line) {
                                if (same_chars(word,other))
                                        anagrams++;
                        } 
                        if (anagrams > 1) {
                                is_valid = 0; 
                                break;
                        }
                }
                valid_phrases += is_valid;
        }
        return valid_phrases;
}

int main()
{
        vector<vector<string>> inputs;
        read_input(ifstream("day4input.txt"), inputs);
        cout << "part1: " << part1(inputs) << " part2: " << part2(inputs) << '\n';
        return 0;
}