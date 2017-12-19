#include <iostream>
#include <fstream>
#include <queue>
#include <array>
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
    int sound, ic;
    unit() : sound{0}, ic{0}{}
    unit(int x) : sound{0}, ic{0}{
        registers.insert(std::pair<char, register_>('p', register_('p',x)));
    }
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

int step(std::array<std::queue<uint64_t>,2> & q, unit & registers, 
    const instruction & instructions, int pid)
{
    std::cout<<pid<<" ic q1 q2 "<<registers.ic<<'\t'<<q[0].size()<<'\t'<<q[1].size()<<'\n';
    while (registers.ic < instructions.size()) {
        std::istringstream iss(instructions[registers.ic]);
        std::string opcode;
        char address;
        iss >> opcode >> address;
        if ("snd" == opcode) {

            q[0 == pid ? 1 : 0].push(registers[address].value);

        } else if ("rcv" == opcode) {

            if (0 == q[pid].size())
                return registers.ic;
            registers[address] = q[pid].front();            
            q[pid].pop();

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
                    registers.ic += value;
                    continue;
                }
            }
        }
        ++registers.ic;
    }
    return -1;
}

int part2(const instruction & instructions)
{
    int pid[] = {0, 1};
    unit registers[] = {unit(pid[0]), unit(pid[1])};
    std::array<std::queue<uint64_t>,2> q;
    int i = 0;
    do {
        step(q, registers[pid[0]], instructions, pid[0]);
        //std::cout<<q[0].size()<<' '<<q[1].size()<<' '<<registers[0].registers.size()<<' '<<registers[1].registers.size()<<'\n';
        step(q, registers[pid[1]], instructions, pid[1]);
    } while (!(q[0].empty() && q[1].empty()));
    return -1;
}

int main()
{
    instruction instructions;
    std::ifstream file("input.txt");
    read_inputs(file, instructions);
    file.close();
    //std::cout<<"part1: "<<part1(instructions)<<'\n';
    std::cout<<"part2: "<<part2(instructions)<<'\n';
    return 0;
}