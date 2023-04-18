/*
 * Copyright (c) 2015-2023 The Khronos Group Inc.
 * Copyright (c) 2015-2023 Valve Corporation
 * Copyright (c) 2015-2023 LunarG, Inc.
 * Copyright (c) 2015-2023 Google, Inc.
 * Modifications Copyright (C) 2020 Advanced Micro Devices, Inc. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 */

#include "utils/cast_utils.h"
#include "../framework/layer_validation_tests.h"

TEST_F(VkLayerTest, StageMaskGsTsEnabled) {
    TEST_DESCRIPTION(
        "Attempt to use a stageMask w/ geometry shader and tesselation shader bits enabled when those features are disabled on the "
        "device.");

    ASSERT_NO_FATAL_FAILURE(Init());
    ASSERT_NO_FATAL_FAILURE(InitRenderTarget());

    std::vector<const char *> device_extension_names;
    auto features = m_device->phy().features();
    // Make sure gs & ts are disabled
    features.geometryShader = false;
    features.tessellationShader = false;
    // The sacrificial device object
    VkDeviceObj test_device(0, gpu(), device_extension_names, &features);

    VkCommandPoolCreateInfo pool_create_info = LvlInitStruct<VkCommandPoolCreateInfo>();
    pool_create_info.queueFamilyIndex = test_device.graphics_queue_node_index_;

    VkCommandPool command_pool;
    vk::CreateCommandPool(test_device.handle(), &pool_create_info, nullptr, &command_pool);

    VkCommandBufferAllocateInfo cmd = LvlInitStruct<VkCommandBufferAllocateInfo>();
    cmd.commandPool = command_pool;
    cmd.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    cmd.commandBufferCount = 1;

    VkCommandBuffer cmd_buffer;
    VkResult err = vk::AllocateCommandBuffers(test_device.handle(), &cmd, &cmd_buffer);
    ASSERT_VK_SUCCESS(err);

    VkEvent event;
    VkEventCreateInfo evci = LvlInitStruct<VkEventCreateInfo>();
    VkResult result = vk::CreateEvent(test_device.handle(), &evci, NULL, &event);
    ASSERT_VK_SUCCESS(result);

    VkCommandBufferBeginInfo cbbi = LvlInitStruct<VkCommandBufferBeginInfo>();
    vk::BeginCommandBuffer(cmd_buffer, &cbbi);
    m_errorMonitor->SetDesiredFailureMsg(kErrorBit, "VUID-vkCmdSetEvent-stageMask-04090");
    vk::CmdSetEvent(cmd_buffer, event, VK_PIPELINE_STAGE_GEOMETRY_SHADER_BIT);
    m_errorMonitor->VerifyFound();

    m_errorMonitor->SetDesiredFailureMsg(kErrorBit, "VUID-vkCmdSetEvent-stageMask-04091");
    vk::CmdSetEvent(cmd_buffer, event, VK_PIPELINE_STAGE_TESSELLATION_CONTROL_SHADER_BIT);
    m_errorMonitor->VerifyFound();

    vk::DestroyEvent(test_device.handle(), event, NULL);
    vk::DestroyCommandPool(test_device.handle(), command_pool, NULL);
}

TEST_F(VkLayerTest, ValidateGeometryShaderEnabled) {
    TEST_DESCRIPTION("Validate geometry shader feature is enabled if geometry shader stage is used");

    VkPhysicalDeviceFeatures deviceFeatures = {};
    deviceFeatures.geometryShader = VK_FALSE;

    ASSERT_NO_FATAL_FAILURE(Init(&deviceFeatures));
    ASSERT_NO_FATAL_FAILURE(InitRenderTarget());

    if (m_device->props.limits.maxGeometryOutputVertices == 0) {
        GTEST_SKIP() << "Device doesn't support geometry shaders";
    }

    VkShaderObj vs(this, bindStateVertShaderText, VK_SHADER_STAGE_VERTEX_BIT);
    VkShaderObj gs(this, bindStateGeomShaderText, VK_SHADER_STAGE_GEOMETRY_BIT);

    auto set_info = [&](CreatePipelineHelper &helper) {
        helper.ia_ci_.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;
        helper.shader_stages_ = {vs.GetStageCreateInfo(), gs.GetStageCreateInfo(), helper.fs_->GetStageCreateInfo()};
    };

    constexpr std::array vuids = {"VUID-VkPipelineShaderStageCreateInfo-stage-00704", "VUID-VkShaderModuleCreateInfo-pCode-08740"};
    CreatePipelineHelper::OneshotTest(*this, set_info, kErrorBit, vuids);
}

TEST_F(VkLayerTest, ValidateTessellationShaderEnabled) {
    TEST_DESCRIPTION(
        "Validate tessellation shader feature is enabled if tessellation control or tessellation evaluation shader stage is used");

    VkPhysicalDeviceFeatures deviceFeatures = {};
    deviceFeatures.tessellationShader = VK_FALSE;

    ASSERT_NO_FATAL_FAILURE(Init(&deviceFeatures));
    ASSERT_NO_FATAL_FAILURE(InitRenderTarget());

    if (m_device->phy().properties().limits.maxTessellationPatchSize == 0) {
        GTEST_SKIP() << "patchControlPoints not supported";
    }

    char const *tcsSource = R"glsl(
        #version 450
        layout(location=0) out int x[];
        layout(vertices=3) out;
        void main(){
           gl_TessLevelOuter[0] = gl_TessLevelOuter[1] = gl_TessLevelOuter[2] = 1;
           gl_TessLevelInner[0] = 1;
           x[gl_InvocationID] = gl_InvocationID;
        }
    )glsl";
    char const *tesSource = R"glsl(
        #version 450
        layout(triangles, equal_spacing, cw) in;
        layout(location=0) patch in int x;
        void main(){
           gl_Position.xyz = gl_TessCoord;
           gl_Position.w = x;
        }
    )glsl";

    VkShaderObj tcs(this, tcsSource, VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT);
    VkShaderObj tes(this, tesSource, VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT);

    VkPipelineInputAssemblyStateCreateInfo iasci{VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO, nullptr, 0,
                                                 VK_PRIMITIVE_TOPOLOGY_PATCH_LIST, VK_FALSE};

    VkPipelineTessellationStateCreateInfo tsci{VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO, nullptr, 0, 3};

    auto set_info = [&](CreatePipelineHelper &helper) {
        helper.ia_ci_.topology = VK_PRIMITIVE_TOPOLOGY_PATCH_LIST;
        helper.gp_ci_.pTessellationState = &tsci;
        helper.gp_ci_.pInputAssemblyState = &iasci;
        helper.shader_stages_.emplace_back(tcs.GetStageCreateInfo());
        helper.shader_stages_.emplace_back(tes.GetStageCreateInfo());
    };
    constexpr std::array vuids = {"VUID-VkPipelineShaderStageCreateInfo-stage-00705", "VUID-VkShaderModuleCreateInfo-pCode-08740",
                                  "VUID-VkShaderModuleCreateInfo-pCode-08740",
                                  "VUID-VkPipelineInputAssemblyStateCreateInfo-topology-00430"};
    CreatePipelineHelper::OneshotTest(*this, set_info, kErrorBit, vuids);
}

TEST_F(VkLayerTest, PointSizeGeomShaderDontWrite) {
    TEST_DESCRIPTION(
        "Create a pipeline using TOPOLOGY_POINT_LIST, set PointSize vertex shader, but not in the final geometry stage.");

    ASSERT_NO_FATAL_FAILURE(Init());

    if ((!m_device->phy().features().geometryShader) || (!m_device->phy().features().shaderTessellationAndGeometryPointSize)) {
        GTEST_SKIP() << "Device does not support the required geometry shader features";
    }
    ASSERT_NO_FATAL_FAILURE(InitRenderTarget());
    ASSERT_NO_FATAL_FAILURE(InitViewport());

    // Create GS declaring PointSize and writing to it
    static char const *gsSource = R"glsl(
        #version 450
        layout (points) in;
        layout (points) out;
        layout (max_vertices = 1) out;
        void main() {
           gl_Position = vec4(1.0, 0.5, 0.5, 0.0);
           EmitVertex();
        }
    )glsl";

    VkShaderObj vs(this, bindStateVertPointSizeShaderText, VK_SHADER_STAGE_VERTEX_BIT);
    VkShaderObj gs(this, gsSource, VK_SHADER_STAGE_GEOMETRY_BIT);

    auto set_info = [&](CreatePipelineHelper &helper) {
        helper.ia_ci_.topology = VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
        helper.shader_stages_ = {vs.GetStageCreateInfo(), gs.GetStageCreateInfo(), helper.fs_->GetStageCreateInfo()};
    };

    CreatePipelineHelper::OneshotTest(*this, set_info, kErrorBit, "VUID-VkGraphicsPipelineCreateInfo-Geometry-07725");
}

TEST_F(VkLayerTest, PointSizeGeomShaderWrite) {
    TEST_DESCRIPTION(
        "Create a pipeline using TOPOLOGY_POINT_LIST, set PointSize vertex shader, but not in the final geometry stage.");

    ASSERT_NO_FATAL_FAILURE(InitFramework());
    VkPhysicalDeviceFeatures features{};
    vk::GetPhysicalDeviceFeatures(gpu(), &features);
    if (features.geometryShader == VK_FALSE) {
        GTEST_SKIP() << "geometryShader not supported";
    }
    features.shaderTessellationAndGeometryPointSize = VK_FALSE;
    ASSERT_NO_FATAL_FAILURE(InitState(&features));
    ASSERT_NO_FATAL_FAILURE(InitRenderTarget());
    ASSERT_NO_FATAL_FAILURE(InitViewport());

    // Compiled using the GLSL code below. GlslangValidator rearranges the members, but here they are kept in the order provided.
    // #version 450
    // layout (points) in;
    // layout (points) out;
    // layout (max_vertices = 1) out;
    // void main() {
    //     gl_Position = vec4(1.0f);
    //     gl_PointSize = 1.0f;
    //     EmitVertex();
    // }
    const char *gsSource = R"(
               OpCapability Geometry
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint Geometry %main "main" %_
               OpExecutionMode %main InputPoints
               OpExecutionMode %main Invocations 1
               OpExecutionMode %main OutputPoints
               OpExecutionMode %main OutputVertices 1
               OpName %_ ""
               OpMemberDecorate %gl_PerVertex 0 BuiltIn Position
               OpMemberDecorate %gl_PerVertex 1 BuiltIn PointSize
               OpMemberDecorate %gl_PerVertex 2 BuiltIn ClipDistance
               OpMemberDecorate %gl_PerVertex 3 BuiltIn CullDistance
               OpDecorate %gl_PerVertex Block
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
    %v4float = OpTypeVector %float 4
       %uint = OpTypeInt 32 0
     %uint_1 = OpConstant %uint 1
%_arr_float_uint_1 = OpTypeArray %float %uint_1
%gl_PerVertex = OpTypeStruct %v4float %float %_arr_float_uint_1 %_arr_float_uint_1
%_ptr_Output_gl_PerVertex = OpTypePointer Output %gl_PerVertex
          %_ = OpVariable %_ptr_Output_gl_PerVertex Output
        %int = OpTypeInt 32 1
      %int_0 = OpConstant %int 0
    %float_1 = OpConstant %float 1
         %17 = OpConstantComposite %v4float %float_1 %float_1 %float_1 %float_1
%_ptr_Output_v4float = OpTypePointer Output %v4float
      %int_1 = OpConstant %int 1
%_ptr_Output_float = OpTypePointer Output %float
       %main = OpFunction %void None %3
          %5 = OpLabel
         %19 = OpAccessChain %_ptr_Output_v4float %_ %int_0
               OpStore %19 %17
         %22 = OpAccessChain %_ptr_Output_float %_ %int_1
               OpStore %22 %float_1
               OpEmitVertex
               OpReturn
               OpFunctionEnd
        )";

    VkShaderObj vs(this, bindStateVertPointSizeShaderText, VK_SHADER_STAGE_VERTEX_BIT);
    VkShaderObj gs(this, gsSource, VK_SHADER_STAGE_GEOMETRY_BIT, SPV_ENV_VULKAN_1_0, SPV_SOURCE_ASM);

    auto set_info = [&](CreatePipelineHelper &helper) {
        helper.ia_ci_.topology = VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
        helper.shader_stages_ = {vs.GetStageCreateInfo(), gs.GetStageCreateInfo(), helper.fs_->GetStageCreateInfo()};
    };

    CreatePipelineHelper::OneshotTest(*this, set_info, kErrorBit, "VUID-VkGraphicsPipelineCreateInfo-Geometry-07726");
}

TEST_F(VkLayerTest, BuiltinBlockOrderMismatchVsGs) {
    TEST_DESCRIPTION("Use different order of gl_Position and gl_PointSize in builtin block interface between VS and GS.");

    ASSERT_NO_FATAL_FAILURE(Init());

    if (!m_device->phy().features().geometryShader || !m_device->phy().features().shaderTessellationAndGeometryPointSize) {
        GTEST_SKIP() << "Device does not support geometry shaders";
    }
    ASSERT_NO_FATAL_FAILURE(InitRenderTarget());
    ASSERT_NO_FATAL_FAILURE(InitViewport());

    // Compiled using the GLSL code below. GlslangValidator rearranges the members, but here they are kept in the order provided.
    // #version 450
    // layout (points) in;
    // layout (points) out;
    // layout (max_vertices = 1) out;
    // in gl_PerVertex {
    //     float gl_PointSize;
    //     vec4 gl_Position;
    // } gl_in[];
    // void main() {
    //     gl_Position = gl_in[0].gl_Position;
    //     gl_PointSize = gl_in[0].gl_PointSize;
    //     EmitVertex();
    // }

    const char *gsSource = R"(
               OpCapability Geometry
               OpCapability GeometryPointSize
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint Geometry %main "main" %_ %gl_in
               OpExecutionMode %main InputPoints
               OpExecutionMode %main Invocations 1
               OpExecutionMode %main OutputPoints
               OpExecutionMode %main OutputVertices 1
               OpSource GLSL 450
               OpMemberDecorate %gl_PerVertex 0 BuiltIn Position
               OpMemberDecorate %gl_PerVertex 1 BuiltIn PointSize
               OpMemberDecorate %gl_PerVertex 2 BuiltIn ClipDistance
               OpMemberDecorate %gl_PerVertex 3 BuiltIn CullDistance
               OpDecorate %gl_PerVertex Block
               OpMemberDecorate %gl_PerVertex_0 0 BuiltIn PointSize
               OpMemberDecorate %gl_PerVertex_0 1 BuiltIn Position
               OpDecorate %gl_PerVertex_0 Block
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
    %v4float = OpTypeVector %float 4
       %uint = OpTypeInt 32 0
     %uint_1 = OpConstant %uint 1
%_arr_float_uint_1 = OpTypeArray %float %uint_1
%gl_PerVertex = OpTypeStruct %v4float %float %_arr_float_uint_1 %_arr_float_uint_1
%_ptr_Output_gl_PerVertex = OpTypePointer Output %gl_PerVertex
          %_ = OpVariable %_ptr_Output_gl_PerVertex Output
        %int = OpTypeInt 32 1
      %int_0 = OpConstant %int 0
%gl_PerVertex_0 = OpTypeStruct %float %v4float
%_arr_gl_PerVertex_0_uint_1 = OpTypeArray %gl_PerVertex_0 %uint_1
%_ptr_Input__arr_gl_PerVertex_0_uint_1 = OpTypePointer Input %_arr_gl_PerVertex_0_uint_1
      %gl_in = OpVariable %_ptr_Input__arr_gl_PerVertex_0_uint_1 Input
%_ptr_Input_v4float = OpTypePointer Input %v4float
%_ptr_Output_v4float = OpTypePointer Output %v4float
      %int_1 = OpConstant %int 1
%_ptr_Input_float = OpTypePointer Input %float
%_ptr_Output_float = OpTypePointer Output %float
       %main = OpFunction %void None %3
          %5 = OpLabel
         %21 = OpAccessChain %_ptr_Input_v4float %gl_in %int_0 %int_1
         %22 = OpLoad %v4float %21
         %24 = OpAccessChain %_ptr_Output_v4float %_ %int_0
               OpStore %24 %22
         %27 = OpAccessChain %_ptr_Input_float %gl_in %int_0 %int_0
         %28 = OpLoad %float %27
         %30 = OpAccessChain %_ptr_Output_float %_ %int_1
               OpStore %30 %28
               OpEmitVertex
               OpReturn
               OpFunctionEnd
        )";

    VkShaderObj vs(this, bindStateVertPointSizeShaderText, VK_SHADER_STAGE_VERTEX_BIT);
    VkShaderObj gs(this, gsSource, VK_SHADER_STAGE_GEOMETRY_BIT, SPV_ENV_VULKAN_1_0, SPV_SOURCE_ASM);

    auto set_info = [&](CreatePipelineHelper &helper) {
        helper.ia_ci_.topology = VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
        helper.shader_stages_ = {vs.GetStageCreateInfo(), gs.GetStageCreateInfo(), helper.fs_->GetStageCreateInfo()};
    };
    CreatePipelineHelper::OneshotTest(*this, set_info, kErrorBit, "UNASSIGNED-CoreValidation-Shader-BuiltinMismatch");
}

TEST_F(VkLayerTest, BuiltinBlockSizeMismatchVsGs) {
    TEST_DESCRIPTION("Use different number of elements in builtin block interface between VS and GS.");

    ASSERT_NO_FATAL_FAILURE(Init());

    if (!m_device->phy().features().geometryShader || !m_device->phy().features().shaderTessellationAndGeometryPointSize) {
        GTEST_SKIP() << "Device does not support geometry shaders";
    }

    ASSERT_NO_FATAL_FAILURE(InitRenderTarget());
    ASSERT_NO_FATAL_FAILURE(InitViewport());

    static const char *gsSource = R"glsl(
        #version 450
        layout (points) in;
        layout (points) out;
        layout (max_vertices = 1) out;
        in gl_PerVertex
        {
            vec4 gl_Position;
            float gl_PointSize;
            float gl_ClipDistance[];
        } gl_in[];
        void main()
        {
            gl_Position = gl_in[0].gl_Position;
            gl_PointSize = gl_in[0].gl_PointSize;
            EmitVertex();
        }
    )glsl";

    VkShaderObj vs(this, bindStateVertPointSizeShaderText, VK_SHADER_STAGE_VERTEX_BIT);
    VkShaderObj gs(this, gsSource, VK_SHADER_STAGE_GEOMETRY_BIT);

    auto set_info = [&](CreatePipelineHelper &helper) {
        helper.ia_ci_.topology = VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
        helper.shader_stages_ = {vs.GetStageCreateInfo(), gs.GetStageCreateInfo(), helper.fs_->GetStageCreateInfo()};
    };
    CreatePipelineHelper::OneshotTest(*this, set_info, kErrorBit, "UNASSIGNED-CoreValidation-Shader-BuiltinMismatch");
}

TEST_F(VkLayerTest, CreatePipelineExceedMaxTessellationControlInputOutputComponents) {
    TEST_DESCRIPTION(
        "Test that errors are produced when the number of per-vertex input and/or output components to the tessellation control "
        "stage exceeds the device limit");

    ASSERT_NO_FATAL_FAILURE(Init());
    ASSERT_NO_FATAL_FAILURE(InitRenderTarget());

    // overflow == 0: no overflow, 1: too many components, 2: location number too large
    for (uint32_t overflow = 0; overflow < 3; ++overflow) {
        m_errorMonitor->Reset();
        VkPhysicalDeviceFeatures feat;
        vk::GetPhysicalDeviceFeatures(gpu(), &feat);
        if (!feat.tessellationShader) {
            GTEST_SKIP() << "tessellation shader stage(s) unsupported";
        }

        // Tessellation control stage
        std::string tcsSourceStr =
            "#version 450\n"
            "\n";
        // Input components
        const uint32_t maxTescInComp = m_device->props.limits.maxTessellationControlPerVertexInputComponents + overflow;
        const uint32_t numInVec4 = maxTescInComp / 4;
        uint32_t inLocation = 0;
        if (overflow == 2) {
            tcsSourceStr += "layout(location=" + std::to_string(numInVec4 + 1) + ") in vec4 vnIn[];\n";
        } else if (overflow == 1) {
            for (uint32_t i = 0; i < numInVec4; i++) {
                tcsSourceStr += "layout(location=" + std::to_string(inLocation) + ") in vec4 v" + std::to_string(i) + "In[];\n";
                inLocation += 1;
            }
            const uint32_t inRemainder = maxTescInComp % 4;
            if (inRemainder != 0) {
                if (inRemainder == 1) {
                    tcsSourceStr += "layout(location=" + std::to_string(inLocation) + ") in float" + " vnIn[];\n";
                } else {
                    tcsSourceStr +=
                        "layout(location=" + std::to_string(inLocation) + ") in vec" + std::to_string(inRemainder) + " vnIn[];\n";
                }
                inLocation += 1;
            }
        }

        // Output components
        const uint32_t maxTescOutComp = m_device->props.limits.maxTessellationControlPerVertexOutputComponents + overflow;
        const uint32_t numOutVec4 = maxTescOutComp / 4;
        uint32_t outLocation = 0;
        if (overflow == 2) {
            tcsSourceStr += "layout(location=" + std::to_string(numOutVec4 + 1) + ") out vec4 vnOut[3];\n";
        } else if (overflow == 1) {
            for (uint32_t i = 0; i < numOutVec4; i++) {
                tcsSourceStr += "layout(location=" + std::to_string(outLocation) + ") out vec4 v" + std::to_string(i) + "Out[3];\n";
                outLocation += 1;
            }
            const uint32_t outRemainder = maxTescOutComp % 4;
            if (outRemainder != 0) {
                if (outRemainder == 1) {
                    tcsSourceStr += "layout(location=" + std::to_string(outLocation) + ") out float" + " vnOut[3];\n";
                } else {
                    tcsSourceStr += "layout(location=" + std::to_string(outLocation) + ") out vec" + std::to_string(outRemainder) +
                                    " vnOut[3];\n";
                }
                outLocation += 1;
            }
        }

        tcsSourceStr += "layout(vertices=3) out;\n";
        // Finalize
        tcsSourceStr +=
            "\n"
            "void main(){\n"
            "}\n";

        VkShaderObj tcs(this, tcsSourceStr.c_str(), VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT);
        VkShaderObj tes(this, bindStateTeshaderText, VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT);

        VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo = LvlInitStruct<VkPipelineInputAssemblyStateCreateInfo>();
        inputAssemblyInfo.flags = 0;
        inputAssemblyInfo.topology = VK_PRIMITIVE_TOPOLOGY_PATCH_LIST;
        inputAssemblyInfo.primitiveRestartEnable = VK_FALSE;

        VkPipelineTessellationStateCreateInfo tessInfo = LvlInitStruct<VkPipelineTessellationStateCreateInfo>();
        tessInfo.flags = 0;
        tessInfo.patchControlPoints = 3;

        m_errorMonitor->SetUnexpectedError("UNASSIGNED-CoreValidation-Shader-InputNotProduced");

        const auto set_info = [&](CreatePipelineHelper &helper) {
            helper.shader_stages_ = {helper.vs_->GetStageCreateInfo(), tcs.GetStageCreateInfo(), tes.GetStageCreateInfo(),
                                     helper.fs_->GetStageCreateInfo()};
            helper.gp_ci_.pTessellationState = &tessInfo;
            helper.gp_ci_.pInputAssemblyState = &inputAssemblyInfo;
        };
        // maxTessellationControlPerVertexInputComponents and maxTessellationControlPerVertexOutputComponents
        switch (overflow) {
            case 0: {
                CreatePipelineHelper::OneshotTest(*this, set_info, kErrorBit);
                break;
            }
            case 1: {
                // in and out component limit
                constexpr std::array vuids = {"VUID-RuntimeSpirv-Location-06272", "VUID-RuntimeSpirv-Location-06272"};
                CreatePipelineHelper::OneshotTest(*this, set_info, kErrorBit, vuids);
                break;
            }
            case 2: {
                // in and out component limit
                constexpr std::array vuids = {"VUID-RuntimeSpirv-Location-06272", "VUID-RuntimeSpirv-Location-06272"};
                CreatePipelineHelper::OneshotTest(*this, set_info, kErrorBit, vuids);
                break;
            }
            default: {
                assert(0);
            }
        }
    }
}

TEST_F(VkLayerTest, CreatePipelineExceedMaxTessellationEvaluationInputOutputComponents) {
    TEST_DESCRIPTION(
        "Test that errors are produced when the number of input and/or output components to the tessellation evaluation stage "
        "exceeds the device limit");

    ASSERT_NO_FATAL_FAILURE(Init());
    ASSERT_NO_FATAL_FAILURE(InitRenderTarget());

    // overflow == 0: no overflow, 1: too many components, 2: location number too large
    for (uint32_t overflow = 0; overflow < 3; ++overflow) {
        m_errorMonitor->Reset();
        VkPhysicalDeviceFeatures feat;
        vk::GetPhysicalDeviceFeatures(gpu(), &feat);
        if (!feat.tessellationShader) {
            GTEST_SKIP() << "tessellation shader stage(s) unsupported";
        }

        // Tessellation evaluation stage
        std::string tesSourceStr =
            "#version 450\n"
            "\n"
            "layout (triangles) in;\n"
            "\n";
        // Input components
        const uint32_t maxTeseInComp = m_device->props.limits.maxTessellationEvaluationInputComponents + overflow;
        const uint32_t numInVec4 = maxTeseInComp / 4;
        uint32_t inLocation = 0;
        if (overflow == 2) {
            tesSourceStr += "layout(location=" + std::to_string(numInVec4 + 1) + ") in vec4 vnIn[];\n";
        } else if (overflow == 1) {
            for (uint32_t i = 0; i < numInVec4; i++) {
                tesSourceStr += "layout(location=" + std::to_string(inLocation) + ") in vec4 v" + std::to_string(i) + "In[];\n";
                inLocation += 1;
            }
            const uint32_t inRemainder = maxTeseInComp % 4;
            if (inRemainder != 0) {
                if (inRemainder == 1) {
                    tesSourceStr += "layout(location=" + std::to_string(inLocation) + ") in float" + " vnIn[];\n";
                } else {
                    tesSourceStr +=
                        "layout(location=" + std::to_string(inLocation) + ") in vec" + std::to_string(inRemainder) + " vnIn[];\n";
                }
                inLocation += 1;
            }
        }

        // Output components
        const uint32_t maxTeseOutComp = m_device->props.limits.maxTessellationEvaluationOutputComponents + overflow;
        const uint32_t numOutVec4 = maxTeseOutComp / 4;
        uint32_t outLocation = 0;
        if (overflow == 2) {
            tesSourceStr += "layout(location=" + std::to_string(numOutVec4 + 1) + ") out vec4 vnOut;\n";
        } else if (overflow == 1) {
            for (uint32_t i = 0; i < numOutVec4; i++) {
                tesSourceStr += "layout(location=" + std::to_string(outLocation) + ") out vec4 v" + std::to_string(i) + "Out;\n";
                outLocation += 1;
            }
            const uint32_t outRemainder = maxTeseOutComp % 4;
            if (outRemainder != 0) {
                if (outRemainder == 1) {
                    tesSourceStr += "layout(location=" + std::to_string(outLocation) + ") out float" + " vnOut;\n";
                } else {
                    tesSourceStr +=
                        "layout(location=" + std::to_string(outLocation) + ") out vec" + std::to_string(outRemainder) + " vnOut;\n";
                }
                outLocation += 1;
            }
        }

        // Finalize
        tesSourceStr +=
            "\n"
            "void main(){\n"
            "}\n";

        VkShaderObj tcs(this, bindStateTscShaderText, VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT);
        VkShaderObj tes(this, tesSourceStr.c_str(), VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT);

        VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo = LvlInitStruct<VkPipelineInputAssemblyStateCreateInfo>();
        inputAssemblyInfo.flags = 0;
        inputAssemblyInfo.topology = VK_PRIMITIVE_TOPOLOGY_PATCH_LIST;
        inputAssemblyInfo.primitiveRestartEnable = VK_FALSE;

        VkPipelineTessellationStateCreateInfo tessInfo = LvlInitStruct<VkPipelineTessellationStateCreateInfo>();
        tessInfo.flags = 0;
        tessInfo.patchControlPoints = 3;

        m_errorMonitor->SetUnexpectedError("UNASSIGNED-CoreValidation-Shader-InputNotProduced");

        const auto set_info = [&](CreatePipelineHelper &helper) {
            helper.shader_stages_ = {helper.vs_->GetStageCreateInfo(), tcs.GetStageCreateInfo(), tes.GetStageCreateInfo(),
                                     helper.fs_->GetStageCreateInfo()};
            helper.gp_ci_.pTessellationState = &tessInfo;
            helper.gp_ci_.pInputAssemblyState = &inputAssemblyInfo;
        };

        // maxTessellationEvaluationInputComponents and maxTessellationEvaluationOutputComponents
        switch (overflow) {
            case 0: {
                CreatePipelineHelper::OneshotTest(*this, set_info, kErrorBit);
                break;
            }
            case 1: {
                // in and out component limit
                constexpr std::array vuids = {"VUID-RuntimeSpirv-Location-06272", "VUID-RuntimeSpirv-Location-06272"};
                CreatePipelineHelper::OneshotTest(*this, set_info, kErrorBit, vuids);
                break;
            }
            case 2: {
                // in and out component limit
                constexpr std::array vuids = {"VUID-RuntimeSpirv-Location-06272", "VUID-RuntimeSpirv-Location-06272"};
                CreatePipelineHelper::OneshotTest(*this, set_info, kErrorBit, vuids);
                break;
            }
            default: {
                assert(false);
            }
        }
    }
}

TEST_F(VkLayerTest, CreatePipelineExceedMaxGeometryInputOutputComponents) {
    TEST_DESCRIPTION(
        "Test that errors are produced when the number of input and/or output components to the geometry stage exceeds the device "
        "limit");

    ASSERT_NO_FATAL_FAILURE(Init());
    ASSERT_NO_FATAL_FAILURE(InitRenderTarget());

    // overflow == 0: no overflow, 1: too many components, 2: location number too large
    for (uint32_t overflow = 0; overflow < 3; ++overflow) {
        m_errorMonitor->Reset();
        VkPhysicalDeviceFeatures feat;
        vk::GetPhysicalDeviceFeatures(gpu(), &feat);
        if (!feat.geometryShader) {
            GTEST_SKIP() << "geometry shader stage unsupported";
        }

        std::string gsSourceStr =
            "#version 450\n"
            "\n"
            "layout(triangles) in;\n"
            "layout(invocations=1) in;\n";

        // Input components
        const uint32_t maxGeomInComp = m_device->props.limits.maxGeometryInputComponents + overflow;
        const uint32_t numInVec4 = maxGeomInComp / 4;
        uint32_t inLocation = 0;
        if (overflow == 2) {
            gsSourceStr += "layout(location=" + std::to_string(numInVec4 + 1) + ") in vec4 vnIn[];\n";
        } else {
            for (uint32_t i = 0; i < numInVec4; i++) {
                gsSourceStr += "layout(location=" + std::to_string(inLocation) + ") in vec4 v" + std::to_string(i) + "In[];\n";
                inLocation += 1;
            }
            const uint32_t inRemainder = maxGeomInComp % 4;
            if (inRemainder != 0) {
                if (inRemainder == 1) {
                    gsSourceStr += "layout(location=" + std::to_string(inLocation) + ") in float" + " vnIn[];\n";
                } else {
                    gsSourceStr +=
                        "layout(location=" + std::to_string(inLocation) + ") in vec" + std::to_string(inRemainder) + " vnIn[];\n";
                }
                inLocation += 1;
            }
        }

        // Output components
        const uint32_t maxGeomOutComp = m_device->props.limits.maxGeometryOutputComponents + overflow;
        const uint32_t numOutVec4 = maxGeomOutComp / 4;
        uint32_t outLocation = 0;
        if (overflow == 2) {
            gsSourceStr += "layout(location=" + std::to_string(numOutVec4) + ") out vec4 vnOut;\n";
        } else if (overflow == 1) {
            for (uint32_t i = 0; i < numOutVec4; i++) {
                gsSourceStr += "layout(location=" + std::to_string(outLocation) + ") out vec4 v" + std::to_string(i) + "Out;\n";
                outLocation += 1;
            }
            const uint32_t outRemainder = maxGeomOutComp % 4;
            if (outRemainder != 0) {
                if (outRemainder == 1) {
                    gsSourceStr += "layout(location=" + std::to_string(outLocation) + ") out float" + " vnOut;\n";
                } else {
                    gsSourceStr +=
                        "layout(location=" + std::to_string(outLocation) + ") out vec" + std::to_string(outRemainder) + " vnOut;\n";
                }
                outLocation += 1;
            }
        }

        // Finalize
        int max_vertices = overflow ? (m_device->props.limits.maxGeometryTotalOutputComponents / maxGeomOutComp + 1) : 1;
        gsSourceStr += "layout(triangle_strip, max_vertices = " + std::to_string(max_vertices) +
                       ") out;\n"
                       "\n"
                       "void main(){\n"
                       "}\n";

        VkShaderObj gs(this, gsSourceStr.c_str(), VK_SHADER_STAGE_GEOMETRY_BIT);

        m_errorMonitor->SetUnexpectedError("VUID-RuntimeSpirv-OpEntryPoint-08743");

        const auto set_info = [&](CreatePipelineHelper &helper) {
            helper.shader_stages_ = {helper.vs_->GetStageCreateInfo(), gs.GetStageCreateInfo(), helper.fs_->GetStageCreateInfo()};
        };
        // maxGeometryInputComponents and maxGeometryOutputComponents
        switch (overflow) {
            case 0: {
                CreatePipelineHelper::OneshotTest(*this, set_info, kErrorBit);
                break;
            }
            case 1: {
                // in and out component limit
                constexpr std::array vuids = {"VUID-RuntimeSpirv-Location-06272", "VUID-RuntimeSpirv-Location-06272"};
                CreatePipelineHelper::OneshotTest(*this, set_info, kErrorBit, vuids);
                break;
            }
            case 2: {
                // in and out component limit
                constexpr std::array vuids = {"VUID-RuntimeSpirv-Location-06272", "VUID-RuntimeSpirv-Location-06272"};
                CreatePipelineHelper::OneshotTest(*this, set_info, kErrorBit, vuids);
                break;
            }
            default: {
                assert(0);
            }
        }
    }
}

TEST_F(VkLayerTest, CreatePipelineExceedMaxGeometryInstanceVertexCount) {
    TEST_DESCRIPTION(
        "Test that errors are produced when the number of output vertices/instances in the geometry stage exceeds the device "
        "limit");

    ASSERT_NO_FATAL_FAILURE(Init());
    ASSERT_NO_FATAL_FAILURE(InitRenderTarget());

    for (int overflow = 0; overflow < 2; ++overflow) {
        m_errorMonitor->Reset();
        VkPhysicalDeviceFeatures feat;
        vk::GetPhysicalDeviceFeatures(gpu(), &feat);
        if (!feat.geometryShader) {
            GTEST_SKIP() << "geometry shader stage unsupported";
        }

        std::string gsSourceStr = R"(
               OpCapability Geometry
               OpMemoryModel Logical GLSL450
               OpEntryPoint Geometry %main "main"
               OpExecutionMode %main InputPoints
               OpExecutionMode %main OutputTriangleStrip
               )";
        if (overflow) {
            gsSourceStr += "OpExecutionMode %main Invocations " +
                           std::to_string(m_device->props.limits.maxGeometryShaderInvocations + 1) +
                           "\n\
                OpExecutionMode %main OutputVertices " +
                           std::to_string(m_device->props.limits.maxGeometryOutputVertices + 1);
        } else {
            gsSourceStr += R"(
               OpExecutionMode %main Invocations 1
               OpExecutionMode %main OutputVertices 1
               )";
        }
        gsSourceStr += R"(
               OpSource GLSL 450
       %void = OpTypeVoid
          %3 = OpTypeFunction %void
       %main = OpFunction %void None %3
          %5 = OpLabel
               OpReturn
               OpFunctionEnd
        )";
        VkShaderObj gs(this, gsSourceStr.c_str(), VK_SHADER_STAGE_GEOMETRY_BIT, SPV_ENV_VULKAN_1_0, SPV_SOURCE_ASM);

        const auto set_info = [&](CreatePipelineHelper &helper) {
            helper.shader_stages_ = {helper.vs_->GetStageCreateInfo(), gs.GetStageCreateInfo(), helper.fs_->GetStageCreateInfo()};
        };
        if (overflow) {
            CreatePipelineHelper::OneshotTest(*this, set_info, kErrorBit,
                                              vector<string>{"VUID-VkPipelineShaderStageCreateInfo-stage-00714",
                                                             "VUID-VkPipelineShaderStageCreateInfo-stage-00715"});
        } else {
            CreatePipelineHelper::OneshotTest(*this, set_info, kErrorBit);
        }
    }
}

TEST_F(VkLayerTest, CreatePipelineTessPatchDecorationMismatch) {
    TEST_DESCRIPTION(
        "Test that an error is produced for a variable output from the TCS without the patch decoration, but consumed in the TES "
        "with the decoration.");

    ASSERT_NO_FATAL_FAILURE(Init());
    ASSERT_NO_FATAL_FAILURE(InitRenderTarget());

    if (!m_device->phy().features().tessellationShader) {
        GTEST_SKIP() << "Device does not support tessellation shaders";
    }

    char const *tcsSource = R"glsl(
        #version 450
        layout(location=0) out int x[];
        layout(vertices=3) out;
        void main(){
           gl_TessLevelOuter[0] = gl_TessLevelOuter[1] = gl_TessLevelOuter[2] = 1;
           gl_TessLevelInner[0] = 1;
           x[gl_InvocationID] = gl_InvocationID;
        }
    )glsl";
    char const *tesSource = R"glsl(
        #version 450
        layout(triangles, equal_spacing, cw) in;
        layout(location=0) patch in int x;
        void main(){
           gl_Position.xyz = gl_TessCoord;
           gl_Position.w = x;
        }
    )glsl";
    VkShaderObj tcs(this, tcsSource, VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT);
    VkShaderObj tes(this, tesSource, VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT);

    VkPipelineInputAssemblyStateCreateInfo iasci{VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO, nullptr, 0,
                                                 VK_PRIMITIVE_TOPOLOGY_PATCH_LIST, VK_FALSE};

    VkPipelineTessellationStateCreateInfo tsci{VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO, nullptr, 0, 3};

    const auto set_info = [&](CreatePipelineHelper &helper) {
        helper.gp_ci_.pTessellationState = &tsci;
        helper.gp_ci_.pInputAssemblyState = &iasci;
        helper.shader_stages_.emplace_back(tcs.GetStageCreateInfo());
        helper.shader_stages_.emplace_back(tes.GetStageCreateInfo());
    };
    CreatePipelineHelper::OneshotTest(*this, set_info, kErrorBit, "UNASSIGNED-CoreValidation-Shader-InterfacePatchVertex");
}

TEST_F(VkLayerTest, CreatePipelineTessErrors) {
    TEST_DESCRIPTION("Test various errors when creating a graphics pipeline with tessellation stages active.");

    ASSERT_NO_FATAL_FAILURE(Init());
    ASSERT_NO_FATAL_FAILURE(InitRenderTarget());

    if (!m_device->phy().features().tessellationShader) {
        GTEST_SKIP() << "Device does not support tessellation shaders";
    }

    char const *tcsSource = R"glsl(
        #version 450
        layout(vertices=3) out;
        void main(){
           gl_TessLevelOuter[0] = gl_TessLevelOuter[1] = gl_TessLevelOuter[2] = 1;
           gl_TessLevelInner[0] = 1;
        }
    )glsl";
    char const *tesSource = R"glsl(
        #version 450
        layout(triangles, equal_spacing, cw) in;
        void main(){
           gl_Position.xyz = gl_TessCoord;
           gl_Position.w = 0;
        }
    )glsl";
    VkShaderObj tcs(this, tcsSource, VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT);
    VkShaderObj tes(this, tesSource, VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT);

    VkPipelineInputAssemblyStateCreateInfo iasci{VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO, nullptr, 0,
                                                 VK_PRIMITIVE_TOPOLOGY_PATCH_LIST, VK_FALSE};

    VkPipelineTessellationStateCreateInfo tsci{VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO, nullptr, 0, 3};

    std::vector<VkPipelineShaderStageCreateInfo> shader_stages = {};
    VkPipelineInputAssemblyStateCreateInfo iasci_bad = iasci;
    VkPipelineInputAssemblyStateCreateInfo *p_iasci = nullptr;
    VkPipelineTessellationStateCreateInfo tsci_bad = tsci;
    VkPipelineTessellationStateCreateInfo *p_tsci = nullptr;

    const auto set_info = [&](CreatePipelineHelper &helper) {
        helper.gp_ci_.pTessellationState = p_tsci;
        helper.gp_ci_.pInputAssemblyState = p_iasci;
        helper.shader_stages_ = {helper.vs_->GetStageCreateInfo(), helper.fs_->GetStageCreateInfo()};
        helper.shader_stages_.insert(helper.shader_stages_.end(), shader_stages.begin(), shader_stages.end());
    };

    iasci_bad.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;  // otherwise we get a failure about invalid topology
    p_iasci = &iasci_bad;
    // Pass a tess control shader without a tess eval shader
    shader_stages = {tcs.GetStageCreateInfo()};
    CreatePipelineHelper::OneshotTest(*this, set_info, kErrorBit, "VUID-VkGraphicsPipelineCreateInfo-pStages-00729");

    // Pass a tess eval shader without a tess control shader
    shader_stages = {tes.GetStageCreateInfo()};
    CreatePipelineHelper::OneshotTest(*this, set_info, kErrorBit, "VUID-VkGraphicsPipelineCreateInfo-pStages-00730");

    p_iasci = &iasci;
    shader_stages = {};
    // Pass patch topology without tessellation shaders
    CreatePipelineHelper::OneshotTest(*this, set_info, kErrorBit, "VUID-VkGraphicsPipelineCreateInfo-topology-00737");

    shader_stages = {tcs.GetStageCreateInfo(), tes.GetStageCreateInfo()};
    // Pass a NULL pTessellationState (with active tessellation shader stages)
    CreatePipelineHelper::OneshotTest(*this, set_info, kErrorBit, "VUID-VkGraphicsPipelineCreateInfo-pStages-00731");

    // Pass an invalid pTessellationState (bad sType)
    tsci_bad.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    p_tsci = &tsci_bad;
    shader_stages = {tcs.GetStageCreateInfo(), tes.GetStageCreateInfo()};
    CreatePipelineHelper::OneshotTest(*this, set_info, kErrorBit, "VUID-VkPipelineTessellationStateCreateInfo-sType-sType");

    // Pass out-of-range patchControlPoints
    p_iasci = &iasci;
    tsci_bad = tsci;
    tsci_bad.patchControlPoints = 0;
    CreatePipelineHelper::OneshotTest(*this, set_info, kErrorBit,
                                      "VUID-VkPipelineTessellationStateCreateInfo-patchControlPoints-01214");

    tsci_bad.patchControlPoints = m_device->props.limits.maxTessellationPatchSize + 1;
    CreatePipelineHelper::OneshotTest(*this, set_info, kErrorBit,
                                      "VUID-VkPipelineTessellationStateCreateInfo-patchControlPoints-01214");

    p_tsci = &tsci;
    // Pass an invalid primitive topology
    iasci_bad = iasci;
    iasci_bad.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    p_iasci = &iasci_bad;
    CreatePipelineHelper::OneshotTest(*this, set_info, kErrorBit, "VUID-VkGraphicsPipelineCreateInfo-pStages-00736");
}

/*// TODO : This test should be good, but needs Tess support in compiler to run
TEST_F(VkLayerTest, InvalidPatchControlPoints)
{
    // Attempt to Create Gfx Pipeline w/o a VS
    VkResult err;

    m_errorMonitor->SetDesiredFailureMsg(kErrorBit, "Invalid Pipeline CreateInfo State: VK_PRIMITIVE_TOPOLOGY_PATCH primitive ");

    ASSERT_NO_FATAL_FAILURE(Init());
    ASSERT_NO_FATAL_FAILURE(InitRenderTarget());

    VkDescriptorPoolSize ds_type_count = {};
        ds_type_count.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        ds_type_count.descriptorCount = 1;

    VkDescriptorPoolCreateInfo ds_pool_ci = LvlInitStruct<VkDescriptorPoolCreateInfo>();
        ds_pool_ci.poolSizeCount = 1;
        ds_pool_ci.pPoolSizes = &ds_type_count;
    vk_testing::DescriptorPool ds_pool(*m_device, ds_pool_ci);

    VkDescriptorSetLayoutBinding dsl_binding = {};
        dsl_binding.binding = 0;
        dsl_binding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        dsl_binding.descriptorCount = 1;
        dsl_binding.stageFlags = VK_SHADER_STAGE_ALL;
        dsl_binding.pImmutableSamplers = NULL;

    VkDescriptorSetLayoutCreateInfo ds_layout_ci = LvlInitStruct<VkDescriptorSetLayoutCreateInfo>();
        ds_layout_ci.bindingCount = 1;
        ds_layout_ci.pBindings = &dsl_binding;

    vk_testing::DescriptorSetLayout ds_layout(*m_device, ds_layout_ci);

    VkDescriptorSet descriptorSet;
    err = vk::AllocateDescriptorSets(m_device->device(), ds_pool.handle(),
VK_DESCRIPTOR_SET_USAGE_NON_FREE, 1, &ds_layout.handle(), &descriptorSet);
    ASSERT_VK_SUCCESS(err);

    VkPipelineLayoutCreateInfo pipeline_layout_ci = LvlInitStruct<VkPipelineLayoutCreateInfo>();
        pipeline_layout_ci.pNext = NULL;
        pipeline_layout_ci.setLayoutCount = 1;
        pipeline_layout_ci.pSetLayouts = &ds_layout.handle();
    vk_testing::PipelineLayout pipeline_layout(*m_device, pipeline_layout_ci);
    ASSERT_VK_SUCCESS(err);

    VkPipelineShaderStageCreateInfo shaderStages[3];
    memset(&shaderStages, 0, 3 * sizeof(VkPipelineShaderStageCreateInfo));

    VkShaderObj vs(this,bindStateVertShaderText,VK_SHADER_STAGE_VERTEX_BIT);
    // Just using VS txt for Tess shaders as we don't care about functionality
    VkShaderObj tc(this,bindStateVertShaderText,VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT);
    VkShaderObj te(this,bindStateVertShaderText,VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT);

    shaderStages[0] = LvlInitStruct<VkPipelineShaderStageCreateInfo>();
    shaderStages[0].stage  = VK_SHADER_STAGE_VERTEX_BIT;
    shaderStages[0].shader = vs.handle();
    shaderStages[1] = LvlInitStruct<VkPipelineShaderStageCreateInfo>();
    shaderStages[1].stage  = VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
    shaderStages[1].shader = tc.handle();
    shaderStages[2] = LvlInitStruct<VkPipelineShaderStageCreateInfo>();
    shaderStages[2].stage  = VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT;
    shaderStages[2].shader = te.handle();

    VkPipelineInputAssemblyStateCreateInfo iaCI = LvlInitStruct<VkPipelineInputAssemblyStateCreateInfo>();
        iaCI.topology = VK_PRIMITIVE_TOPOLOGY_PATCH_LIST;

    VkPipelineTessellationStateCreateInfo tsCI = LvlInitStruct<VkPipelineTessellationStateCreateInfo>();
        tsCI.patchControlPoints = 0; // This will cause an error

    VkGraphicsPipelineCreateInfo gp_ci = LvlInitStruct<VkGraphicsPipelineCreateInfo>();
        gp_ci.stageCount = 3;
        gp_ci.pStages = shaderStages;
        gp_ci.pVertexInputState = NULL;
        gp_ci.pInputAssemblyState = &iaCI;
        gp_ci.pTessellationState = &tsCI;
        gp_ci.pViewportState = NULL;
        gp_ci.pRasterizationState = NULL;
        gp_ci.pMultisampleState = NULL;
        gp_ci.pDepthStencilState = NULL;
        gp_ci.pColorBlendState = NULL;
        gp_ci.flags = VK_PIPELINE_CREATE_DISABLE_OPTIMIZATION_BIT;
        gp_ci.layout = pipeline_layout.handle();
        gp_ci.renderPass = renderPass();

    VkPipelineCacheCreateInfo pc_ci = LvlInitStruct<VkPipelineCacheCreateInfo>();
        pc_ci.initialSize = 0;
        pc_ci.initialData = 0;
        pc_ci.maxSize = 0;

    VkPipeline pipeline;
    VkPipelineCache pipelineCache;

    err = vk::CreatePipelineCache(m_device->device(), &pc_ci, NULL,
&pipelineCache);
    ASSERT_VK_SUCCESS(err);
    err = vk::CreateGraphicsPipelines(m_device->device(), pipelineCache, 1,
&gp_ci, NULL, &pipeline);

    m_errorMonitor->VerifyFound();

    vk::DestroyPipelineCache(m_device->device(), pipelineCache, NULL);
}
*/