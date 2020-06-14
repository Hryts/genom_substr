//
// Created by kurlyana on 14.06.2020.
//

#ifndef OPENCL_OPENCL_UTILS_H

#ifdef __APPLE__
#include <OpenCL/cl.hpp>
    #include <OpenCL/opencl.h>
#else
#include <CL/cl.hpp>
#include <CL/opencl.h>
#endif

static std::vector<std::pair<std::string, cl::Device>> getAvailableDevices();

std::vector<std::string> getNeededDevices();

#define OPENCL_OPENCL_UTILS_H

#endif //OPENCL_OPENCL_UTILS_H
