#include <iostream>
#include <vector>

#include <CL/cl.hpp>
#include <CL/opencl.h>


std::vector<std::string> get_devices(){
    std::vector<std::string> devices = OpenCLScanner::getAvailableDevices();
    std::vector<std::string> cpuDevices = CPUScanner::getAvailableDevices();
    devices.insert(devices.cend(), std::make_move_iterator(cpuDevices.cbegin()),
                   std::make_move_iterator(cpuDevices.cend()));
    return devices;
}




std::vector<cl::Device> devices;
int find_devices() {
    std::vector<cl::Platform> platforms; // get all platforms
    std::vector<cl::Device> devices_available;
    int n = 0; // number of available devices
    cl::Platform::get(&platforms);
    for(int i=0; i<(int)platforms.size(); i++) {
        devices_available.clear();
        platforms[i].getDevices(CL_DEVICE_TYPE_ALL, &devices_available);
        if(devices_available.size()==0) continue; // no device found in plattform i
        for(int j=0; j<(int)devices_available.size(); j++) {
            n++;
            devices.push_back(devices_available[j]);
        }
    }
    if(platforms.size()==0||devices.size()==0) {
        std::cout << "Error: There are no OpenCL devices available!" << std::endl;
        return -1;
    }
    for(int i=0; i<n; i++) std::cout << "ID: " << i << ", Device: " << devices[i].getInfo<CL_DEVICE_NAME>() << std::endl;
    return n; // return number of available devices
}

int main() {
    std::string device = get_devices()[0];

    return 0;
}
