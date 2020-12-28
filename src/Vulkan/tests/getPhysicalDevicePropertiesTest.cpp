//
// Created by tracy on 2020/12/28.
//

#include <iostream>

#include <base/utils.h>
#include <base/initializers.hpp>

namespace cg::vulkan {
VkInstance createInstance()
{
    VkInstance instance = VK_NULL_HANDLE;
    VkInstanceCreateInfo instanceCreateInfo = utils::instanceCreateInfo();
    VK_CHECK_RESULT(vkCreateInstance(&instanceCreateInfo, nullptr, &instance));
    return instance;
}

std::vector<VkPhysicalDevice> getPhysicalDevices(VkInstance instance)
{
    std::vector<VkPhysicalDevice> devices;
    if (instance == VK_NULL_HANDLE) {
        return devices;
    }

    uint32_t physicalDeviceCnt = 0;
    VK_CHECK_RESULT(vkEnumeratePhysicalDevices(instance, &physicalDeviceCnt, nullptr));
    devices.resize(physicalDeviceCnt);
    VK_CHECK_RESULT(vkEnumeratePhysicalDevices(instance, &physicalDeviceCnt, devices.data()));
    return devices;
}

void logAllPhysicalDevicesInfo(const std::vector<VkPhysicalDevice> &devices)
{
    int cnt = 0;
    for (const auto &device : devices) {
        std::cout << "GPU: " << cnt << std::endl;
        std::cout << utils::getPhysicalDeviceProperties(device) << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        ++cnt;
    }
}
}  // namespace cg::vulkan

int main()
{
    VkInstance instance = cg::vulkan::createInstance();
    std::vector<VkPhysicalDevice> physicalDevices = cg::vulkan::getPhysicalDevices(instance);
    cg::vulkan::logAllPhysicalDevicesInfo(physicalDevices);
}
