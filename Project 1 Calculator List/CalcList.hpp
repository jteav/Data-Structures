//Johnathan Teav
#ifndef CALCLIST_H
#define CALCLIST_H
#include <string>
#include "CalcListInterface.hpp"
using namespace std;

//Node for the linked list
//The node can store an operation and a number.
class Node {
private:
    FUNCTIONS op;
    double num;
    double sum = 0.0;
    Node* prev;
    Node* next;

    friend class LinkedList;
    friend class CalcList;
};

/*Class for the calculator
It stores its operations as a linked list
The count variable is to keep track of the size of the linked list*/
class CalcList:public CalcListInterface{
public:
    CalcList();
    ~CalcList();

    double total() const;
    void newOperation(const FUNCTIONS func, const double operand);
    void removeLastOperation();
    std::string toString(unsigned short precision) const;

    int count = 0; //Keeps track of the number of operations
protected:
    void add(Node* v, const FUNCTIONS& fun, const double& no);
    void remove(Node* v);
    bool empty() const;
private:
    Node* header;
    Node* trailer;
};

#endif