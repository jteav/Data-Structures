//Johnathan Teav
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include "CalcList.hpp"

using namespace std;

//The constructor for the linked list
CalcList::CalcList(){
header = new Node;
trailer = new Node;
header->next = trailer;
trailer->prev = header;
}

//The destructor for the linked list
CalcList::~CalcList(){
    while (!empty()) remove(header->next);
    delete header;
    delete trailer;
}

//Checks to see if the list is empty
bool CalcList::empty() const{
    return (header->next == trailer);
}

//Inserts the operation and number before node v
void CalcList::add(Node* v, const FUNCTIONS& fun, const double& no){
    count++;

    Node* u = new Node;
    u->op = fun;
    u->num = no;
    u->next = v;
    u->prev = v->prev;
    v->prev->next = u;
    v->prev = u;
    u->sum = u->prev->sum;
}

//Removes the node v
void CalcList::remove(Node* v){
    if(empty()){
        throw("List is already empty!");
    }
    else{
        count--;

        Node* u = v->prev;
        Node* w = v->next;
        u->next = w;
        w->prev = u;
        delete v;
    }
}

//Returns the current total in the linked list.
double CalcList::total() const{
    return trailer->prev->sum;
}

/*Adds a new operation to the calculator.
First argument is the operation to be used.
Second argument is the number to be used.*/
void CalcList::newOperation(const FUNCTIONS func, const double operand){
    add(trailer, func, operand);

    switch(func){
        case ADDITION:
            trailer->prev->sum += operand;
            break;
        case SUBTRACTION:
            trailer->prev->sum -= operand;
            break;
        case MULTIPLICATION:
            trailer->prev->sum *= operand;
            break;
        case DIVISION:
            if(operand == 0){
                removeLastOperation();
                throw("Divide by zero error.");
            }
            else{
                trailer->prev->sum /= operand;
                break;
            }
        default:
            throw("Arithmetic operation error. Addition, Subtraction, Multiplication, and Division only.");
            break;
    }
}

//Removes the last operation from the calculator
void CalcList::removeLastOperation(){ 
        remove(trailer->prev);
}

/*Returns the list of operations in the calculator in string format
The argument specifies the decimal precision
The while loop interates through the linked list
It iterates backwards starting from the end
The if statements determine what the operation is and how to format it*/
std::string CalcList::toString(unsigned short precision) const{
    Node* cur = trailer->prev;
    stringstream ss;        //variable to store data stream
    string str = "";        //string to return
    int step = count;       //variable to countdown

    ss.precision(precision);//sets the precision to floats
    
    while(cur->prev != NULL)
    {
        ss << step << ": ";
        ss << cur->prev->sum;

        if(cur->op == ADDITION){
            ss << "+";
        }
        else if(cur->op == SUBTRACTION){
            ss << "-";
        }
        else if(cur->op == MULTIPLICATION){
            ss << "*";
        }
        else if(cur->op == DIVISION){
            ss << "/";
        }
        ss << cur->num << "=" << cur->sum << endl;

        cur = cur->prev;
        step--;
    }
    str = ss.str();
    return str;
}