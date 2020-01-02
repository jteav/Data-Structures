//Johnathan Teav
#include <string>
#include <list>
#include <iostream>

#include "Vertex.hpp"
#include "Edge.hpp"

using namespace std;

//Inserts vertex label
void Vertex::putLabel(string l){
    label = l;
}
//Inserts vertex position
void Vertex::putPosition(int p){
    position = p;
}
//Adds edge to vertex connecting it to other vertex specified
void Vertex::addEdge(unsigned long w, Vertex *b){
    ed.push_back(new Edge);
    ed.back()->position = ed.size()-1;
    ed.back()->weight = w;
    ed.back()->a = this;
    ed.back()->b = b;
}
//Deletes edge connecting to vertex specified
void Vertex::removeEdge(string l1, string l2){
    for(unsigned int i = 0; i < ed.size(); i++)
        if(ed.at(i)->a->label == l1 && ed.at(i)->b->label == l2){
            ed.erase(ed.begin()+i);
            break;
        }
}
//Prints every edge the vertex contains
void Vertex::printEdges(){
    cout << "Edges\n";
    for(unsigned int i = 0; i < ed.size(); i++)
        ed.at(i)->printEdge();
}