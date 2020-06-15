//
// Created by hryts on 6/15/20.
//

#include <string>
#include "transitionTable.h"

std::string subVectorToStr(std::vector<char> vec, size_t from, size_t to) {
    std::vector<char> subVector(vec.begin()+from, vec.begin()+to);
    std::string strRes(subVector.begin(), subVector.end());
    return strRes;
}

void loadWord(Table* table, std::string word, size_t id){
    for (size_t i = 0; i < word.size()-1; ++i) {
        Transition* currentState{};
        currentState->ch = word[i];
        currentState->id = id;

    }
}

void load(Table* table, const std::vector<char>& patternsBuffer) {
//        TODO: two bit coding of input data

    size_t coma = 0;
    size_t eol = 0;
    size_t id;

    for (size_t i=0;i<patternsBuffer.size();++i){
        if(patternsBuffer[i]==',') {
            coma=i;
            id = std::stoi(subVectorToStr(patternsBuffer, eol, coma));
        }
        if(patternsBuffer[i]==10) { // TODO: sth instead of 10 here needed
            eol=i;
            std::string word = subVectorToStr(patternsBuffer, coma, eol);
        }
    }
}
