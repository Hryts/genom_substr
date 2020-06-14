//
// Created by Bernadzikovskiy Slavik on 14.06.2020.
//

#include "rw_utils.h"
#include <fstream>

std::vector<char> readFile(const std::string& fileName) {
    std::ifstream file(fileName, std::ios::binary | std::ios::ate);
    if (file) {
        std::streamsize size = file.tellg(); // Get file size.
        file.seekg(0, std::ios::beg); // Move file cursor back to start.

        std::vector<char> buffer(size);
        if (file.read(buffer.data(), size)) {
            return buffer;
        } else {
            std::string message = "Failed to read file \"" +
                                  fileName + "\": " + std::strerror(errno);
            throw std::runtime_error(message);
        }
    } else {
        std::string message = "Failed to open file \"" +
                              fileName + "\": " + std::strerror(errno);
        throw std::runtime_error(message);
    }
}