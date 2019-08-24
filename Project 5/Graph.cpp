//Johnathan Teav
#include <iostream>
#include <climits>
#include <queue>
#include <algorithm>

#include "Graph.hpp"

using namespace std;

//Creates a new vertex with the label provided
void Graph::addVertex(string label){
    ver.push_back(new Vertex);
    ver.back()->putLabel(label);
    ver.back()->putPosition(ver.size()-1);
}
//Deletes the vertex specified by the label
void Graph::removeVertex(string label){
    unsigned int i;
    for(i = 0; i < ver.size(); i++){
        if(ver.at(i)->label == label){
            ver.erase(ver.begin()+i);
            break;
        }
    }

    //Adjusts the positions of the remaining vertices
    for(unsigned int j = 0; j < ver.size(); j++){
        if(j >= i){
            ver.at(j)->position -= 1;
        }
    }
}
//Creates an edge between the specified labels with the weight specified
void Graph::addEdge(string label1, string label2, unsigned long weight){
    unsigned int i;
    unsigned int j;

    //Find the first vertex
    for(i = 0; i < ver.size(); i++)
        if(ver.at(i)->label == label1)
            break;

    //Find the second vertex
    for(j = 0; j < ver.size(); j++)
        if(ver.at(j)->label == label2)
            break;

    //Add edge connecting them
    ver.at(i)->addEdge(weight, ver.at(j));
    ver.at(j)->addEdge(weight, ver.at(i));
}
//Deletes edge between the specified vertices
void Graph::removeEdge(string label1, string label2){
    unsigned int i;
    unsigned int j;

    //Find the first vertex and delete its edge
    for(i = 0; i < ver.size(); i++)
        if(ver.at(i)->label == label1)
            break;
    ver.at(i)->removeEdge(label1, label2);

    //Find the second vertex and delete its edge
    for(j = 0; j < ver.size(); j++)
        if(ver.at(j)->label == label2)
            break;
    ver.at(j)->removeEdge(label2, label1);
}
//Finds the shortest path using Dijkstra's Algorithm
unsigned long Graph::shortestPath(string startLabel, string endLabel, vector<string> &path){
    unsigned long sum = ULONG_MAX;

    //Create a vector of distances
    vector<unsigned long> dist(ver.size(), ULONG_MAX);

    //Create a vector of unvisited vertices
    vector<Vertex*>unvisited;
    for(unsigned int i = 0; i < ver.size(); i++){
        unvisited.push_back(ver.at(i));
    }
    
    //Create a vector that will point to previous vertex in path
    vector<Vertex*>prev(ver.size(), nullptr);

    //Find the start vertex
    Vertex* cur;
    for(unsigned int i = 0; i < ver.size(); i++){
        if(ver.at(i)->label == startLabel){
            cur = ver.at(i);
            dist.at(i) = 0;
            break;
        }
    }

    //Find the end vertex
    Vertex* end;
    for(unsigned int i = 0; i < ver.size(); i++){
        if(ver.at(i)->label == endLabel){
            end = ver.at(i);
            break;
        }
    }

    //Loop for Dijkstra's Algorithm
    while(!unvisited.empty()){
        //Find the next unvisited vertex
        unsigned int j = 0;
        for(unsigned int i = 0; i < unvisited.size(); i++){
            //Determine if it is the closest vertex
            if(dist.at(unvisited.at(i)->position) < dist.at(cur->position)){
                cur = unvisited.at(i);
                j = i;
            }
        }

        //If destination vertex is reached
        if(cur == end){
            //Put prev labels into path
            Vertex* it = end;
            path.push_back(end->label);
            while(prev.at(it->position) != nullptr){
                path.push_back(prev.at(it->position)->label);
                it = prev.at(it->position);
            }

            reverse(path.begin(), path.end());

            sum = dist.at(cur->position);
            break;
        }
        //Erase current vertex from unvisited
        unvisited.erase(unvisited.begin()+j);

        //Visit each neighbor of the current vertex
        for(unsigned int i = 0; i < cur->ed.size(); i++){
            unsigned int distance = dist.at(cur->position) + cur->ed.at(i)->weight;
            if(distance < dist.at(cur->ed.at(i)->b->position)){
                dist.at(cur->ed.at(i)->b->position) = distance;
                prev.at(cur->ed.at(i)->b->position) = cur;
            }
        }
    
        //Assign cur to the next vertex
        if(!unvisited.empty()){
            cur = unvisited.at(0);
        }
    }
    
    return sum;
}
//Prints every vertice that graph contains. It calls the print function for edges.
void Graph::printVertices(){
    for(unsigned int i = 0; i < ver.size(); i++){
        cout << "Vertex\n";
        cout << "Label: " << ver.at(i)->label << " Position: " << ver.at(i)->position << endl;
        ver.at(i)->printEdges();
    }
}