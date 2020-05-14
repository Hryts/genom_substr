#include <iostream>
#include "Bohr.h"


int main() {
    Bohr b;
    b.add_key("abc");
    b.add_key("ab");
    b.add_key("abcd");
    b.add_key("a");
    b.find_all_entries("aaabcdefghigkl");

    std::cout << b.to_str();
}