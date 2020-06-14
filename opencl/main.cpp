#include <iostream>
#include <vector>
#ifdef __APPLE__
    #include <OpenCL/cl.hpp>
    #include <OpenCL/opencl.h>
#else
    #include <CL/cl.hpp>
    #include <CL/opencl.h>
#endif

constexpr auto PROGRAM_PATH = "."; // Path to source file

static std::vector<std::pair<std::string, cl::Device>> getAvailableDevices_tmp() {
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

std::vector<std::string> getNeededDevices() {
    std::vector<std::string> devices;
    for (auto device : getAvailableDevices_tmp()) {
        devices.emplace_back(device.first);
    }
    return devices;
}

int main() {
    cl::Device device;
    cl::Context context;
    cl::Kernel pfacKernel;

    device = getAvailableDevices_tmp()[0].second;
    context = cl::Context(device);


    // TODO: Роздуплитись
    auto sourceBytes = readFile(PROGRAM_PATH);

    const cl::Program::Sources sources = {{sourceBytes.data(), sourceBytes.size()}};
    cl::Program program = cl::Program(context, sources);

    pfacKernel = cl::Kernel(program, "our_pfac");


    // TODO: Read text

    // TODO: Create output data

    // TODO: Read dict

    return 0;
}
