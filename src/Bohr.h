//
// Created by hryts on 4/7/20.
//

#ifndef GENOME_SUBSTR_BOHR_H
#define GENOME_SUBSTR_BOHR_H

#include <vector>
#include <string>
#include <unordered_map>

#define k 26

struct bohr_vrtx{
    int next_vrtx[k];
    int pat_num;        // pat_num -- index of of pattern
    int suff_link;
    int auto_move[k];   // remembering machine change of state
    int par;            // par - parent node in tree
    int suff_flink;     // sufficient suffix link TODO: WTF?? (Never used)
    bool flag;          // true is the vrtx is the end of a word
    char symb;          // symbol in the edge between parent and current
};

class Bohr {
public:
//    ~Bohr(); //TODO: think if destructor needed
    Bohr();
    void add_key(const std::string& s);
    void find_all_entries(const std::string& str);
    std::string to_str();

private:
    std::vector<bohr_vrtx> bohr;
    std::vector<std::string> pattern;
    bohr_vrtx make_bohr_vrtx(int p, char c);
    std::unordered_map<int, std::string> res;
    int get_auto_move(int v, char ch);
    int get_suff_flink(int v);
    int get_suff_link(int v);
    void check(int v,int i);
};



#endif //GENOME_SUBSTR_BOHR_H
