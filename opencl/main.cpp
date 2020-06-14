#include <iostream>
#include <vector>

#ifdef __APPLE__
    #include <OpenCL/cl.hpp>
    #include <OpenCL/opencl.h>
#else
    #include <CL/cl.hpp>
    #include <CL/opencl.h>
#include <chrono>
#include <set>

#endif

#include "rw_utils.h"
#include "opencl_utils.h"
#include "patterns_trie.h"


constexpr auto PROGRAM_PATH = "."; // Path to source file

// TODO: config input data?
// TODO: downloading test data
// TODO: set timer (where?)

int main() {
    // Initializing OpenCL space
    cl::Device device;
    cl::Context context;
    cl::Kernel pfacKernel;

    device = getAvailableDevices()[0].second;
    context = cl::Context(device);

    // TODO: Роздуплитись
    auto sourceBytes = readFile(PROGRAM_PATH);
    const cl::Program::Sources sources = {{sourceBytes.data(), sourceBytes.size()}};
    cl::Program program = cl::Program(context, sources);

    // Creating an output vector
    std::vector<size_t> foundIDsResult;

    // Initializing pattern trie structure
    std::string patternsFilePath = "./data/markers.csv";
    auto* patternTrie = initPatternsTrie(patternsFilePath);

    // TODO: Read genomes
    // TODO: setArg to kernel

    pfacKernel = cl::Kernel(program, "our_pfac");

    // TODO: Merge
    // TODO: create output matrix file

    return 0;
}