//Johnathan Teav
#include "GritVM.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <exception>
#include <iterator>
using namespace std;
using namespace GVMHelper;

//The constructor sets machineStatus to WAITING, the accumulator to zero,
//and the currentInstruct iterator to the beginning of the instruction memory
GritVM::GritVM(){
    machineStatus = WAITING;
    accumulator = 0;
    currentInstruct = instructMem.begin();
}
//The load function takes in the filename and a vector for the initial memory.
//It returns the STATUS of the GritVM program.
STATUS GritVM::load(const string filename, const vector<long> &initialMemory){
        file.open(filename);

        //throw if there is an issue with opening the file
        if(!file.is_open()){
            throw "Error opening file.\n";
        }

        //copies the initialMemory into the dataMem
        dataMem = initialMemory;

        string line;

        //parses the instructions and pushes them into instructMem
        while(getline(file, line)){
            if(isalpha(line[0]))
                instructMem.push_back(parseInstruction(line));
        }
    
        if(instructMem.size() != 0)
            machineStatus = READY;
        
        return machineStatus;
}
//The run function runs the program.
//It returns the STATUS of the GritVM program.
STATUS GritVM::run(){
    //Sets the status to RUNNING
    if(machineStatus == READY)
        machineStatus = RUNNING;
    
    //Calls the evaluate function to interpret the instructions
    //The loop ends when the machineStatus changes or when it runs out of instructions
    while(machineStatus == RUNNING && currentInstruct != instructMem.end()){
        evaluate(*currentInstruct);
    }

    if(currentInstruct == instructMem.end())
        machineStatus = HALTED;

    if(instructMem.empty())
        machineStatus = WAITING;

    file.close();

    return machineStatus;
}
//Returns the data memory vector
vector<long> GritVM::getDataMem(){
    return dataMem;
}
//Resets the GritVM program
STATUS GritVM::reset(){
    dataMem.clear();
    instructMem.clear();
    machineStatus = WAITING;
    accumulator = 0;
    currentInstruct = instructMem.begin();

    return machineStatus;
}
//The evaluate function uses switch statements to execute the instructions
void GritVM::evaluate(Instruction instruct){
    vector<long>::iterator it;

    switch(instruct.operation){
        case CLEAR:{
            accumulator = 0;
            currentInstruct++;
        }
        case AT:{
            accumulator = dataMem.at(instruct.argument);
            currentInstruct++;
        }
        case SET:{
            dataMem.at(instruct.argument) = accumulator;
            currentInstruct++;
        }
        case INSERT:{
            dataMem.insert(dataMem.begin() + instruct.argument, accumulator);
            currentInstruct++;
        }
        case ERASE:{
            dataMem.erase(dataMem.begin() + instruct.argument);
            currentInstruct++;
        }
        case ADDCONST:{
            accumulator += instruct.argument;
            currentInstruct++;
        }
        case SUBCONST:{
            accumulator -= instruct.argument;
            currentInstruct++;
        }
        case MULCONST:{
            accumulator *= instruct.argument;
            currentInstruct++;
        }
        case DIVCONST:{
            accumulator /= instruct.argument;
            currentInstruct++;
        }
        case ADDMEM:{
            accumulator += dataMem.at(instruct.argument);
            currentInstruct++;
        }
        case SUBMEM:{
            accumulator -= dataMem.at(instruct.argument);
            currentInstruct++;
        }
        case MULMEM:{
            accumulator *= dataMem.at(instruct.argument);
            currentInstruct++;
        }
        case DIVMEM:{
            accumulator /= dataMem.at(instruct.argument);
            currentInstruct++;
        }
        case JUMPREL:{
            std::advance(currentInstruct, instruct.argument);
        }
        case JUMPZERO:{
            if(accumulator == 0)
                std::advance(currentInstruct, instruct.argument);
            else
                currentInstruct++;
        }
        case JUMPNZERO:{
            if(accumulator != 0)
                std::advance(currentInstruct, instruct.argument);
            else
                currentInstruct++;
        }
        case NOOP:{
            currentInstruct++;
        }
        case HALT:{
            machineStatus = HALTED;
        }
        case OUTPUT:{
            cout << accumulator << endl;
            currentInstruct++;
        }
        case CHECKMEM:{
            //I converted dataMem.size() to an unsigned int to avoid a warning
            unsigned int size = dataMem.size();
            if(size < instruct.argument)
                machineStatus = ERRORED;
            currentInstruct++;
        }
        default:{
            currentInstruct++;
        }
    }
}
//Just a print function to test some functionality
void GritVM::printVM(bool printData, bool printInstruction){
    cout << "****** Output Dump ******" << endl;
    cout << "Status: " << statusToString(machineStatus) << endl;

    if(printData) {
        cout << "*** Data Memory ***" << endl;
        int index = 0;
        vector<long>::iterator it = dataMem.begin();
        while(it != dataMem.end()){
            long item = (*it);
            cout << "Location " << index++ << ": " << item << endl;
            it++;
        }
    }

    if(printInstruction) {
        cout << "*** Instruction Memory ***" << endl;
        int index = 0;
        list<Instruction>::iterator it = instructMem.begin();
        while(it != instructMem.end()){
            Instruction item = (*it);
            cout << "Instruction " << index++ << ": " << instructionToString(item.operation) << " " << item.argument << endl;
            it++;
        }
    }
}