//
// Created by tracy on 2020/12/28.
//

#ifndef COMPUTERGRAPHICSEXERCISE_INITIALIZERS_HPP
#define COMPUTERGRAPHICSEXERCISE_INITIALIZERS_HPP

#include <vulkan/vulkan.h>

namespace cg::vulkan::utils {
inline VkApplicationInfo applicationInfo()
{
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pNext = nullptr;
    return appInfo;
}

inline VkApplicationInfo applicationInfo(const std::string &appName, uint32_t major, uint32_t minor, uint32_t patch)
{
    VkApplicationInfo appInfo = applicationInfo();
    appInfo.pApplicationName = appName.c_str();
    appInfo.applicationVersion = VK_MAKE_VERSION(major, minor, patch);
    appInfo.apiVersion = VK_HEADER_VERSION_COMPLETE;
    return appInfo;
}

inline VkInstanceCreateInfo instanceCreateInfo()
{
    VkInstanceCreateInfo instanceCreateInfo{};
    instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    return instanceCreateInfo;
}

inline VkInstanceCreateInfo instanceCreateInfo(const VkApplicationInfo &appInfo)
{
    VkInstanceCreateInfo createInfo = instanceCreateInfo();
    createInfo.pApplicationInfo = &appInfo;
    return createInfo;
}
}  // namespace cg::vulkan::utils

#endif  // COMPUTERGRAPHICSEXERCISE_INITIALIZERS_HPP
