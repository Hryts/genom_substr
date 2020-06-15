//
// Created by Bernadzikovskiy Slavik on 14.06.2020.
//

#include <fstream>
#include <string>
#include <sstream>

#include "rw_utils.h"

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

void readConfig(std::map<std::string, std::string> &config, const char *file) {
    std::ifstream configFile(file);

    if (!configFile.good())
        throw std::ios_base::failure("Wrong path for config file by a!");

    std::string line, key, value;

    while (getline(configFile, line)) {

        if (line.empty() || line[0] == '#' || line[0] == ' ')
            continue;

        std::istringstream lineStream(line);
        if (std::getline(lineStream, key, '=')) {
            if (std::getline(lineStream, value)) {
                config.insert(std::make_pair(key, value));
            }
        }
    }

    std::ifstream genomeFile(config["genome_file"]);
    if (!genomeFile.good())
        throw std::ios_base::failure("Wrong path for genome file!");

    std::ifstream markerFile(config["markers_file"]);
    if (!markerFile.good())
        throw std::ios_base::failure("Wrong path for marker file!");

    std::ifstream kernelFile(config["kernel_file"]);
    if (!kernelFile.good())
        throw std::ios_base::failure("Wrong path for kernel file!");

    std::ofstream outputFile(config["output_file"]);
    if (!outputFile.good())
        throw std::ios_base::failure("Wrong path for output file!");
}
