//
// Created by Bernadzikovskiy Slavik on 5/15/20.
//

#include "utils.h"

void getConfig(std::map<std::string, std::string> &config, int &threadNum) {
    const std::string file = "../config.dat";
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
                if (key == "threadNum")
                    threadNum = std::stoi(value);
                else
                    config.insert(std::make_pair(key, value));
            }
        }
    }

    std::ifstream readfile(config["infile"]);
    if (!readfile.good())
        throw std::ios_base::failure("Wrong path for readfile!");

    if (threadNum < 1)
        throw std::invalid_argument("Wrong number of indexing threads!");
}


void readFile(const std::string &file, std::string& res){

    std::ifstream raw_file(file, std::ios::binary);
    std::ifstream f(file);
    std::string str;

    if(f) {
        std::ostringstream ss;
        ss << f.rdbuf(); // reading data
        str = ss.str();
    }

    res.reserve(str.size());
    bool isRepOfN = false;
    boost::locale::boundary::ssegment_index resultMap(boost::locale::boundary::word, str.begin(),
                                                      str.end());
    resultMap.rule(boost::locale::boundary::word_any);

    for (boost::locale::boundary::ssegment_index::iterator it = resultMap.begin(), e = resultMap.end();
         it != e; it++) {
        it++;
        res += *it;
    }
}


