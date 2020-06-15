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
//    std::string patternsFilePath = "./data/markers.csv";
//    auto* patternTrie = initPatternsTrie(patternsFilePath);

    std::vector<char> input;
    input.push_back('A');
    input.push_back('B');
    input.push_back('C');
    input.push_back('D');

    std::vector<char> output(N);

    cl::Buffer inputBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, input.size(), input.data());
    cl::Buffer outputBuffer(context, CL_MEM_READ_WRITE, output.size());
    // TODO: Read genomes
    // TODO: setArg to kernel

    queue.enqueueWriteBuffer(inputBuffer, CL_TRUE, 0, input.size(), input.data());

    add.setArg(0, static_cast<u_long >(N));
    add.setArg(1, inputBuffer);
    add.setArg(2, outputBuffer);

    queue.enqueueNDRangeKernel(add, cl::NullRange, N, cl::NullRange);

    // Get result back to host.
    queue.enqueueReadBuffer(outputBuffer, CL_TRUE, 0, output.size(), output.data());

    for(auto &res : output){
        std::cout << res << std::endl;
    }

    // TODO: Merge
    // TODO: create output matrix file

    return 0;
}