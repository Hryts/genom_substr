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
#include "transitionTable.h"

static std::vector<std::pair<std::string, cl::Device>> getAvailableDevices() {
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

        }
    }

    devices.insert(devices.cend(), std::make_move_iterator(accelerators.cbegin()),
                   std::make_move_iterator(accelerators.cend()));
    devices.insert(devices.cend(), std::make_move_iterator(cpus.cbegin()),
                   std::make_move_iterator(cpus.cend()));

    return devices;
}

int main() {
    std::map<std::string, std::string> config;
    readConfig(config, "../config.dat");

    auto PROGRAM_PATH = config["kernel_file"];
    std::string patternsFilePath = config["markers_file"];
    std::string genomeFilePath = config["genome_file"];

    cl::Device device;
    cl::Context context;

    int N;

    device = getAvailableDevices()[0].second;
    context = cl::Context(device);

    auto sourceBytes = readFile(PROGRAM_PATH);
    const cl::Program::Sources sources = {{sourceBytes.data(), sourceBytes.size()}};
    cl::Program program = cl::Program(context, sources);
    cl::CommandQueue queue(context, device);

    try {
        program.build();
    } catch (...) {
        std::cout << "Wasn't able to build OpenCL program";
        std::exit(-1);
    }

    cl::Kernel add = cl::Kernel(program, "add");

    std::vector<size_t> foundIDsResult;

    auto markers = readFile(patternsFilePath);
    std::vector<Node> trie = markersToTrie(markers);
    std::vector<std::vector<char>> vectorizedTrie = trieToVec(trie);

    std::vector<char> input = readFile(genomeFilePath);
    N = input.size();

    std::vector<char> output(N);

    std::vector<char> chs = vectorizedTrie[0];
    std::vector<char> ids = vectorizedTrie[1];
    std::vector<char> firsts = vectorizedTrie[2];
    std::vector<char> seconds = vectorizedTrie[3];
    std::vector<char> thirds = vectorizedTrie[4];
    std::vector<char> fourths = vectorizedTrie[5];

    cl::Buffer inputBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, input.size(), input.data());
    cl::Buffer chsBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, chs.size(), chs.data());
    cl::Buffer idsBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, ids.size(), ids.data());
    cl::Buffer firstsBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, firsts.size(), firsts.data());
    cl::Buffer secondsBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, seconds.size(), seconds.data());
    cl::Buffer thirdsBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, thirds.size(), thirds.data());
    cl::Buffer fourthsBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, fourths.size(), fourths.data());
    cl::Buffer outputBuffer(context, CL_MEM_READ_WRITE, output.size());

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

    queue.enqueueReadBuffer(outputBuffer, CL_TRUE, 0, output.size(), output.data());

    // TODO: write output

    return 0;
}