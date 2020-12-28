//
// Created by tracy on 2020/12/28.
//

#include <iostream>
#include <base/utils.h>

namespace cg::vulkan {
void printAvailableLayers()
{
    std::vector<VkLayerProperties> availableLayers = utils::getAvailableLayers();
    for (const auto &properties : availableLayers) {
        std::cout << properties.layerName << std::endl;
    }
}
}  // namespace cg::vulkan

int main()
{
    cg::vulkan::printAvailableLayers();
}
