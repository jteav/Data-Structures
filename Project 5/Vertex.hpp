//Johnathan Teav
#ifndef VERTEX_H
#define VERTEX_H

#include <string>
#include <vector>

using namespace std;

class Edge; //Forward declaration

//Class for a vertex containing edges
class Vertex{
public:
    void putLabel(string l);
    void putPosition(int p);
    void addEdge(unsigned long w, Vertex *b);
    void removeEdge(string l1, string l2);
    void printEdges();
private:
    string label;
    int position;
    vector<Edge*>ed;
friend class Graph;
friend class Edge;
};

#endif