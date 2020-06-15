//
// Created by Bernadzikovskiy Slavik on 14.06.2020.
//

#ifndef GENOME_SUBSTR_UTILS_H
#define GENOME_SUBSTR_UTILS_H

#include <vector>
#include <string>
#include <unordered_map>
#include <map>

std::vector<char> readFile(const std::string& fileName);
void readConfig(std::map<std::string, std::string> &config, const char *file);

#endif //GENOME_SUBSTR_UTILS_H
