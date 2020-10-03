//Johnathan Teav
#include "GritVM.hpp"
using namespace std;
using namespace GVMHelper;

//The constructor sets machineStatus to WAITING, the accumulator to zero,
//and the currentInstruct iterator to the beginning of the instruction memory
GritVM::GritVM(){
    machineStatus = WAITING;
    accumulator = 0;
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
            if(isalpha(line[0])){
                instructMem.push_back(parseInstruction(line));
            }
        }

        currentInstruct = instructMem.begin();

        if(instructMem.size() != 0){
            machineStatus = READY;
        }
        
        return machineStatus;
}

//The run function runs the program.
//It returns the STATUS of the GritVM program.
STATUS GritVM::run(){
    //Sets the status to RUNNING
    if(machineStatus == READY){
        machineStatus = RUNNING;
    }

    /*Calls the evaluate function to interpret the instructions
    Also calls the advanceInstruct function to advance the instructions
    The loop ends when the machineStatus changes or when it runs out of instructions*/
    while(machineStatus == RUNNING && currentInstruct != instructMem.end()){
        long jumpDistance = evaluate(*currentInstruct);
        advanceInstruct(jumpDistance);
    }

    if(currentInstruct == instructMem.end()){
        machineStatus = HALTED;
    }

    if(instructMem.empty()){
        machineStatus = WAITING;
    }

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
long GritVM::evaluate(Instruction instruct){
    long jump;
    switch(instruct.operation){
        case CLEAR:{
            accumulator = 0;
            jump = 1;
            break;
        }
        case AT:{
            accumulator = dataMem.at(instruct.argument);
            jump = 1;
            break;
        }
        case SET:{
            dataMem.at(instruct.argument) = accumulator;
            jump = 1;
            break;
        }
        case INSERT:{
            dataMem.insert(dataMem.begin() + instruct.argument, accumulator);
            jump = 1;
            break;
        }
        case ERASE:{
            dataMem.erase(dataMem.begin() + instruct.argument);
            jump = 1;
            break;
        }
        case ADDCONST:{
            accumulator += instruct.argument;
            jump = 1;
            break;
        }
        case SUBCONST:{
            accumulator -= instruct.argument;
            jump = 1;
            break;
        }
        case MULCONST:{
            accumulator *= instruct.argument;
            jump = 1;
            break;
        }
        case DIVCONST:{
            accumulator /= instruct.argument;
            jump = 1;
            break;
        }
        case ADDMEM:{
            accumulator += dataMem.at(instruct.argument);
            jump = 1;
            break;
        }
        case SUBMEM:{
            accumulator -= dataMem.at(instruct.argument);
            jump = 1;
            break;
        }
        case MULMEM:{
            accumulator *= dataMem.at(instruct.argument);
            jump = 1;
            break;
        }
        case DIVMEM:{
            accumulator /= dataMem.at(instruct.argument);
            jump = 1;
            break;
        }
        case JUMPREL:{
            jump =  instruct.argument;
            break;
        }
        case JUMPZERO:{
            if(accumulator == 0){
                jump = instruct.argument;
                break;
            }
            else{
                jump = 1;
                break;
            }
        }
        case JUMPNZERO:{
            if(accumulator != 0){
                jump = instruct.argument;
                break;
            }
            else{
                jump = 1;
                break;
            }
        }
        case NOOP:{
            jump = 1;
            break;
        }
        case HALT:{
            machineStatus = HALTED;
            break;
        }
        case OUTPUT:{
            cout << accumulator << endl;
            jump = 1;
            break;
        }
        case CHECKMEM:{
            //I converted dataMem.size() to an unsigned int to avoid a warning
            unsigned int size = dataMem.size();
            if(size >= instruct.argument){
                jump = 1;
            }
            else{
                machineStatus = ERRORED;
            }
            break;
        }
        default:{
            jump = 1;
        }
    }
    return jump;
}

//Advances the instruction by the proper amount.
void GritVM::advanceInstruct(long jump){
    advance(currentInstruct, jump);
}

//A print function to test some functionality.
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
/*
int main(){
    GritVM vm;
    vector<long> mem = {42};
    vm.load("test.gvm", mem);
    vm.run();
    vector<long> data = vm.getDataMem();
    cout << data[0] << endl;
    cout << data[1] << endl;
    cout << data[2] << endl;
    
    return 0;
}*/