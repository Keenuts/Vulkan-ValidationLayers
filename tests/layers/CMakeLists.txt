# ~~~
# Copyright (c) 2016-2022 Valve Corporation
# Copyright (c) 2016-2022 LunarG, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# ~~~
add_library(VkLayer_device_profile_api MODULE
    ${CMAKE_CURRENT_SOURCE_DIR}/device_profile_api.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/vk_lunarg_device_profile_api_layer.h
    ${PROJECT_SOURCE_DIR}/layers/vk_layer_extension_utils.cpp
)

target_link_libraries(VkLayer_device_profile_api PRIVATE VkLayer_utils)

if (WIN32)
    # Need to use this instead of target_link_options() for older versions of CMake.
    set_target_properties(VkLayer_device_profile_api PROPERTIES
        LINK_FLAGS "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/VkLayer_device_profile_api.def"
    )
elseif(APPLE)
    set_target_properties(VkLayer_device_profile_api PROPERTIES SUFFIX ".dylib")
elseif (LINUX)
    set_target_properties(VkLayer_device_profile_api PROPERTIES
        LINK_FLAGS "-Wl,--version-script=${CMAKE_CURRENT_SOURCE_DIR}/libVkLayer_device_profile_api.map,-Bsymbolic"
    )
endif()

target_include_directories(VkLayer_device_profile_api PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(INTERMEDIATE_FILE "${CMAKE_CURRENT_BINARY_DIR}/profiling.json")

if (WIN32)
    set(JSON_LIBRARY_PATH ".\\\\VkLayer_device_profile_api.dll")
elseif(APPLE)
    set(JSON_LIBRARY_PATH "./libVkLayer_device_profile_api.dylib")
else()
    set(JSON_LIBRARY_PATH "./libVkLayer_device_profile_api.so")
endif()

set(JSON_API_VERSION ${VulkanHeaders_VERSION})

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/VkLayer_device_profile_api.json.in" ${INTERMEDIATE_FILE} @ONLY)

# It's much simpler for development if the device profile layer is in the same location as the validation layer
add_custom_command(TARGET VkLayer_device_profile_api POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:VkLayer_device_profile_api> $<TARGET_FILE_DIR:VkLayer_khronos_validation>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${INTERMEDIATE_FILE} $<TARGET_FILE_DIR:VkLayer_khronos_validation>/"VkLayer_device_profile_api.json"
)
