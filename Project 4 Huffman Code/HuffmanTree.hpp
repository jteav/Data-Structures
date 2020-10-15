//Johnathan Teav

#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include "HuffmanBase.hpp"
#include "HeapQueue.hpp"
#include <map>
#include <deque>
using namespace std;

class HuffmanTree:public HuffmanTreeBase {
public:
    string compress(string inputStr);
    string serializeTree() const;
    string decompress(string inputCode, string serializedTree);
protected:
    void encode(HuffmanNode* cur, string prefixCode);
    void postOrder(HuffmanNode* cur);
private:
    map<char, size_t> freqMap;  //Map of the frequencies of each character
    map<char, string> charMap;  //Map of the prefix codes of each character
    HeapQueue <HuffmanNode*, HuffmanNode::Compare> freqQueue;   //Priority queue of frequencies from the map
    string compressedStr;
    string serializedStr;
    string decompressedStr;
};

#endif