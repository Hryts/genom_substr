//
// Created by Bernadzikovskiy Slavik on 14.06.2020.
//

#ifndef GENOME_SUBSTR_UTILS_H
#define GENOME_SUBSTR_UTILS_H

#include <vector>
#include <string>
#include <unordered_map>

std::vector<char> readFile(const std::string& fileName);
std::unordered_map<size_t, std::string> readCSVMarkers(std::string pathToFile);


#endif //GENOME_SUBSTR_UTILS_H
