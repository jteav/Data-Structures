//Johnathan Teav
#include "HuffmanTree.hpp"
#include <string>
using namespace std;

//The compress function compresses a string into a Huffman code.
//It takes a string as input and returns and encoded string.
string HuffmanTree::compress(string inputStr){
    //Inserts the characters and their frequencies into a map
    for(int i = 0; i < inputStr.size(); i++){
        if(freqMap.find(inputStr[i]) == freqMap.end())
            freqMap.insert(pair<char, size_t>(inputStr[i], 1));
        else
            freqMap.at(inputStr[i])++;
    }

    //Inserts the characters and frequencies into a priority queue
    for(map<char, size_t>::iterator it = freqMap.begin(); it != freqMap.end(); it++){
        HuffmanNode *np = new HuffmanNode(it->first, it->second);
        freqQueue.insert(np);
    }

    //Turns characters into leaf nodes and creates intermediate nodes
    HuffmanNode* left;
    HuffmanNode* right;
    HuffmanNode* parentNode;
    while(freqQueue.size() != 1){
        left = freqQueue.min();
        freqQueue.removeMin();
        right = freqQueue.min();
        freqQueue.removeMin();

        int freqSum = left->getFrequency() + right->getFrequency();
        parentNode = new HuffmanNode('\0', freqSum, nullptr, left, right);
        freqQueue.insert(parentNode);
    }

    //Encode the characters into a map.
    encode(freqQueue.min(), "");

    //Append the string with encoded characters
    for(char c : inputStr){
        compressedStr += charMap[c];
    }

    //Serialize the tree using post order.
    postOrder(freqQueue.min());

    return compressedStr;
}

//Returns a serialized string.
string HuffmanTree::serializeTree() const{
    return serializedStr;
}

//The decompress function takes a Huffman code and its serialized tree and returns the original text.
string HuffmanTree::decompress(string inputCode, string serializedTree){
    HuffmanNode* right;
    HuffmanNode* left;
    HuffmanNode* parent;

    deque <HuffmanNode*> charQueue;

    //Deserialize the tree.
    for(int i = 1; i < serializedTree.length(); i++){
        //Build a new tree.
        if((serializedTree[i] == 'B' && serializedTree[i-1] != 'L')||
            (serializedTree[i] == 'B' && serializedTree[i-1] == 'L' && serializedTree[i-2] == 'L')){
            right = charQueue.back();
            charQueue.pop_back();
            left = charQueue.back();
            charQueue.pop_back();
            parent = new HuffmanNode('\0', 1, nullptr, left, right);
            charQueue.push_back(parent);
        }
        //Push nodes into deque to attach to the tree.
        else if(serializedTree[i-1] == 'L'){
            charQueue.push_back(new HuffmanNode(serializedTree[i], 1));
        }
    }

    //Decode the inputCode using the deserialized tree.
    HuffmanNode* cur = charQueue.back();
    for(char ch : inputCode){
        if(ch == '0'){
            cur = cur->left;
        }
        else if(ch == '1'){
            cur = cur->right;
        }

        if(cur -> isLeaf()){
            decompressedStr += cur->getCharacter();
            cur = charQueue.back();
        }
    }
    
    return decompressedStr;
}

//Recursive function that traverses the tree and encodes the characters with a map.
//cur is the current node. prefixCode is the character encoded.
//Left traversal is a 0. Right traversal is a 1.
void HuffmanTree::encode(HuffmanNode* cur, string prefixCode){
    if(cur == nullptr){
        return;
    }
    else{
        if(cur->getFrequency() != '0'){
            charMap.insert(pair<char, string>(cur->getCharacter(), prefixCode));
        }

        encode(cur->right, prefixCode + "1");   //1 for right branch
        encode(cur->left, prefixCode + "0");    //0 for left branch
    }
}

//Recursive function to serialize the tree using post order.
//Leaves have an L plus the character  appended to the string.
//Branches have a B appended to the string.
//cur is the current node.
void HuffmanTree::postOrder(HuffmanNode* cur){
    if(cur == nullptr){
        return;
    }
    else{
        postOrder(cur->left);
        postOrder(cur->right);

        if(cur->isBranch()){
            serializedStr += 'B';
        }
        else if(cur->isLeaf()){
            serializedStr += 'L';
            serializedStr += cur->getCharacter();
        }
    }
}