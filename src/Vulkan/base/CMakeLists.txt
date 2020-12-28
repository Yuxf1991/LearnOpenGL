set(VULKAN_BASE_SRC utils.cpp)

add_library(vulkanBase ${VULKAN_BASE_SRC})
target_link_libraries(vulkanBase vulkan)
