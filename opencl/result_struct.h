//
// Created by kurlyana on 14.06.2020.
//

#ifndef OPENCL_RESULT_STRUCT_H
#define OPENCL_RESULT_STRUCT_H

#include <set>

class ConcurrentResult {
public:
    ConcurrentResult();
    void merge(ConcurrentResult localRes);
    void addId(size_t id);

private:
    std::set<size_t> res;

};

#endif //OPENCL_RESULT_STRUCT_H
