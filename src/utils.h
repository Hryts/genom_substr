//
// Created by Bernadzikovskiy Slavik on 5/15/20.
//

#ifndef GENOME_SUBSTR_UTILS_H
#define GENOME_SUBSTR_UTILS_H

#include <string>
#include <map>
#include <boost/locale.hpp>
#include <fstream>
#include <sstream>

void getConfig(std::map<std::string, std::string> &config, int &threadNum);
void readFile(const std::string &file, std::string& res);

#endif //GENOME_SUBSTR_UTILS_H
