//Johnathan Teav
#ifndef EDGE_H
#define EDGE_H
#include <iostream>

#include "Vertex.hpp"

using namespace std;

//Class an edge pointing to two vertices
class Edge{
public:
    //Prints info about the edge
    void printEdge(){
        cout << "Position: " << position << " Weight: " << weight << " a: " << a->label << " b: " << b->label << endl;
    }
private:
    int position;
    int weight;
    Vertex* a;
    Vertex* b;
friend class Vertex;
friend class Graph;
};

#endif