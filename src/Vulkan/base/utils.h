//
// Created by tracy on 2020/12/28.
//

#ifndef COMPUTERGRAPHICSEXERCISE_UTILS_H
#define COMPUTERGRAPHICSEXERCISE_UTILS_H

#include <cassert>
#include <string>
#include <vector>

#include <vulkan/vulkan.h>

namespace cg::vulkan::utils {
#define VK_CHECK_RESULT(f)                                                                                           \
    {                                                                                                                \
        VkResult res = (f);                                                                                          \
        if (res != VK_SUCCESS) {                                                                                     \
            std::cout << "Fatal : VkResult is \"" << res << "\" in " << __FILE__ << " at line " << __LINE__ << "\n"; \
            assert(res == VK_SUCCESS);                                                                               \
        }                                                                                                            \
    }

std::string getPhysicalDeviceProperties(const VkPhysicalDevice &physicalDevice);

std::vector<VkLayerProperties> getAvailableLayers();
}  // namespace cg::vulkan::utils

#endif  // COMPUTERGRAPHICSEXERCISE_UTILS_H
