//
// Created by hryts on 6/15/20.
//

#ifndef OPENCL_TRANSITIONTABLE_H
#define OPENCL_TRANSITIONTABLE_H

#include <vector>

//struct Transition {
//    int ch;
//    size_t nextState;
//    size_t id;
//};
//
//struct Table {
//    std::vector<std::vector<Transition>> transitionTable; // TODO: init with size
//};
//
//void load(const std::vector<char>& buffer);

 struct Node{
     short ch;
     int id;
     size_t children[4];
 };

// void updateTrie(std::vector<Node>& trie, std::string word, size_t id);

 std::vector<Node> markersToTrie(std::vector<char> markers);
 std::vector<std::vector<char>> trieToVec(std::vector<Node> trie);

#endif //OPENCL_TRANSITIONTABLE_H
