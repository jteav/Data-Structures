//Johnathan Teav
#ifndef GRITVM_H
#define GRITVM_H
#include "GritVMBase.hpp"
#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <iterator>
using namespace std;
using namespace GVMHelper;

//Class to interpret and evaluate the GritVM program
class GritVM:public GritVMInterface {
public:
    GritVM();
    STATUS load(const string filename, const vector<long> &initialMemory);
    STATUS run();
    vector<long> getDataMem();
    STATUS reset();
    void printVM(bool printData, bool printInstruction);
    void evaluate(Instruction instruct);
private:
    vector<long> dataMem;
    list<Instruction> instructMem;
    list<Instruction>::iterator currentInstruct;
    STATUS machineStatus;
    long accumulator;
    ifstream file;
};

#endif