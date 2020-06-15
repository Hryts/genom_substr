//
// Created by hryts on 6/15/20.
//

#ifndef OPENCL_TRANSITIONTABLE_H
#define OPENCL_TRANSITIONTABLE_H

#include <vector>

 struct Node{
     short ch;
     int id;
     size_t children[4];
 };

 std::vector<Node> markersToTrie(std::vector<char> markers);
 std::vector<std::vector<char>> trieToVec(std::vector<Node> trie);

#endif //OPENCL_TRANSITIONTABLE_H
