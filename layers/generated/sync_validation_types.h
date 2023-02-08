// *** THIS FILE IS GENERATED - DO NOT EDIT ***
// See helper_file_generator.py for modifications


/***************************************************************************
 *
 * Copyright (c) 2015-2023 The Khronos Group Inc.
 * Copyright (c) 2015-2023 Valve Corporation
 * Copyright (c) 2015-2023 LunarG, Inc.
 * Copyright (c) 2015-2023 Google Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ****************************************************************************/

#pragma once

#include <array>
#include <bitset>
#include <map>
#include <stdint.h>
#include <vulkan/vulkan.h>
#include "vk_layer_data.h"
using SyncStageAccessFlags = std::bitset<128>;

// clang-format off

// Fake stages and accesses for acquire present support
static const VkPipelineStageFlagBits2 VK_PIPELINE_STAGE_2_PRESENT_ENGINE_BIT_SYNCVAL = 0x0000040000000000ULL;
static const VkAccessFlagBits2 VK_ACCESS_2_PRESENT_ACQUIRE_READ_BIT_SYNCVAL = 0x0000400000000000ULL;
static const VkAccessFlagBits2 VK_ACCESS_2_PRESENT_PRESENTED_BIT_SYNCVAL = 0x0000800000000000ULL;

// Unique number for each  stage/access combination
enum SyncStageAccessIndex {
    SYNC_ACCESS_INDEX_NONE = 0,
    SYNC_DRAW_INDIRECT_INDIRECT_COMMAND_READ = 1,
    SYNC_DRAW_INDIRECT_TRANSFORM_FEEDBACK_COUNTER_READ_EXT = 2,
    SYNC_INDEX_INPUT_INDEX_READ = 3,
    SYNC_VERTEX_ATTRIBUTE_INPUT_VERTEX_ATTRIBUTE_READ = 4,
    SYNC_VERTEX_SHADER_ACCELERATION_STRUCTURE_READ = 5,
    SYNC_VERTEX_SHADER_DESCRIPTOR_BUFFER_READ_EXT = 6,
    SYNC_VERTEX_SHADER_SHADER_SAMPLED_READ = 7,
    SYNC_VERTEX_SHADER_SHADER_STORAGE_READ = 8,
    SYNC_VERTEX_SHADER_SHADER_STORAGE_WRITE = 9,
    SYNC_VERTEX_SHADER_UNIFORM_READ = 10,
    SYNC_TESSELLATION_CONTROL_SHADER_ACCELERATION_STRUCTURE_READ = 11,
    SYNC_TESSELLATION_CONTROL_SHADER_DESCRIPTOR_BUFFER_READ_EXT = 12,
    SYNC_TESSELLATION_CONTROL_SHADER_SHADER_SAMPLED_READ = 13,
    SYNC_TESSELLATION_CONTROL_SHADER_SHADER_STORAGE_READ = 14,
    SYNC_TESSELLATION_CONTROL_SHADER_SHADER_STORAGE_WRITE = 15,
    SYNC_TESSELLATION_CONTROL_SHADER_UNIFORM_READ = 16,
    SYNC_TESSELLATION_EVALUATION_SHADER_ACCELERATION_STRUCTURE_READ = 17,
    SYNC_TESSELLATION_EVALUATION_SHADER_DESCRIPTOR_BUFFER_READ_EXT = 18,
    SYNC_TESSELLATION_EVALUATION_SHADER_SHADER_SAMPLED_READ = 19,
    SYNC_TESSELLATION_EVALUATION_SHADER_SHADER_STORAGE_READ = 20,
    SYNC_TESSELLATION_EVALUATION_SHADER_SHADER_STORAGE_WRITE = 21,
    SYNC_TESSELLATION_EVALUATION_SHADER_UNIFORM_READ = 22,
    SYNC_GEOMETRY_SHADER_ACCELERATION_STRUCTURE_READ = 23,
    SYNC_GEOMETRY_SHADER_DESCRIPTOR_BUFFER_READ_EXT = 24,
    SYNC_GEOMETRY_SHADER_SHADER_SAMPLED_READ = 25,
    SYNC_GEOMETRY_SHADER_SHADER_STORAGE_READ = 26,
    SYNC_GEOMETRY_SHADER_SHADER_STORAGE_WRITE = 27,
    SYNC_GEOMETRY_SHADER_UNIFORM_READ = 28,
    SYNC_TRANSFORM_FEEDBACK_EXT_TRANSFORM_FEEDBACK_COUNTER_READ_EXT = 29,
    SYNC_TRANSFORM_FEEDBACK_EXT_TRANSFORM_FEEDBACK_COUNTER_WRITE_EXT = 30,
    SYNC_TRANSFORM_FEEDBACK_EXT_TRANSFORM_FEEDBACK_WRITE_EXT = 31,
    SYNC_FRAGMENT_DENSITY_PROCESS_EXT_FRAGMENT_DENSITY_MAP_READ_EXT = 32,
    SYNC_TASK_SHADER_EXT_ACCELERATION_STRUCTURE_READ = 33,
    SYNC_TASK_SHADER_EXT_DESCRIPTOR_BUFFER_READ_EXT = 34,
    SYNC_TASK_SHADER_EXT_SHADER_SAMPLED_READ = 35,
    SYNC_TASK_SHADER_EXT_SHADER_STORAGE_READ = 36,
    SYNC_TASK_SHADER_EXT_SHADER_STORAGE_WRITE = 37,
    SYNC_TASK_SHADER_EXT_UNIFORM_READ = 38,
    SYNC_MESH_SHADER_EXT_ACCELERATION_STRUCTURE_READ = 39,
    SYNC_MESH_SHADER_EXT_DESCRIPTOR_BUFFER_READ_EXT = 40,
    SYNC_MESH_SHADER_EXT_SHADER_SAMPLED_READ = 41,
    SYNC_MESH_SHADER_EXT_SHADER_STORAGE_READ = 42,
    SYNC_MESH_SHADER_EXT_SHADER_STORAGE_WRITE = 43,
    SYNC_MESH_SHADER_EXT_UNIFORM_READ = 44,
    SYNC_FRAGMENT_SHADING_RATE_ATTACHMENT_FRAGMENT_SHADING_RATE_ATTACHMENT_READ = 45,
    SYNC_EARLY_FRAGMENT_TESTS_DEPTH_STENCIL_ATTACHMENT_READ = 46,
    SYNC_EARLY_FRAGMENT_TESTS_DEPTH_STENCIL_ATTACHMENT_WRITE = 47,
    SYNC_FRAGMENT_SHADER_ACCELERATION_STRUCTURE_READ = 48,
    SYNC_FRAGMENT_SHADER_DESCRIPTOR_BUFFER_READ_EXT = 49,
    SYNC_FRAGMENT_SHADER_INPUT_ATTACHMENT_READ = 50,
    SYNC_FRAGMENT_SHADER_SHADER_SAMPLED_READ = 51,
    SYNC_FRAGMENT_SHADER_SHADER_STORAGE_READ = 52,
    SYNC_FRAGMENT_SHADER_SHADER_STORAGE_WRITE = 53,
    SYNC_FRAGMENT_SHADER_UNIFORM_READ = 54,
    SYNC_LATE_FRAGMENT_TESTS_DEPTH_STENCIL_ATTACHMENT_READ = 55,
    SYNC_LATE_FRAGMENT_TESTS_DEPTH_STENCIL_ATTACHMENT_WRITE = 56,
    SYNC_COLOR_ATTACHMENT_OUTPUT_COLOR_ATTACHMENT_READ = 57,
    SYNC_COLOR_ATTACHMENT_OUTPUT_COLOR_ATTACHMENT_READ_NONCOHERENT_EXT = 58,
    SYNC_COLOR_ATTACHMENT_OUTPUT_COLOR_ATTACHMENT_WRITE = 59,
    SYNC_COMPUTE_SHADER_ACCELERATION_STRUCTURE_READ = 60,
    SYNC_COMPUTE_SHADER_DESCRIPTOR_BUFFER_READ_EXT = 61,
    SYNC_COMPUTE_SHADER_SHADER_SAMPLED_READ = 62,
    SYNC_COMPUTE_SHADER_SHADER_STORAGE_READ = 63,
    SYNC_COMPUTE_SHADER_SHADER_STORAGE_WRITE = 64,
    SYNC_COMPUTE_SHADER_UNIFORM_READ = 65,
    SYNC_COPY_TRANSFER_READ = 66,
    SYNC_COPY_TRANSFER_WRITE = 67,
    SYNC_RESOLVE_TRANSFER_READ = 68,
    SYNC_RESOLVE_TRANSFER_WRITE = 69,
    SYNC_BLIT_TRANSFER_READ = 70,
    SYNC_BLIT_TRANSFER_WRITE = 71,
    SYNC_CLEAR_TRANSFER_WRITE = 72,
    SYNC_COMMAND_PREPROCESS_NV_COMMAND_PREPROCESS_READ_NV = 73,
    SYNC_COMMAND_PREPROCESS_NV_COMMAND_PREPROCESS_WRITE_NV = 74,
    SYNC_CONDITIONAL_RENDERING_EXT_CONDITIONAL_RENDERING_READ_EXT = 75,
    SYNC_RAY_TRACING_SHADER_ACCELERATION_STRUCTURE_READ = 76,
    SYNC_RAY_TRACING_SHADER_DESCRIPTOR_BUFFER_READ_EXT = 77,
    SYNC_RAY_TRACING_SHADER_SHADER_BINDING_TABLE_READ = 78,
    SYNC_RAY_TRACING_SHADER_SHADER_SAMPLED_READ = 79,
    SYNC_RAY_TRACING_SHADER_SHADER_STORAGE_READ = 80,
    SYNC_RAY_TRACING_SHADER_SHADER_STORAGE_WRITE = 81,
    SYNC_RAY_TRACING_SHADER_UNIFORM_READ = 82,
    SYNC_ACCELERATION_STRUCTURE_BUILD_ACCELERATION_STRUCTURE_READ = 83,
    SYNC_ACCELERATION_STRUCTURE_BUILD_ACCELERATION_STRUCTURE_WRITE = 84,
    SYNC_ACCELERATION_STRUCTURE_BUILD_INDIRECT_COMMAND_READ = 85,
    SYNC_ACCELERATION_STRUCTURE_BUILD_MICROMAP_READ_EXT = 86,
    SYNC_ACCELERATION_STRUCTURE_BUILD_SHADER_SAMPLED_READ = 87,
    SYNC_ACCELERATION_STRUCTURE_BUILD_SHADER_STORAGE_READ = 88,
    SYNC_ACCELERATION_STRUCTURE_BUILD_TRANSFER_READ = 89,
    SYNC_ACCELERATION_STRUCTURE_BUILD_TRANSFER_WRITE = 90,
    SYNC_ACCELERATION_STRUCTURE_BUILD_UNIFORM_READ = 91,
    SYNC_ACCELERATION_STRUCTURE_COPY_TRANSFER_READ = 92,
    SYNC_ACCELERATION_STRUCTURE_COPY_TRANSFER_WRITE = 93,
    SYNC_VIDEO_DECODE_VIDEO_DECODE_READ = 94,
    SYNC_VIDEO_DECODE_VIDEO_DECODE_WRITE = 95,
    SYNC_VIDEO_ENCODE_VIDEO_ENCODE_READ = 96,
    SYNC_VIDEO_ENCODE_VIDEO_ENCODE_WRITE = 97,
    SYNC_SUBPASS_SHADING_HUAWEI_INPUT_ATTACHMENT_READ = 98,
    SYNC_OPTICAL_FLOW_NV_OPTICAL_FLOW_READ_NV = 99,
    SYNC_OPTICAL_FLOW_NV_OPTICAL_FLOW_WRITE_NV = 100,
    SYNC_MICROMAP_BUILD_EXT_MICROMAP_READ_EXT = 101,
    SYNC_MICROMAP_BUILD_EXT_MICROMAP_WRITE_EXT = 102,
    SYNC_HOST_HOST_READ = 103,
    SYNC_HOST_HOST_WRITE = 104,
    SYNC_PRESENT_ENGINE_SYNCVAL_PRESENT_ACQUIRE_READ_SYNCVAL = 105,
    SYNC_PRESENT_ENGINE_SYNCVAL_PRESENT_PRESENTED_SYNCVAL = 106,
    SYNC_IMAGE_LAYOUT_TRANSITION = 107,
    SYNC_QUEUE_FAMILY_OWNERSHIP_TRANSFER = 108,
};

// Unique bit for each  stage/access combination
static const SyncStageAccessFlags SYNC_DRAW_INDIRECT_INDIRECT_COMMAND_READ_BIT = (SyncStageAccessFlags(1) << SYNC_DRAW_INDIRECT_INDIRECT_COMMAND_READ);
static const SyncStageAccessFlags SYNC_DRAW_INDIRECT_TRANSFORM_FEEDBACK_COUNTER_READ_BIT_EXT = (SyncStageAccessFlags(1) << SYNC_DRAW_INDIRECT_TRANSFORM_FEEDBACK_COUNTER_READ_EXT);
static const SyncStageAccessFlags SYNC_INDEX_INPUT_INDEX_READ_BIT = (SyncStageAccessFlags(1) << SYNC_INDEX_INPUT_INDEX_READ);
static const SyncStageAccessFlags SYNC_VERTEX_ATTRIBUTE_INPUT_VERTEX_ATTRIBUTE_READ_BIT = (SyncStageAccessFlags(1) << SYNC_VERTEX_ATTRIBUTE_INPUT_VERTEX_ATTRIBUTE_READ);
static const SyncStageAccessFlags SYNC_VERTEX_SHADER_ACCELERATION_STRUCTURE_READ_BIT = (SyncStageAccessFlags(1) << SYNC_VERTEX_SHADER_ACCELERATION_STRUCTURE_READ);
static const SyncStageAccessFlags SYNC_VERTEX_SHADER_DESCRIPTOR_BUFFER_READ_BIT_EXT = (SyncStageAccessFlags(1) << SYNC_VERTEX_SHADER_DESCRIPTOR_BUFFER_READ_EXT);
static const SyncStageAccessFlags SYNC_VERTEX_SHADER_SHADER_SAMPLED_READ_BIT = (SyncStageAccessFlags(1) << SYNC_VERTEX_SHADER_SHADER_SAMPLED_READ);
static const SyncStageAccessFlags SYNC_VERTEX_SHADER_SHADER_STORAGE_READ_BIT = (SyncStageAccessFlags(1) << SYNC_VERTEX_SHADER_SHADER_STORAGE_READ);
static const SyncStageAccessFlags SYNC_VERTEX_SHADER_SHADER_STORAGE_WRITE_BIT = (SyncStageAccessFlags(1) << SYNC_VERTEX_SHADER_SHADER_STORAGE_WRITE);
static const SyncStageAccessFlags SYNC_VERTEX_SHADER_UNIFORM_READ_BIT = (SyncStageAccessFlags(1) << SYNC_VERTEX_SHADER_UNIFORM_READ);
static const SyncStageAccessFlags SYNC_TESSELLATION_CONTROL_SHADER_ACCELERATION_STRUCTURE_READ_BIT = (SyncStageAccessFlags(1) << SYNC_TESSELLATION_CONTROL_SHADER_ACCELERATION_STRUCTURE_READ);
static const SyncStageAccessFlags SYNC_TESSELLATION_CONTROL_SHADER_DESCRIPTOR_BUFFER_READ_BIT_EXT = (SyncStageAccessFlags(1) << SYNC_TESSELLATION_CONTROL_SHADER_DESCRIPTOR_BUFFER_READ_EXT);
static const SyncStageAccessFlags SYNC_TESSELLATION_CONTROL_SHADER_SHADER_SAMPLED_READ_BIT = (SyncStageAccessFlags(1) << SYNC_TESSELLATION_CONTROL_SHADER_SHADER_SAMPLED_READ);
static const SyncStageAccessFlags SYNC_TESSELLATION_CONTROL_SHADER_SHADER_STORAGE_READ_BIT = (SyncStageAccessFlags(1) << SYNC_TESSELLATION_CONTROL_SHADER_SHADER_STORAGE_READ);
static const SyncStageAccessFlags SYNC_TESSELLATION_CONTROL_SHADER_SHADER_STORAGE_WRITE_BIT = (SyncStageAccessFlags(1) << SYNC_TESSELLATION_CONTROL_SHADER_SHADER_STORAGE_WRITE);
static const SyncStageAccessFlags SYNC_TESSELLATION_CONTROL_SHADER_UNIFORM_READ_BIT = (SyncStageAccessFlags(1) << SYNC_TESSELLATION_CONTROL_SHADER_UNIFORM_READ);
static const SyncStageAccessFlags SYNC_TESSELLATION_EVALUATION_SHADER_ACCELERATION_STRUCTURE_READ_BIT = (SyncStageAccessFlags(1) << SYNC_TESSELLATION_EVALUATION_SHADER_ACCELERATION_STRUCTURE_READ);
static const SyncStageAccessFlags SYNC_TESSELLATION_EVALUATION_SHADER_DESCRIPTOR_BUFFER_READ_BIT_EXT = (SyncStageAccessFlags(1) << SYNC_TESSELLATION_EVALUATION_SHADER_DESCRIPTOR_BUFFER_READ_EXT);
static const SyncStageAccessFlags SYNC_TESSELLATION_EVALUATION_SHADER_SHADER_SAMPLED_READ_BIT = (SyncStageAccessFlags(1) << SYNC_TESSELLATION_EVALUATION_SHADER_SHADER_SAMPLED_READ);
static const SyncStageAccessFlags SYNC_TESSELLATION_EVALUATION_SHADER_SHADER_STORAGE_READ_BIT = (SyncStageAccessFlags(1) << SYNC_TESSELLATION_EVALUATION_SHADER_SHADER_STORAGE_READ);
static const SyncStageAccessFlags SYNC_TESSELLATION_EVALUATION_SHADER_SHADER_STORAGE_WRITE_BIT = (SyncStageAccessFlags(1) << SYNC_TESSELLATION_EVALUATION_SHADER_SHADER_STORAGE_WRITE);
static const SyncStageAccessFlags SYNC_TESSELLATION_EVALUATION_SHADER_UNIFORM_READ_BIT = (SyncStageAccessFlags(1) << SYNC_TESSELLATION_EVALUATION_SHADER_UNIFORM_READ);
static const SyncStageAccessFlags SYNC_GEOMETRY_SHADER_ACCELERATION_STRUCTURE_READ_BIT = (SyncStageAccessFlags(1) << SYNC_GEOMETRY_SHADER_ACCELERATION_STRUCTURE_READ);
static const SyncStageAccessFlags SYNC_GEOMETRY_SHADER_DESCRIPTOR_BUFFER_READ_BIT_EXT = (SyncStageAccessFlags(1) << SYNC_GEOMETRY_SHADER_DESCRIPTOR_BUFFER_READ_EXT);
static const SyncStageAccessFlags SYNC_GEOMETRY_SHADER_SHADER_SAMPLED_READ_BIT = (SyncStageAccessFlags(1) << SYNC_GEOMETRY_SHADER_SHADER_SAMPLED_READ);
static const SyncStageAccessFlags SYNC_GEOMETRY_SHADER_SHADER_STORAGE_READ_BIT = (SyncStageAccessFlags(1) << SYNC_GEOMETRY_SHADER_SHADER_STORAGE_READ);
static const SyncStageAccessFlags SYNC_GEOMETRY_SHADER_SHADER_STORAGE_WRITE_BIT = (SyncStageAccessFlags(1) << SYNC_GEOMETRY_SHADER_SHADER_STORAGE_WRITE);
static const SyncStageAccessFlags SYNC_GEOMETRY_SHADER_UNIFORM_READ_BIT = (SyncStageAccessFlags(1) << SYNC_GEOMETRY_SHADER_UNIFORM_READ);
static const SyncStageAccessFlags SYNC_TRANSFORM_FEEDBACK_BIT_EXT_TRANSFORM_FEEDBACK_COUNTER_READ_BIT_EXT = (SyncStageAccessFlags(1) << SYNC_TRANSFORM_FEEDBACK_EXT_TRANSFORM_FEEDBACK_COUNTER_READ_EXT);
static const SyncStageAccessFlags SYNC_TRANSFORM_FEEDBACK_BIT_EXT_TRANSFORM_FEEDBACK_COUNTER_WRITE_BIT_EXT = (SyncStageAccessFlags(1) << SYNC_TRANSFORM_FEEDBACK_EXT_TRANSFORM_FEEDBACK_COUNTER_WRITE_EXT);
static const SyncStageAccessFlags SYNC_TRANSFORM_FEEDBACK_BIT_EXT_TRANSFORM_FEEDBACK_WRITE_BIT_EXT = (SyncStageAccessFlags(1) << SYNC_TRANSFORM_FEEDBACK_EXT_TRANSFORM_FEEDBACK_WRITE_EXT);
static const SyncStageAccessFlags SYNC_FRAGMENT_DENSITY_PROCESS_BIT_EXT_FRAGMENT_DENSITY_MAP_READ_BIT_EXT = (SyncStageAccessFlags(1) << SYNC_FRAGMENT_DENSITY_PROCESS_EXT_FRAGMENT_DENSITY_MAP_READ_EXT);
static const SyncStageAccessFlags SYNC_TASK_SHADER_EXT_ACCELERATION_STRUCTURE_READ_BIT = (SyncStageAccessFlags(1) << SYNC_TASK_SHADER_EXT_ACCELERATION_STRUCTURE_READ);
static const SyncStageAccessFlags SYNC_TASK_SHADER_BIT_EXT_DESCRIPTOR_BUFFER_READ_BIT_EXT = (SyncStageAccessFlags(1) << SYNC_TASK_SHADER_EXT_DESCRIPTOR_BUFFER_READ_EXT);
static const SyncStageAccessFlags SYNC_TASK_SHADER_EXT_SHADER_SAMPLED_READ_BIT = (SyncStageAccessFlags(1) << SYNC_TASK_SHADER_EXT_SHADER_SAMPLED_READ);
static const SyncStageAccessFlags SYNC_TASK_SHADER_EXT_SHADER_STORAGE_READ_BIT = (SyncStageAccessFlags(1) << SYNC_TASK_SHADER_EXT_SHADER_STORAGE_READ);
static const SyncStageAccessFlags SYNC_TASK_SHADER_EXT_SHADER_STORAGE_WRITE_BIT = (SyncStageAccessFlags(1) << SYNC_TASK_SHADER_EXT_SHADER_STORAGE_WRITE);
static const SyncStageAccessFlags SYNC_TASK_SHADER_EXT_UNIFORM_READ_BIT = (SyncStageAccessFlags(1) << SYNC_TASK_SHADER_EXT_UNIFORM_READ);
static const SyncStageAccessFlags SYNC_MESH_SHADER_EXT_ACCELERATION_STRUCTURE_READ_BIT = (SyncStageAccessFlags(1) << SYNC_MESH_SHADER_EXT_ACCELERATION_STRUCTURE_READ);
static const SyncStageAccessFlags SYNC_MESH_SHADER_BIT_EXT_DESCRIPTOR_BUFFER_READ_BIT_EXT = (SyncStageAccessFlags(1) << SYNC_MESH_SHADER_EXT_DESCRIPTOR_BUFFER_READ_EXT);
static const SyncStageAccessFlags SYNC_MESH_SHADER_EXT_SHADER_SAMPLED_READ_BIT = (SyncStageAccessFlags(1) << SYNC_MESH_SHADER_EXT_SHADER_SAMPLED_READ);
static const SyncStageAccessFlags SYNC_MESH_SHADER_EXT_SHADER_STORAGE_READ_BIT = (SyncStageAccessFlags(1) << SYNC_MESH_SHADER_EXT_SHADER_STORAGE_READ);
static const SyncStageAccessFlags SYNC_MESH_SHADER_EXT_SHADER_STORAGE_WRITE_BIT = (SyncStageAccessFlags(1) << SYNC_MESH_SHADER_EXT_SHADER_STORAGE_WRITE);
static const SyncStageAccessFlags SYNC_MESH_SHADER_EXT_UNIFORM_READ_BIT = (SyncStageAccessFlags(1) << SYNC_MESH_SHADER_EXT_UNIFORM_READ);
static const SyncStageAccessFlags SYNC_FRAGMENT_SHADING_RATE_ATTACHMENT_FRAGMENT_SHADING_RATE_ATTACHMENT_READ_BIT = (SyncStageAccessFlags(1) << SYNC_FRAGMENT_SHADING_RATE_ATTACHMENT_FRAGMENT_SHADING_RATE_ATTACHMENT_READ);
static const SyncStageAccessFlags SYNC_EARLY_FRAGMENT_TESTS_DEPTH_STENCIL_ATTACHMENT_READ_BIT = (SyncStageAccessFlags(1) << SYNC_EARLY_FRAGMENT_TESTS_DEPTH_STENCIL_ATTACHMENT_READ);
static const SyncStageAccessFlags SYNC_EARLY_FRAGMENT_TESTS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT = (SyncStageAccessFlags(1) << SYNC_EARLY_FRAGMENT_TESTS_DEPTH_STENCIL_ATTACHMENT_WRITE);
static const SyncStageAccessFlags SYNC_FRAGMENT_SHADER_ACCELERATION_STRUCTURE_READ_BIT = (SyncStageAccessFlags(1) << SYNC_FRAGMENT_SHADER_ACCELERATION_STRUCTURE_READ);
static const SyncStageAccessFlags SYNC_FRAGMENT_SHADER_DESCRIPTOR_BUFFER_READ_BIT_EXT = (SyncStageAccessFlags(1) << SYNC_FRAGMENT_SHADER_DESCRIPTOR_BUFFER_READ_EXT);
static const SyncStageAccessFlags SYNC_FRAGMENT_SHADER_INPUT_ATTACHMENT_READ_BIT = (SyncStageAccessFlags(1) << SYNC_FRAGMENT_SHADER_INPUT_ATTACHMENT_READ);
static const SyncStageAccessFlags SYNC_FRAGMENT_SHADER_SHADER_SAMPLED_READ_BIT = (SyncStageAccessFlags(1) << SYNC_FRAGMENT_SHADER_SHADER_SAMPLED_READ);
static const SyncStageAccessFlags SYNC_FRAGMENT_SHADER_SHADER_STORAGE_READ_BIT = (SyncStageAccessFlags(1) << SYNC_FRAGMENT_SHADER_SHADER_STORAGE_READ);
static const SyncStageAccessFlags SYNC_FRAGMENT_SHADER_SHADER_STORAGE_WRITE_BIT = (SyncStageAccessFlags(1) << SYNC_FRAGMENT_SHADER_SHADER_STORAGE_WRITE);
static const SyncStageAccessFlags SYNC_FRAGMENT_SHADER_UNIFORM_READ_BIT = (SyncStageAccessFlags(1) << SYNC_FRAGMENT_SHADER_UNIFORM_READ);
static const SyncStageAccessFlags SYNC_LATE_FRAGMENT_TESTS_DEPTH_STENCIL_ATTACHMENT_READ_BIT = (SyncStageAccessFlags(1) << SYNC_LATE_FRAGMENT_TESTS_DEPTH_STENCIL_ATTACHMENT_READ);
static const SyncStageAccessFlags SYNC_LATE_FRAGMENT_TESTS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT = (SyncStageAccessFlags(1) << SYNC_LATE_FRAGMENT_TESTS_DEPTH_STENCIL_ATTACHMENT_WRITE);
static const SyncStageAccessFlags SYNC_COLOR_ATTACHMENT_OUTPUT_COLOR_ATTACHMENT_READ_BIT = (SyncStageAccessFlags(1) << SYNC_COLOR_ATTACHMENT_OUTPUT_COLOR_ATTACHMENT_READ);
static const SyncStageAccessFlags SYNC_COLOR_ATTACHMENT_OUTPUT_COLOR_ATTACHMENT_READ_NONCOHERENT_BIT_EXT = (SyncStageAccessFlags(1) << SYNC_COLOR_ATTACHMENT_OUTPUT_COLOR_ATTACHMENT_READ_NONCOHERENT_EXT);
static const SyncStageAccessFlags SYNC_COLOR_ATTACHMENT_OUTPUT_COLOR_ATTACHMENT_WRITE_BIT = (SyncStageAccessFlags(1) << SYNC_COLOR_ATTACHMENT_OUTPUT_COLOR_ATTACHMENT_WRITE);
static const SyncStageAccessFlags SYNC_COMPUTE_SHADER_ACCELERATION_STRUCTURE_READ_BIT = (SyncStageAccessFlags(1) << SYNC_COMPUTE_SHADER_ACCELERATION_STRUCTURE_READ);
static const SyncStageAccessFlags SYNC_COMPUTE_SHADER_DESCRIPTOR_BUFFER_READ_BIT_EXT = (SyncStageAccessFlags(1) << SYNC_COMPUTE_SHADER_DESCRIPTOR_BUFFER_READ_EXT);
static const SyncStageAccessFlags SYNC_COMPUTE_SHADER_SHADER_SAMPLED_READ_BIT = (SyncStageAccessFlags(1) << SYNC_COMPUTE_SHADER_SHADER_SAMPLED_READ);
static const SyncStageAccessFlags SYNC_COMPUTE_SHADER_SHADER_STORAGE_READ_BIT = (SyncStageAccessFlags(1) << SYNC_COMPUTE_SHADER_SHADER_STORAGE_READ);
static const SyncStageAccessFlags SYNC_COMPUTE_SHADER_SHADER_STORAGE_WRITE_BIT = (SyncStageAccessFlags(1) << SYNC_COMPUTE_SHADER_SHADER_STORAGE_WRITE);
static const SyncStageAccessFlags SYNC_COMPUTE_SHADER_UNIFORM_READ_BIT = (SyncStageAccessFlags(1) << SYNC_COMPUTE_SHADER_UNIFORM_READ);
static const SyncStageAccessFlags SYNC_COPY_TRANSFER_READ_BIT = (SyncStageAccessFlags(1) << SYNC_COPY_TRANSFER_READ);
static const SyncStageAccessFlags SYNC_COPY_TRANSFER_WRITE_BIT = (SyncStageAccessFlags(1) << SYNC_COPY_TRANSFER_WRITE);
static const SyncStageAccessFlags SYNC_RESOLVE_TRANSFER_READ_BIT = (SyncStageAccessFlags(1) << SYNC_RESOLVE_TRANSFER_READ);
static const SyncStageAccessFlags SYNC_RESOLVE_TRANSFER_WRITE_BIT = (SyncStageAccessFlags(1) << SYNC_RESOLVE_TRANSFER_WRITE);
static const SyncStageAccessFlags SYNC_BLIT_TRANSFER_READ_BIT = (SyncStageAccessFlags(1) << SYNC_BLIT_TRANSFER_READ);
static const SyncStageAccessFlags SYNC_BLIT_TRANSFER_WRITE_BIT = (SyncStageAccessFlags(1) << SYNC_BLIT_TRANSFER_WRITE);
static const SyncStageAccessFlags SYNC_CLEAR_TRANSFER_WRITE_BIT = (SyncStageAccessFlags(1) << SYNC_CLEAR_TRANSFER_WRITE);
static const SyncStageAccessFlags SYNC_COMMAND_PREPROCESS_BIT_NV_COMMAND_PREPROCESS_READ_BIT_NV = (SyncStageAccessFlags(1) << SYNC_COMMAND_PREPROCESS_NV_COMMAND_PREPROCESS_READ_NV);
static const SyncStageAccessFlags SYNC_COMMAND_PREPROCESS_BIT_NV_COMMAND_PREPROCESS_WRITE_BIT_NV = (SyncStageAccessFlags(1) << SYNC_COMMAND_PREPROCESS_NV_COMMAND_PREPROCESS_WRITE_NV);
static const SyncStageAccessFlags SYNC_CONDITIONAL_RENDERING_BIT_EXT_CONDITIONAL_RENDERING_READ_BIT_EXT = (SyncStageAccessFlags(1) << SYNC_CONDITIONAL_RENDERING_EXT_CONDITIONAL_RENDERING_READ_EXT);
static const SyncStageAccessFlags SYNC_RAY_TRACING_SHADER_ACCELERATION_STRUCTURE_READ_BIT = (SyncStageAccessFlags(1) << SYNC_RAY_TRACING_SHADER_ACCELERATION_STRUCTURE_READ);
static const SyncStageAccessFlags SYNC_RAY_TRACING_SHADER_DESCRIPTOR_BUFFER_READ_BIT_EXT = (SyncStageAccessFlags(1) << SYNC_RAY_TRACING_SHADER_DESCRIPTOR_BUFFER_READ_EXT);
static const SyncStageAccessFlags SYNC_RAY_TRACING_SHADER_SHADER_BINDING_TABLE_READ_BIT = (SyncStageAccessFlags(1) << SYNC_RAY_TRACING_SHADER_SHADER_BINDING_TABLE_READ);
static const SyncStageAccessFlags SYNC_RAY_TRACING_SHADER_SHADER_SAMPLED_READ_BIT = (SyncStageAccessFlags(1) << SYNC_RAY_TRACING_SHADER_SHADER_SAMPLED_READ);
static const SyncStageAccessFlags SYNC_RAY_TRACING_SHADER_SHADER_STORAGE_READ_BIT = (SyncStageAccessFlags(1) << SYNC_RAY_TRACING_SHADER_SHADER_STORAGE_READ);
static const SyncStageAccessFlags SYNC_RAY_TRACING_SHADER_SHADER_STORAGE_WRITE_BIT = (SyncStageAccessFlags(1) << SYNC_RAY_TRACING_SHADER_SHADER_STORAGE_WRITE);
static const SyncStageAccessFlags SYNC_RAY_TRACING_SHADER_UNIFORM_READ_BIT = (SyncStageAccessFlags(1) << SYNC_RAY_TRACING_SHADER_UNIFORM_READ);
static const SyncStageAccessFlags SYNC_ACCELERATION_STRUCTURE_BUILD_ACCELERATION_STRUCTURE_READ_BIT = (SyncStageAccessFlags(1) << SYNC_ACCELERATION_STRUCTURE_BUILD_ACCELERATION_STRUCTURE_READ);
static const SyncStageAccessFlags SYNC_ACCELERATION_STRUCTURE_BUILD_ACCELERATION_STRUCTURE_WRITE_BIT = (SyncStageAccessFlags(1) << SYNC_ACCELERATION_STRUCTURE_BUILD_ACCELERATION_STRUCTURE_WRITE);
static const SyncStageAccessFlags SYNC_ACCELERATION_STRUCTURE_BUILD_INDIRECT_COMMAND_READ_BIT = (SyncStageAccessFlags(1) << SYNC_ACCELERATION_STRUCTURE_BUILD_INDIRECT_COMMAND_READ);
static const SyncStageAccessFlags SYNC_ACCELERATION_STRUCTURE_BUILD_MICROMAP_READ_BIT_EXT = (SyncStageAccessFlags(1) << SYNC_ACCELERATION_STRUCTURE_BUILD_MICROMAP_READ_EXT);
static const SyncStageAccessFlags SYNC_ACCELERATION_STRUCTURE_BUILD_SHADER_SAMPLED_READ_BIT = (SyncStageAccessFlags(1) << SYNC_ACCELERATION_STRUCTURE_BUILD_SHADER_SAMPLED_READ);
static const SyncStageAccessFlags SYNC_ACCELERATION_STRUCTURE_BUILD_SHADER_STORAGE_READ_BIT = (SyncStageAccessFlags(1) << SYNC_ACCELERATION_STRUCTURE_BUILD_SHADER_STORAGE_READ);
static const SyncStageAccessFlags SYNC_ACCELERATION_STRUCTURE_BUILD_TRANSFER_READ_BIT = (SyncStageAccessFlags(1) << SYNC_ACCELERATION_STRUCTURE_BUILD_TRANSFER_READ);
static const SyncStageAccessFlags SYNC_ACCELERATION_STRUCTURE_BUILD_TRANSFER_WRITE_BIT = (SyncStageAccessFlags(1) << SYNC_ACCELERATION_STRUCTURE_BUILD_TRANSFER_WRITE);
static const SyncStageAccessFlags SYNC_ACCELERATION_STRUCTURE_BUILD_UNIFORM_READ_BIT = (SyncStageAccessFlags(1) << SYNC_ACCELERATION_STRUCTURE_BUILD_UNIFORM_READ);
static const SyncStageAccessFlags SYNC_ACCELERATION_STRUCTURE_COPY_TRANSFER_READ_BIT = (SyncStageAccessFlags(1) << SYNC_ACCELERATION_STRUCTURE_COPY_TRANSFER_READ);
static const SyncStageAccessFlags SYNC_ACCELERATION_STRUCTURE_COPY_TRANSFER_WRITE_BIT = (SyncStageAccessFlags(1) << SYNC_ACCELERATION_STRUCTURE_COPY_TRANSFER_WRITE);
static const SyncStageAccessFlags SYNC_VIDEO_DECODE_VIDEO_DECODE_READ_BIT = (SyncStageAccessFlags(1) << SYNC_VIDEO_DECODE_VIDEO_DECODE_READ);
static const SyncStageAccessFlags SYNC_VIDEO_DECODE_VIDEO_DECODE_WRITE_BIT = (SyncStageAccessFlags(1) << SYNC_VIDEO_DECODE_VIDEO_DECODE_WRITE);
static const SyncStageAccessFlags SYNC_VIDEO_ENCODE_VIDEO_ENCODE_READ_BIT = (SyncStageAccessFlags(1) << SYNC_VIDEO_ENCODE_VIDEO_ENCODE_READ);
static const SyncStageAccessFlags SYNC_VIDEO_ENCODE_VIDEO_ENCODE_WRITE_BIT = (SyncStageAccessFlags(1) << SYNC_VIDEO_ENCODE_VIDEO_ENCODE_WRITE);
static const SyncStageAccessFlags SYNC_SUBPASS_SHADING_HUAWEI_INPUT_ATTACHMENT_READ_BIT = (SyncStageAccessFlags(1) << SYNC_SUBPASS_SHADING_HUAWEI_INPUT_ATTACHMENT_READ);
static const SyncStageAccessFlags SYNC_OPTICAL_FLOW_BIT_NV_OPTICAL_FLOW_READ_BIT_NV = (SyncStageAccessFlags(1) << SYNC_OPTICAL_FLOW_NV_OPTICAL_FLOW_READ_NV);
static const SyncStageAccessFlags SYNC_OPTICAL_FLOW_BIT_NV_OPTICAL_FLOW_WRITE_BIT_NV = (SyncStageAccessFlags(1) << SYNC_OPTICAL_FLOW_NV_OPTICAL_FLOW_WRITE_NV);
static const SyncStageAccessFlags SYNC_MICROMAP_BUILD_BIT_EXT_MICROMAP_READ_BIT_EXT = (SyncStageAccessFlags(1) << SYNC_MICROMAP_BUILD_EXT_MICROMAP_READ_EXT);
static const SyncStageAccessFlags SYNC_MICROMAP_BUILD_BIT_EXT_MICROMAP_WRITE_BIT_EXT = (SyncStageAccessFlags(1) << SYNC_MICROMAP_BUILD_EXT_MICROMAP_WRITE_EXT);
static const SyncStageAccessFlags SYNC_HOST_HOST_READ_BIT = (SyncStageAccessFlags(1) << SYNC_HOST_HOST_READ);
static const SyncStageAccessFlags SYNC_HOST_HOST_WRITE_BIT = (SyncStageAccessFlags(1) << SYNC_HOST_HOST_WRITE);
static const SyncStageAccessFlags SYNC_PRESENT_ENGINE_BIT_SYNCVAL_PRESENT_ACQUIRE_READ_BIT_SYNCVAL = (SyncStageAccessFlags(1) << SYNC_PRESENT_ENGINE_SYNCVAL_PRESENT_ACQUIRE_READ_SYNCVAL);
static const SyncStageAccessFlags SYNC_PRESENT_ENGINE_BIT_SYNCVAL_PRESENT_PRESENTED_BIT_SYNCVAL = (SyncStageAccessFlags(1) << SYNC_PRESENT_ENGINE_SYNCVAL_PRESENT_PRESENTED_SYNCVAL);
static const SyncStageAccessFlags SYNC_IMAGE_LAYOUT_TRANSITION_BIT = (SyncStageAccessFlags(1) << SYNC_IMAGE_LAYOUT_TRANSITION);
static const SyncStageAccessFlags SYNC_QUEUE_FAMILY_OWNERSHIP_TRANSFER_BIT = (SyncStageAccessFlags(1) << SYNC_QUEUE_FAMILY_OWNERSHIP_TRANSFER);

// Map of the StageAccessIndices from the StageAccess Bit
const vvl::unordered_map<SyncStageAccessFlags, SyncStageAccessIndex>& syncStageAccessIndexByStageAccessBit();

struct SyncStageAccessInfoType {
    const char *name;
    VkPipelineStageFlags2 stage_mask;
    VkAccessFlags2 access_mask;
    SyncStageAccessIndex stage_access_index;
    SyncStageAccessFlags stage_access_bit;
};

// Array of text names and component masks for each stage/access index
const std::array<SyncStageAccessInfoType, 109>& syncStageAccessInfoByStageAccessIndex();

// Constants defining the mask of all read and write stage_access states
static const SyncStageAccessFlags syncStageAccessReadMask = ( //  Mask of all read StageAccess bits
    SYNC_DRAW_INDIRECT_INDIRECT_COMMAND_READ_BIT |
    SYNC_DRAW_INDIRECT_TRANSFORM_FEEDBACK_COUNTER_READ_BIT_EXT |
    SYNC_INDEX_INPUT_INDEX_READ_BIT |
    SYNC_VERTEX_ATTRIBUTE_INPUT_VERTEX_ATTRIBUTE_READ_BIT |
    SYNC_VERTEX_SHADER_ACCELERATION_STRUCTURE_READ_BIT |
    SYNC_VERTEX_SHADER_DESCRIPTOR_BUFFER_READ_BIT_EXT |
    SYNC_VERTEX_SHADER_SHADER_SAMPLED_READ_BIT |
    SYNC_VERTEX_SHADER_SHADER_STORAGE_READ_BIT |
    SYNC_VERTEX_SHADER_UNIFORM_READ_BIT |
    SYNC_TESSELLATION_CONTROL_SHADER_ACCELERATION_STRUCTURE_READ_BIT |
    SYNC_TESSELLATION_CONTROL_SHADER_DESCRIPTOR_BUFFER_READ_BIT_EXT |
    SYNC_TESSELLATION_CONTROL_SHADER_SHADER_SAMPLED_READ_BIT |
    SYNC_TESSELLATION_CONTROL_SHADER_SHADER_STORAGE_READ_BIT |
    SYNC_TESSELLATION_CONTROL_SHADER_UNIFORM_READ_BIT |
    SYNC_TESSELLATION_EVALUATION_SHADER_ACCELERATION_STRUCTURE_READ_BIT |
    SYNC_TESSELLATION_EVALUATION_SHADER_DESCRIPTOR_BUFFER_READ_BIT_EXT |
    SYNC_TESSELLATION_EVALUATION_SHADER_SHADER_SAMPLED_READ_BIT |
    SYNC_TESSELLATION_EVALUATION_SHADER_SHADER_STORAGE_READ_BIT |
    SYNC_TESSELLATION_EVALUATION_SHADER_UNIFORM_READ_BIT |
    SYNC_GEOMETRY_SHADER_ACCELERATION_STRUCTURE_READ_BIT |
    SYNC_GEOMETRY_SHADER_DESCRIPTOR_BUFFER_READ_BIT_EXT |
    SYNC_GEOMETRY_SHADER_SHADER_SAMPLED_READ_BIT |
    SYNC_GEOMETRY_SHADER_SHADER_STORAGE_READ_BIT |
    SYNC_GEOMETRY_SHADER_UNIFORM_READ_BIT |
    SYNC_TRANSFORM_FEEDBACK_BIT_EXT_TRANSFORM_FEEDBACK_COUNTER_READ_BIT_EXT |
    SYNC_FRAGMENT_DENSITY_PROCESS_BIT_EXT_FRAGMENT_DENSITY_MAP_READ_BIT_EXT |
    SYNC_TASK_SHADER_EXT_ACCELERATION_STRUCTURE_READ_BIT |
    SYNC_TASK_SHADER_BIT_EXT_DESCRIPTOR_BUFFER_READ_BIT_EXT |
    SYNC_TASK_SHADER_EXT_SHADER_SAMPLED_READ_BIT |
    SYNC_TASK_SHADER_EXT_SHADER_STORAGE_READ_BIT |
    SYNC_TASK_SHADER_EXT_UNIFORM_READ_BIT |
    SYNC_MESH_SHADER_EXT_ACCELERATION_STRUCTURE_READ_BIT |
    SYNC_MESH_SHADER_BIT_EXT_DESCRIPTOR_BUFFER_READ_BIT_EXT |
    SYNC_MESH_SHADER_EXT_SHADER_SAMPLED_READ_BIT |
    SYNC_MESH_SHADER_EXT_SHADER_STORAGE_READ_BIT |
    SYNC_MESH_SHADER_EXT_UNIFORM_READ_BIT |
    SYNC_FRAGMENT_SHADING_RATE_ATTACHMENT_FRAGMENT_SHADING_RATE_ATTACHMENT_READ_BIT |
    SYNC_EARLY_FRAGMENT_TESTS_DEPTH_STENCIL_ATTACHMENT_READ_BIT |
    SYNC_FRAGMENT_SHADER_ACCELERATION_STRUCTURE_READ_BIT |
    SYNC_FRAGMENT_SHADER_DESCRIPTOR_BUFFER_READ_BIT_EXT |
    SYNC_FRAGMENT_SHADER_INPUT_ATTACHMENT_READ_BIT |
    SYNC_FRAGMENT_SHADER_SHADER_SAMPLED_READ_BIT |
    SYNC_FRAGMENT_SHADER_SHADER_STORAGE_READ_BIT |
    SYNC_FRAGMENT_SHADER_UNIFORM_READ_BIT |
    SYNC_LATE_FRAGMENT_TESTS_DEPTH_STENCIL_ATTACHMENT_READ_BIT |
    SYNC_COLOR_ATTACHMENT_OUTPUT_COLOR_ATTACHMENT_READ_BIT |
    SYNC_COLOR_ATTACHMENT_OUTPUT_COLOR_ATTACHMENT_READ_NONCOHERENT_BIT_EXT |
    SYNC_COMPUTE_SHADER_ACCELERATION_STRUCTURE_READ_BIT |
    SYNC_COMPUTE_SHADER_DESCRIPTOR_BUFFER_READ_BIT_EXT |
    SYNC_COMPUTE_SHADER_SHADER_SAMPLED_READ_BIT |
    SYNC_COMPUTE_SHADER_SHADER_STORAGE_READ_BIT |
    SYNC_COMPUTE_SHADER_UNIFORM_READ_BIT |
    SYNC_COPY_TRANSFER_READ_BIT |
    SYNC_RESOLVE_TRANSFER_READ_BIT |
    SYNC_BLIT_TRANSFER_READ_BIT |
    SYNC_COMMAND_PREPROCESS_BIT_NV_COMMAND_PREPROCESS_READ_BIT_NV |
    SYNC_CONDITIONAL_RENDERING_BIT_EXT_CONDITIONAL_RENDERING_READ_BIT_EXT |
    SYNC_RAY_TRACING_SHADER_ACCELERATION_STRUCTURE_READ_BIT |
    SYNC_RAY_TRACING_SHADER_DESCRIPTOR_BUFFER_READ_BIT_EXT |
    SYNC_RAY_TRACING_SHADER_SHADER_BINDING_TABLE_READ_BIT |
    SYNC_RAY_TRACING_SHADER_SHADER_SAMPLED_READ_BIT |
    SYNC_RAY_TRACING_SHADER_SHADER_STORAGE_READ_BIT |
    SYNC_RAY_TRACING_SHADER_UNIFORM_READ_BIT |
    SYNC_ACCELERATION_STRUCTURE_BUILD_ACCELERATION_STRUCTURE_READ_BIT |
    SYNC_ACCELERATION_STRUCTURE_BUILD_INDIRECT_COMMAND_READ_BIT |
    SYNC_ACCELERATION_STRUCTURE_BUILD_MICROMAP_READ_BIT_EXT |
    SYNC_ACCELERATION_STRUCTURE_BUILD_SHADER_SAMPLED_READ_BIT |
    SYNC_ACCELERATION_STRUCTURE_BUILD_SHADER_STORAGE_READ_BIT |
    SYNC_ACCELERATION_STRUCTURE_BUILD_TRANSFER_READ_BIT |
    SYNC_ACCELERATION_STRUCTURE_BUILD_UNIFORM_READ_BIT |
    SYNC_ACCELERATION_STRUCTURE_COPY_TRANSFER_READ_BIT |
    SYNC_VIDEO_DECODE_VIDEO_DECODE_READ_BIT |
    SYNC_VIDEO_ENCODE_VIDEO_ENCODE_READ_BIT |
    SYNC_SUBPASS_SHADING_HUAWEI_INPUT_ATTACHMENT_READ_BIT |
    SYNC_OPTICAL_FLOW_BIT_NV_OPTICAL_FLOW_READ_BIT_NV |
    SYNC_MICROMAP_BUILD_BIT_EXT_MICROMAP_READ_BIT_EXT |
    SYNC_HOST_HOST_READ_BIT |
    SYNC_PRESENT_ENGINE_BIT_SYNCVAL_PRESENT_ACQUIRE_READ_BIT_SYNCVAL
);

static const SyncStageAccessFlags syncStageAccessWriteMask = ( //  Mask of all write StageAccess bits
    SYNC_VERTEX_SHADER_SHADER_STORAGE_WRITE_BIT |
    SYNC_TESSELLATION_CONTROL_SHADER_SHADER_STORAGE_WRITE_BIT |
    SYNC_TESSELLATION_EVALUATION_SHADER_SHADER_STORAGE_WRITE_BIT |
    SYNC_GEOMETRY_SHADER_SHADER_STORAGE_WRITE_BIT |
    SYNC_TRANSFORM_FEEDBACK_BIT_EXT_TRANSFORM_FEEDBACK_COUNTER_WRITE_BIT_EXT |
    SYNC_TRANSFORM_FEEDBACK_BIT_EXT_TRANSFORM_FEEDBACK_WRITE_BIT_EXT |
    SYNC_TASK_SHADER_EXT_SHADER_STORAGE_WRITE_BIT |
    SYNC_MESH_SHADER_EXT_SHADER_STORAGE_WRITE_BIT |
    SYNC_EARLY_FRAGMENT_TESTS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT |
    SYNC_FRAGMENT_SHADER_SHADER_STORAGE_WRITE_BIT |
    SYNC_LATE_FRAGMENT_TESTS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT |
    SYNC_COLOR_ATTACHMENT_OUTPUT_COLOR_ATTACHMENT_WRITE_BIT |
    SYNC_COMPUTE_SHADER_SHADER_STORAGE_WRITE_BIT |
    SYNC_COPY_TRANSFER_WRITE_BIT |
    SYNC_RESOLVE_TRANSFER_WRITE_BIT |
    SYNC_BLIT_TRANSFER_WRITE_BIT |
    SYNC_CLEAR_TRANSFER_WRITE_BIT |
    SYNC_COMMAND_PREPROCESS_BIT_NV_COMMAND_PREPROCESS_WRITE_BIT_NV |
    SYNC_RAY_TRACING_SHADER_SHADER_STORAGE_WRITE_BIT |
    SYNC_ACCELERATION_STRUCTURE_BUILD_ACCELERATION_STRUCTURE_WRITE_BIT |
    SYNC_ACCELERATION_STRUCTURE_BUILD_TRANSFER_WRITE_BIT |
    SYNC_ACCELERATION_STRUCTURE_COPY_TRANSFER_WRITE_BIT |
    SYNC_VIDEO_DECODE_VIDEO_DECODE_WRITE_BIT |
    SYNC_VIDEO_ENCODE_VIDEO_ENCODE_WRITE_BIT |
    SYNC_OPTICAL_FLOW_BIT_NV_OPTICAL_FLOW_WRITE_BIT_NV |
    SYNC_MICROMAP_BUILD_BIT_EXT_MICROMAP_WRITE_BIT_EXT |
    SYNC_HOST_HOST_WRITE_BIT |
    SYNC_PRESENT_ENGINE_BIT_SYNCVAL_PRESENT_PRESENTED_BIT_SYNCVAL |
    SYNC_IMAGE_LAYOUT_TRANSITION_BIT |
    SYNC_QUEUE_FAMILY_OWNERSHIP_TRANSFER_BIT
);

// Bit order mask of stage_access bit for each stage
const std::map<VkPipelineStageFlags2, SyncStageAccessFlags>& syncStageAccessMaskByStageBit();

// Bit order mask of stage_access bit for each access
const std::map<VkAccessFlags2, SyncStageAccessFlags>& syncStageAccessMaskByAccessBit();

// stage_access index for each stage and access
const std::map<VkPipelineStageFlags2, std::map<VkAccessFlags2, SyncStageAccessIndex>>& syncStageAccessIndexByStageAndAccess();

// Direct VkPipelineStageFlags to valid VkAccessFlags lookup table
const std::map<VkPipelineStageFlags2, VkAccessFlags2>& syncDirectStageToAccessMask();

// Pipeline stages corresponding to VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT for each VkQueueFlagBits
const std::map<VkQueueFlagBits, VkPipelineStageFlags2>& syncAllCommandStagesByQueueFlags();

// Masks of logically earlier stage flags for a given stage flag
const std::map<VkPipelineStageFlags2, VkPipelineStageFlags2>& syncLogicallyEarlierStages();

// Masks of logically later stage flags for a given stage flag
const std::map<VkPipelineStageFlags2, VkPipelineStageFlags2>& syncLogicallyLaterStages();

// Lookup table of stage orderings
const std::map<VkPipelineStageFlags2, int>& syncStageOrder();

struct SyncShaderStageAccess {
    SyncStageAccessIndex sampled_read;
    SyncStageAccessIndex storage_read;
    SyncStageAccessIndex storage_write;
    SyncStageAccessIndex uniform_read;
};

const std::map<VkShaderStageFlagBits, SyncShaderStageAccess>& syncStageAccessMaskByShaderStage();