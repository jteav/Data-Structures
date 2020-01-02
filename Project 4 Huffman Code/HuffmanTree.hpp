//Johnathan Teav

#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include "HuffmanBase.hpp"
#include "HeapQueue.hpp"
#include <map>
#include <stack>
#include <utility>

using namespace std;

class HuffmanTree:public HuffmanTreeBase {
public:
    string compress(string inputStr);
    string serializeTree() const;
    string decompress(string inputCode, const std::string serializedTree);
private:
    map<char, size_t> freqMap;
    char c;
    size_t f;
    HeapQueue <HuffmanNode*, HuffmanNode::Compare> freqQueue;
};

#endif