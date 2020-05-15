//
// Created by hryts on 4/7/20.
//

#include <cstring>
#include <iostream>
#include "Bohr.h"

Bohr::Bohr() { bohr.push_back(make_bohr_vrtx(0, '$')); }

bohr_vrtx Bohr::make_bohr_vrtx(int p, char c) {
    bohr_vrtx v;
    memset(v.next_vrtx, 255, sizeof(v.next_vrtx));
    memset(v.auto_move, 255, sizeof(v.auto_move));
    v.flag = false;
    v.suff_link = -1;
    v.good_suff_link = -1;
    v.par = p;
    v.symb = c;
    return v;
}

void Bohr::add_key(const std::string &s) {
    int num=0; // starting from zero
    for (int i = 0; i < s.length(); ++i){
        char ch = s[i] - 'A'; // Get the index in alphabet TODO: find more efficient way (might be std::map)
        if (bohr[num].next_vrtx[ch] == -1){ // -1 - means there is no edge
            bohr.push_back(make_bohr_vrtx(num, ch));
            bohr[num].next_vrtx[ch] = bohr.size() - 1;
        }
        num = bohr[num].next_vrtx[ch];
    }
    bohr[num].flag = true;
    pattern.push_back(s);
    bohr[num].pat_num = pattern.size() - 1;
}

int Bohr::get_auto_move(int v, char ch) {
    if (bohr[v].auto_move[ch] == -1)
        if (bohr[v].next_vrtx[ch] != -1)  // no machine change of state remembered
            bohr[v].auto_move[ch] = bohr[v].next_vrtx[ch];
        else if (v == 0)
            bohr[v].auto_move[ch] = 0;
        else
            bohr[v].auto_move[ch] = get_auto_move(get_suff_link(v), ch);
    return bohr[v].auto_move[ch];
}

int Bohr::get_good_suff_link(int v) {
    if (bohr[v].good_suff_link == -1){ // Didn't count suffix yet
        int u=get_suff_link(v);
        if (u==0) // either v is a root, or suff_ling of points on the root
            bohr[v].good_suff_link = 0;
        else
            bohr[v].good_suff_link = (bohr[u].flag) ? u : get_good_suff_link(u);
    }
    return bohr[v].good_suff_link;
}

int Bohr::get_suff_link(int v) {
    if (bohr[v].suff_link==-1)
        if (v==0 || bohr[v].par==0)
            bohr[v].suff_link=0;
        else
            bohr[v].suff_link = get_auto_move(get_suff_link(bohr[v].par), bohr[v].symb);
    return bohr[v].suff_link;
}

void Bohr::check(int v, int i, std::unordered_map<std::string, int> &res) {
    for(int u=v;u!=0;u=get_good_suff_link(u)){
        if (bohr[u].flag) {
//            res[pattern[bohr[u].pat_num]] = 1;
            std::cout<<"+"<<std::endl;
        }
//            std::cout<<res.find(pattern[bohr[u].par])==res;
    }
}

void Bohr::find_all_entries(const std::string &str, std::unordered_map<std::string, int> &res) {
    int u=0;
    for(int i=0; i < str.length(); ++i){
        u=get_auto_move(u, str[i] - 'A');
        check(u,i+1, res);
    }
}
