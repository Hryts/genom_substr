//
// Created by kurlyana on 14.06.2020.
//

#ifndef OPENCL_PATTERNS_TRIE_H

#include <iostream>
#include <unordered_map>
#include <set>

// Node to represent the ending of the pattern and an id of the pattern to identify what pattern was found

struct PatternTrie {
    int id = -1;
    bool isEndOfPattern = false;
    std::unordered_map<char, PatternTrie*> children;
};

// need to insert an id at the end of every pattern!!!!!!!!!

PatternTrie* makeNewTrieNode()
{
    auto* node = new PatternTrie;
    return node;
}

void insert(PatternTrie*& root, const std::string& pattern, int id)
{
    if (root == nullptr)
        root = makeNewTrieNode();

    PatternTrie* temp = root;
    for (char x : pattern) {
        if (temp->children.find(x) == temp->children.end())
            temp->children[x] = makeNewTrieNode();
        temp = temp->children[x];
    }

    temp->isEndOfPattern = true;
    temp->id = id;
}


std::set<int> search(PatternTrie* root, const std::string& subGenome)
{
    std::set<int> patternIDs;

    if (root == nullptr)
        return patternIDs;

    PatternTrie* temp = root;
    for (char i : subGenome) {
        temp = temp->children[i];

        if (temp == nullptr)
            return patternIDs;

        if (temp->isEndOfPattern)
            patternIDs.insert(temp->id);
    }

    if (temp->isEndOfPattern)
        patternIDs.insert(temp->id);

    return patternIDs;
}

#define OPENCL_PATTERNS_TRIE_H

#endif //OPENCL_PATTERNS_TRIE_H
