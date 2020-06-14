//
// Created by Bernadzikovskiy Slavik on 14.06.2020.
//

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

#include <archive.h>
#include <archive_entry.h>
#include <boost/filesystem.hpp>

#include "rw_utils.h"

namespace fs = boost::filesystem;

#ifndef USING_BOOST
#define USING_BOOST
#endif

#define ARCHIVE_L ".fasta.gz"
#define ARCHIVE_U ".ZIP"
#define TEXT_FILE_L ".txt"
#define TEXT_FILE_U ".TXT"

#define MAX_TEXT_FILE_SIZE 10000000



void read_archive(const char *archive_file, tbb::flow::broadcast_node& input_node , int max_words) {
    struct archive *archive_ptr;
    struct archive_entry *entry_ptr;
    int ret_signal;

    archive_ptr = archive_read_new();
    archive_read_support_filter_all(archive_ptr);
    archive_read_support_format_all(archive_ptr);

    ret_signal = archive_read_open_filename(archive_ptr, (const char *) archive_file, 10240);
    if (ret_signal != ARCHIVE_OK)
        exit(1);

    while (archive_read_next_header(archive_ptr, &entry_ptr) == ARCHIVE_OK) {
        boost::filesystem::path entry_path = boost::filesystem::path(archive_entry_pathname(entry_ptr));
        if ((entry_path.extension() == TEXT_FILE_L || entry_path.extension() == TEXT_FILE_U) && archive_entry_size(entry_ptr) <= MAX_TEXT_FILE_SIZE) {
            std::string text = std::string(archive_entry_size(entry_ptr), 0);
            ret_signal = archive_read_data(archive_ptr, &text[0], text.size());
            if (ret_signal == ARCHIVE_FATAL || ret_signal ==  ARCHIVE_WARN || ret_signal == ARCHIVE_RETRY)
                continue;
            std::cout << "buffer" << text;
            divide_and_push(&text, &input_node, max_words);
        }
    }
    archive_free(archive_ptr);
}

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

std::unordered_map<size_t, std::string> readCSVMarkers(std::string pathToFile) {
    std::ifstream file(pathToFile, std::ios::binary | std::ios::ate);
    if (file) {

    } else {
        std::string message = "Failed to open file \"" +
                pathToFile + "\": " + std::strerror(errno);
        throw std::runtime_error(message);
    }
}