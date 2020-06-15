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
#include "transitionTable.h"


constexpr auto PROGRAM_PATH = "../kernels.cl"; // Path to source file

// TODO: config input data?
// TODO: downloading test data
// TODO: set timer (where?)


static std::vector<std::pair<std::string, cl::Device>> getAvailableDevices() {
    // Hochu gpu
    std::vector<std::pair<std::string, cl::Device>> devices;

    std::vector<std::pair<std::string, cl::Device>> accelerators;
    std::vector<std::pair<std::string, cl::Device>> cpus;

    std::vector<cl::Platform> clplatforms;
    cl::Platform::get(&clplatforms);

    for (const auto& platform : clplatforms) {
        try {
            std::vector<cl::Device> cldevices;
            platform.getDevices(CL_DEVICE_TYPE_ALL, &cldevices);
            for (const auto& device : cldevices) {
                const cl_device_type type = device.getInfo<CL_DEVICE_TYPE>();
                std::string name = device.getInfo<CL_DEVICE_NAME>();
                if (type == CL_DEVICE_TYPE_GPU) {
                    name = "OpenCL:GPU[" +
                           std::to_string(devices.size()) +
                           "]:" + name;
                    devices.emplace_back(name, device);
                } else if (type == CL_DEVICE_TYPE_ACCELERATOR) {
                    name = "OpenCL:ACCELERATOR[" +
                           std::to_string(accelerators.size()) +
                           "]:" + name;
                    accelerators.emplace_back(name, device);
                } else if (type == CL_DEVICE_TYPE_CPU) {
                    name = "OpenCL:CPU[" +
                           std::to_string(cpus.size()) +
                           "]:" + name;
                    cpus.emplace_back(name, device);
                }
            }
        } catch (...) {
            // Ne chipay
        }
    }

    // Add vsilyake gavno (ne gpu)
    devices.insert(devices.cend(), std::make_move_iterator(accelerators.cbegin()),
                   std::make_move_iterator(accelerators.cend()));
    devices.insert(devices.cend(), std::make_move_iterator(cpus.cbegin()),
                   std::make_move_iterator(cpus.cend()));

    return devices;
}

int main() {
    // Initializing OpenCL space
    cl::Device device;
    cl::Context context;
    cl::Kernel pfacKernel;

    int N = 4;

    device = getAvailableDevices()[0].second;
    context = cl::Context(device);

    // TODO: Роздуплитись
    auto sourceBytes = readFile(PROGRAM_PATH);
    const cl::Program::Sources sources = {{sourceBytes.data(), sourceBytes.size()}};
    cl::Program program = cl::Program(context, sources);
    cl::CommandQueue queue(context, device);

    program.build();

    std::cout << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device) << std::endl;

    cl::Kernel add = cl::Kernel(program, "add");

    // Creating an output vector
    std::vector<size_t> foundIDsResult;

    // Initializing pattern trie structure
    std::string patternsFilePath = "../data/markers2.csv";
//    auto* patternTrie = initPatternsTrie(patternsFilePath);
    auto markers = readFile(patternsFilePath);
    std::vector<Node> trie = markersToTrie(markers);
    std::vector<std::vector<char>> vectorizedTrie = trieToVec(trie);
//    std::cout<<patternsFilePath;

    std::vector<char> input;
    input.push_back('A');
    input.push_back('T');
    input.push_back('C');
    input.push_back('T');
    input.push_back('A');
    input.push_back('T');
    input.push_back('T');
    input.push_back('G');

    std::vector<char> output(N);

    for(auto i: vectorizedTrie[0]){
        printf("%c\n", i);
    }

//    std::vector<Node> trie;
//
//    Node top;
//    Node first;
//    Node second;
//    Node third;
//    Node fourth;
//
//    top.ch = 'a';
//    top.id = 1;
//    top.first_child = 1;
//    top.second_child = 2;
//    top.third_child = 3;
//    top.fourth_child = 4;
//
//    first.ch = 'A';
//    first.id = 0;
//    first.first_child = 0;
//    first.second_child = 0;
//    first.third_child = 0;
//    first.fourth_child = 0;
//
//    second.ch = 'C';
//    second.id = 0;
//    second.first_child = 0;
//    second.second_child = 0;
//    second.third_child = 0;
//    second.fourth_child = 0;
//
//    third.ch = 'T';
//    third.id = 0;
//    third.first_child = 0;
//    third.second_child = 0;
//    third.third_child = 0;
//    third.fourth_child = 0;
//
//    fourth.ch = 'G';
//    fourth.id = 1;
//    fourth.first_child = 0;
//    fourth.second_child = 0;
//    fourth.third_child = 0;
//    fourth.fourth_child = 0;
//
//    trie.push_back(top);
//    trie.push_back(first);
//    trie.push_back(second);
//    trie.push_back(third);
//    trie.push_back(fourth);

    std::vector<char> chs = vectorizedTrie[0];
    std::vector<char> idens = vectorizedTrie[1];
    std::vector<char> firsts = vectorizedTrie[2];
    std::vector<char> seconds = vectorizedTrie[3];
    std::vector<char> thirds = vectorizedTrie[4];
    std::vector<char> fourths = vectorizedTrie[5];

    cl::Buffer inputBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, input.size(), input.data());
    cl::Buffer chsBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, chs.size(), chs.data());
    cl::Buffer idsBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, idens.size(), idens.data());
    cl::Buffer firstsBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, firsts.size(), firsts.data());
    cl::Buffer secondsBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, seconds.size(), seconds.data());
    cl::Buffer thirdsBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, thirds.size(), thirds.data());
    cl::Buffer fourthsBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, fourths.size(), fourths.data());
    cl::Buffer outputBuffer(context, CL_MEM_READ_WRITE, output.size());

    // TODO: Read genomes
    // TODO: setArg to kernel

    queue.enqueueWriteBuffer(inputBuffer, CL_TRUE, 0, input.size(), input.data());

    add.setArg(0, static_cast<u_long >(N));
    add.setArg(1, inputBuffer);
    add.setArg(2, outputBuffer);
    add.setArg(3, chsBuffer);
    add.setArg(4, idsBuffer);
    add.setArg(5, firstsBuffer);
    add.setArg(6, secondsBuffer);
    add.setArg(7, thirdsBuffer);
    add.setArg(8, fourthsBuffer);

    queue.enqueueNDRangeKernel(add, cl::NullRange, N, cl::NullRange);

    // Get result back to host.
    queue.enqueueReadBuffer(outputBuffer, CL_TRUE, 0, output.size(), output.data());

//    for(auto &res : output){
//        std::cout << res << std::endl;
//    }

    // TODO: Merge
    // TODO: create output matrix file

    return 0;
}