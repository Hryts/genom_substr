//
// Created by kurlyana on 14.06.2020.
//

#ifndef OPENCL_PATTERNS_TRIE_H

#include <iostream>
#include <unordered_map>
#include <set>

// Node to represent the ending of the pattern and an id of the pattern to identify what pattern was found

struct PatternTrie {
    size_t id = 0;
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

PatternTrie* initPatternsTrie(const std::string patternsFilePath){
    auto patternsBuffer = readFile(patternsFilePath);
    size_t coma = 0;
    size_t eol = 0;
    int id;

    auto* res = new PatternTrie;

    for (size_t i=0;i<patternsBuffer.size();++i){
        if(patternsBuffer[i]==',') {
            coma=i;
            id = std::stoi(patternsBuffer.substr(eol, coma-eol));
        }
        if(patternsBuffer[i]=='LF') {
            eol=i;
            insert(res, patternsBuffer.substr(coma, eol-coma), id);
        }
    }
    return res;
}

#define OPENCL_PATTERNS_TRIE_H

#endif //OPENCL_PATTERNS_TRIE_H
