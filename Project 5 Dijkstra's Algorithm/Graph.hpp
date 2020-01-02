//Johnathan Teav
#ifndef GRAPH_H
#define GRAPH_H

#include "GraphBase.hpp"
#include "Vertex.hpp"
#include "Edge.hpp"

using namespace std;

//Class for a graph containing vertices
class Graph:public GraphBase {
public:
    void addVertex(string label);
    void removeVertex(string label);
    void addEdge(string label1, string label2, unsigned long weight);
    void removeEdge(string label1, string label2);
    unsigned long shortestPath(string startLabel, string endLabel, vector<string> &path);
    void printVertices();
private:
    vector<Vertex*>ver;
};

#endif