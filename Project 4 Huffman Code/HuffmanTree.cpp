//Johnathan Teav
#include "HuffmanTree.hpp"
#include <string>
using namespace std;

//The compress function compresses a string into a Huffman code.
string HuffmanTree::compress(string inputStr){
    //Inserts the characters and their frequencies into a map
    for(int i = 0; inputStr[i] != *inputStr.end(); i++){
        if(freqMap.find(inputStr[i]) == freqMap.end())
            freqMap.insert(pair<char, size_t>(inputStr[i], 1));
        else
            freqMap.at(inputStr[i])++;
    }

    //Inserts the characters and frequencies into a priority queue
    for(map<char, size_t>::iterator it = freqMap.begin(); it != freqMap.end(); it++){
        c = it->first;
        f = it->second;
        HuffmanNode *np = new HuffmanNode(c,f);
        freqQueue.insert(np);
    }

//TEST
    cout << "MAP\n";
    for(map<char, size_t>::iterator it = freqMap.begin(); it != freqMap.end(); it++)
        cout << it->first << "->" << it->second << endl;

    cout << "QUEUE\n";
    while(!freqQueue.empty()){
        cout << freqQueue.min() << endl;
        freqQueue.removeMin();
    }

    return "";
}
//The serializeTree function organizes the characters connected to the nodes using post order.
string HuffmanTree::serializeTree() const{
    return "";
}
//The decompress function deserializes the tree and decompress the Huffman code.
string HuffmanTree::decompress(string inputCode, const std::string serializedTree){
    return "";
}
//TEST
int main(){
    HuffmanTree huff;
    huff.compress("it is time to unmask the computing community as a Secret Society for the Creation and Preservation of Artificial Complexity");
    return 0;
}