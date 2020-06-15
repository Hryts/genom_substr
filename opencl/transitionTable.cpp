//
// Created by hryts on 6/15/20.
//

#include <string>
#include "transitionTable.h"
//#include "patterns_trie.h"

std::string subVectorToStr(std::vector<char> vec, size_t from, size_t to) {
    std::vector<char> subVector(vec.begin()+from, vec.begin()+to);
    std::string strRes(subVector.begin(), subVector.end());
    return strRes;
}

//void loadWord(Table* table, std::string word, size_t id){
//    for (size_t i = 0; i < word.size()-1; ++i) {
//        Transition* currentState{};
//        currentState->ch = word[i];
//        currentState->id = id;
//
//    }
//}

//void load(Table* table, const std::vector<char>& patternsBuffer) {
////        TODO: two bit coding of input data
//
//    size_t coma = 0;
//    size_t eol = 0;
//    size_t id;
//
//    for (size_t i=0;i<patternsBuffer.size();++i){
//        if(patternsBuffer[i]==',') {
//            coma=i;
//            id = std::stoi(subVectorToStr(patternsBuffer, eol, coma));
//        }
//        if(patternsBuffer[i]==10) { // TODO: sth instead of 10 here needed
//            eol=i;
//            std::string word = subVectorToStr(patternsBuffer, coma, eol);
//        }
//    }
//}

std::vector<Node> markersToTrie(std::vector<char> markers) {
    std::vector<Node> res;

    size_t coma = 0;
    size_t eol = 0;
    int id=10;


    for (size_t i=0;i<markers.size();++i){
        if(markers[i]==',') {
            coma=i;
            id = std::stoi(subVectorToStr(markers, eol, coma));
        }
        if(markers[i]=='\n') {
            eol=i;
            auto marker = subVectorToStr(markers, coma, eol);
            updateTrie(res, marker, id);
        }
    }
}

std::vector<std::vector<size_t>> trieToVec(std::vector<Node> trie) {
    std::vector chars;
    std::vector ids;
    std::vector firsts;
    std::vector seconds;
    std::vector thirds;
    std::vector fourths;
    for (auto node:trie){
        chars.push_back(node.ch);
        ids.push_back(node.id);
        firsts.push_back(node.children[0]);
        seconds.push_back(node.children[1]);
        thirds.push_back(node.children[2]);
        fourths.push_back(node.children[3]);
    }
    std::vector<std::vector<size_t>> res;
    res.push_back(chars);
    res.push_back(ids);
    res.push_back(firsts);
    res.push_back(seconds);
    res.push_back(thirds);
    res.push_back(fourths);

    return res;
}

void updateTrie(std::vector<Node>& trie, const std::string& word, size_t id) {
    if (trie.empty()) {
        Node root{};
        root.ch='!';
        root.id=-1;
        trie.push_back(root);
    }

    Node previousNode = trie[0];

    for (char i : word){
        int child;
        char letter = i;

        if (letter == 'A')
            child = 0;
        else if (letter == 'C')
            child = 1;
        else if (letter == 'T')
            child = 2;
        else
            child = 3;

        Node currentNode{};
        currentNode.id=-1;
        currentNode.ch=i;

        if (previousNode.children[child] == 0) {
            previousNode.children[child] = trie.size();
            trie.push_back(currentNode);
            previousNode = currentNode;
        }
        else {
            previousNode = trie[previousNode.children[child]];
        }
    }
    previousNode.id = id;
}