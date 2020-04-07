#include "Bohr.h"


int main() {
    Bohr b;
    b.add_key("abc");
    b.add_key("ab");
    b.add_key("cbc");
    b.add_key("dab");
    b.find_all_entries("abracadabra");
}