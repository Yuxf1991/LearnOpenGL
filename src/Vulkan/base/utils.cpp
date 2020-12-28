//
// Created by tracy on 2020/12/28.
//

#include "utils.h"
#include <string>

namespace cg::vulkan::utils {
inline std::string getFormattedVersion(uint32_t version)
{
    uint32_t major = VK_VERSION_MAJOR(version);
    uint32_t minor = VK_VERSION_MINOR(version);
    uint32_t patch = VK_VERSION_PATCH(version);

    return std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(patch);
}

std::string getPhysicalDeviceProperties(const VkPhysicalDevice &physicalDevice)
{
    VkPhysicalDeviceProperties deviceProperties{};
    vkGetPhysicalDeviceProperties(physicalDevice, &deviceProperties);

    std::string buf;
    buf += ("apiVersion: " + getFormattedVersion(deviceProperties.apiVersion) + "\n");
    buf += ("driverVersion: " + getFormattedVersion(deviceProperties.driverVersion) + "\n");
    buf += ("vendorID: " + std::to_string(deviceProperties.vendorID) + "\n");
    buf += ("deviceID: " + std::to_string(deviceProperties.deviceID) + "\n");
    buf += ("deviceType: " + std::to_string(deviceProperties.deviceType) + "\n");
    buf += ("deviceName: " + std::string(deviceProperties.deviceName) + "\n");
    buf += ("pipelineCacheUUID: " + std::to_string(deviceProperties.pipelineCacheUUID[0]));
    return buf;
}

std::vector<VkLayerProperties> getAvailableLayers()
{
    uint32_t layerCount = 0;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
    return availableLayers;
}
}  // namespace cg::vulkan::utils
