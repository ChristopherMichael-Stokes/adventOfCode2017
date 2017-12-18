#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cinttypes>

typedef std::vector<std::string> instruction;

struct register_ {
    char address;
    uint64_t value;

    register_(char a, uint64_t v) : address{a}, value{v}{}
    register_(char a) : address{a}, value{0}{}
    register_& operator=(int v) {
        this->value = v;
        return *this;
    }
    register_& operator+=(int v) {
        this->value += v;
        return *this;
    }
    register_& operator*=(int v) {
        this->value *= v;
        return *this;
    }
    register_& operator%=(int v) {
        this->value %= v;
        return *this;
    }
};

struct unit {
    std::map<char, register_> registers;
    int sound;
    register_& operator[](char a){
        auto reg = registers.find(a);
        if (reg != registers.end()) {
            return reg->second;
        }
        registers.insert(std::pair<char, register_>(a, register_(a)));
        return registers.find(a)->second;
    }
};


int part1(const instruction & instructions)
{
    unit registers;
    int ic = 0;
    while (ic < instructions.size()) {
        std::istringstream iss(instructions[ic]);
        std::string opcode;
        char address;
        iss >> opcode >> address;
        if ("snd" == opcode) {
            registers.sound = registers[address].value;
        } else if ("rcv" == opcode) {
            if (0 != registers[address].value)
                return registers.sound; 
        } else {
            std::string op;
            iss >> op;
            uint64_t value = op[0] < 'a'? atoi(op.c_str()) : registers[op[0]].value; 
            if ("set" == opcode) {
                registers[address] = value;
            } else if ("add" == opcode) {
                registers[address] += value;
            } else if ("mul" == opcode) {
                registers[address] *= value;
            } else if ("mod" == opcode) {
                registers[address] %= value;
            } else if ("jgz" == opcode) {
                if (registers[address].value > 0) {
                    ic += value;
                    continue;
                }
            }
        }
        ++ic;
    }
    return -1;
}

void read_inputs(std::istream & is, instruction & inputs)
{
    for (std::string s; std::getline(is, s); )
        inputs.push_back(s);
}

int main()
{
    instruction instructions;
    std::ifstream file("input.txt");
    read_inputs(file, instructions);
    file.close();
    std::cout<<"part1: "<<part1(instructions)<<'\n';
    return 0;
}