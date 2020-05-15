//
// Created by hryts on 4/7/20.
//

#ifndef GENOME_SUBSTR_BOHR_H
#define GENOME_SUBSTR_BOHR_H

#include <vector>
#include <string>
#include <unordered_map>

struct bohr_vrtx { // TODO: Try to replace <int next_vrtx[k]> and <int auto_move[k]> with std::map or std::unordered_map
    int next_vrtx[26];
    int auto_move[26];   // remembering machine change of state
    int suff_link;
    int good_suff_link;
    int pat_num;        // pat_num -- index of of pattern
    int par;            // par - parent node in tree
    bool flag;          // true is the vrtx is the end of a word
    char symb;          // symbol in the edge between parent and current
};

class Bohr {
public:
//    ~Bohr(); //TODO: think if destructor needed
    Bohr();
    void add_key(const std::string& s);
    void find_all_entries(const std::string& str, std::unordered_map<std::string, int> &res);

private:
    std::vector<bohr_vrtx> bohr;
    std::vector<std::string> pattern;
    bohr_vrtx make_bohr_vrtx(int p, char c);
    int get_auto_move(int v, char ch);
    int get_good_suff_link(int v);
    int get_suff_link(int v);
    void check(int v,int i, std::unordered_map<std::string, int> &res);
};



#endif //GENOME_SUBSTR_BOHR_H
