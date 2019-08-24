//Johnathan Teav
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include "CalcList.hpp"

using namespace std;

//The constructor for the linked list
LinkedList::LinkedList(){
header = new Node;
trailer = new Node;
header->next = trailer;
trailer->prev = header;
}

//The destructor for the linked list
LinkedList::~LinkedList(){
    while (!empty()) removeFront();
    delete header;
    delete trailer;
}

//Checks to see if the list is empty
bool LinkedList::empty() const{
    return (header->next == trailer);
}

//Inserts the operation and number before node v
void LinkedList::add(Node* v, const FUNCTIONS& fun, const double& no){
    Node* u = new Node;
    u->op = fun;
    u->num = no;
    u->next = v;
    u->prev = v->prev;
    v->prev->next = v->prev = u;
}

//Adds element e to the back of the list
void LinkedList::addBack(const FUNCTIONS& fun, const double& no){
    add(trailer, fun, no);
}

//Removes the node v
void LinkedList::remove(Node* v){
    Node* u = v->prev;
    Node* w = v->next;
    u->next = w;
    w->prev = u;
    delete v;
}

//Removes an element from the front of the list
void LinkedList::removeFront(){
    remove(header->next);
}

//Removes an element from the back of the list
void LinkedList::removeBack(){
    remove(trailer->prev);
}

//Returns the current total in the linked list
//The while loop iterates through the linked list
//The if statements determine what operation to perform.
double CalcList::total() const{
    if(list.empty()){
        return 0;
    }
    else{
    Node* cur = list.header->next;
    double sum = 0;

    while(cur->next != NULL)
    {
        if(cur->op == ADDITION){
            sum += cur->num;
        }
        else if(cur->op == SUBTRACTION){
            sum -= cur->num;
        }
        else if(cur->op == MULTIPLICATION){
            sum *= cur->num;
        }
        else if(cur->op == DIVISION){
            sum /= cur->num;
        }

        cur = cur->next;
    }

    return sum;
}
}

//Adds a new operation to the calculator
//First argument is the operation to be used
//Second argument is the number to be used
//It also increments count to keep track of the size of the linked list
void CalcList::newOperation(const FUNCTIONS func, const double operand){
    list.addBack(func, operand);
    count++;
}

//Removes the last operation from the calculator
//It also decrements count to keep track of the size of the linked list
void CalcList::removeLastOperation(){ 
        list.removeBack();
        count--;
}

//Returns the list of operations in the calculator in string format
//The argument specifies the decimal precision
//The while loop interates through the linked list
//It iterates backwards starting from the end
//The if statements determine what the operation is and how to format it
std::string CalcList::toString(unsigned short precision) const{
    Node* cur = list.trailer->prev;
    double sum = total();
    string str;         //string to store everything
    int i = count;      //variable to countdown
    
    while(cur->prev != NULL)
    {
        if(cur->op == ADDITION){
            //This section inserts the decrement countdown variable into the string
            ostringstream ct;
            ct << i;
            str += ct.str();
            str += ": ";
            i--;

            //This section sets up the value on the left of the operation
            //and inserts it into the string
            sum -= cur->num;
            ostringstream first;
            first << fixed << setprecision(precision) << sum;
            str += first.str();

            //This inserts the operation into the string
            str += "+";

            //This section sets up the value on the right of the operation
            ostringstream no;
            no << fixed << setprecision(precision) << cur->num;
            str += no.str();

            //This inserts the equal sign into the string
            str += "=";

            //This sets up the total on the right of the equal sign
            //and inserts it into the string
            ostringstream tot;
            tot << fixed << setprecision(precision) << sum+cur->num;
            str += tot.str();
            
            str += "\n";
        }
        //The rest of the if statements follow the same format as the first
        else if(cur->op == SUBTRACTION){
            ostringstream ct;
            ct << i;
            str += ct.str();
            str += ": ";
            i--;

            sum += cur->num;
            ostringstream first;
            first << fixed << setprecision(precision) << sum;
            str += first.str();

            str += "-";

            ostringstream no;
            no << fixed << setprecision(precision) << cur->num;
            str += no.str();

            str += "=";

            ostringstream tot;
            tot << fixed << setprecision(precision) << sum-cur->num;
            str += tot.str();

            str += "\n";
        }
        else if(cur->op == MULTIPLICATION){
            ostringstream ct;
            ct << i;
            str += ct.str();
            str += ": ";
            i--;

            sum /= cur->num;
            ostringstream first;
            first << fixed << setprecision(precision) << sum;
            str += first.str();

            str += "*";

            ostringstream no;
            no << fixed << setprecision(precision) << cur->num;
            str += no.str();

            str += "=";

            ostringstream tot;
            tot << fixed << setprecision(precision) << sum*cur->num;
            str += tot.str();

            str += "\n";
        }
        else if(cur->op == DIVISION){
            ostringstream ct;
            ct << i;
            str += ct.str();
            str += ": ";
            i--;

            sum *= cur->num;
            ostringstream first;
            first << fixed << setprecision(precision) << sum;
            str += first.str();

            str += "/";

            ostringstream no;
            no << fixed << setprecision(precision) << cur->num;
            str += no.str();

            str += "=";

            ostringstream tot;
            tot << fixed << setprecision(precision) << sum/cur->num;
            str += tot.str();

            str += "\n";
        }

        cur = cur->prev;
    }
    return str;
}

/*int main()
{
    CalcList calc;
    cout << "The total is: " << calc.total() << endl;
    return 0;
}*/