#include "pipeline_sub_state.h"

#include "state_tracker.h"

VertexInputState::VertexInputState(const safe_VkGraphicsPipelineCreateInfo &create_info)
    : input_state(create_info.pVertexInputState), input_assembly_state(create_info.pInputAssemblyState) {
    if (create_info.pVertexInputState) {
        const auto *vici = create_info.pVertexInputState;
        if (vici->vertexBindingDescriptionCount) {
            const auto count = vici->vertexBindingDescriptionCount;
            binding_descriptions.reserve(count);
            binding_to_index_map.reserve(count);

            for (uint32_t i = 0; i < count; i++) {
                binding_descriptions.emplace_back(vici->pVertexBindingDescriptions[i]);
                binding_to_index_map[binding_descriptions.back().binding] = i;
            }
        }

        if (vici->vertexAttributeDescriptionCount) {
            vertex_attribute_descriptions.reserve(vici->vertexAttributeDescriptionCount);
            std::copy(vici->pVertexAttributeDescriptions,
                      vici->pVertexAttributeDescriptions + vici->vertexAttributeDescriptionCount,
                      std::back_inserter(vertex_attribute_descriptions));
        }

        vertex_attribute_alignments.reserve(vertex_attribute_descriptions.size());
        for (const auto &attr : vertex_attribute_descriptions) {
            VkDeviceSize vtx_attrib_req_alignment = FormatElementSize(attr.format);
            if (FormatElementIsTexel(attr.format)) {
                vtx_attrib_req_alignment = SafeDivision(vtx_attrib_req_alignment, FormatComponentCount(attr.format));
            }
            vertex_attribute_alignments.push_back(vtx_attrib_req_alignment);
        }
    }
}

PreRasterState::PreRasterState(const ValidationStateTracker &dev_data, const safe_VkGraphicsPipelineCreateInfo &create_info)
    : subpass(create_info.subpass) {
    pipeline_layout = dev_data.Get<PIPELINE_LAYOUT_STATE>(create_info.layout);

    viewport_state = create_info.pViewportState;

    rp_state = dev_data.Get<RENDER_PASS_STATE>(create_info.renderPass);

    raster_state = create_info.pRasterizationState;

    tess_create_info = create_info.pTessellationState;

    for (uint32_t i = 0; i < create_info.stageCount; ++i) {
        // TODO might need to filter out more than just fragment shaders here
        if (create_info.pStages[i].stage != VK_SHADER_STAGE_FRAGMENT_BIT) {
            auto module_state = dev_data.Get<SHADER_MODULE_STATE>(create_info.pStages[i].module);
            if (!module_state) {
                // If module is null and there is a VkShaderModuleCreateInfo in the pNext chain of the stage info, then this
                // module is part of a library and the state must be created
                const auto shader_ci = LvlFindInChain<VkShaderModuleCreateInfo>(create_info.pStages[i].pNext);
                if (shader_ci) {
                    const uint32_t unique_shader_id = 0;  // TODO GPU-AV rework required to get this value properly
                    module_state = dev_data.CreateShaderModuleState(*shader_ci, unique_shader_id);
                }
            }

            if (module_state) {
                const auto *stage_ci = &create_info.pStages[i];
                switch (create_info.pStages[i].stage) {
                    case VK_SHADER_STAGE_VERTEX_BIT:
                        vertex_shader = std::move(module_state);
                        vertex_shader_ci = stage_ci;
                        break;
                    case VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT:
                        tessc_shader = std::move(module_state);
                        tessc_shader_ci = stage_ci;
                        break;
                    case VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT:
                        tesse_shader = std::move(module_state);
                        tesse_shader_ci = stage_ci;
                        break;
                    case VK_SHADER_STAGE_GEOMETRY_BIT:
                        geometry_shader = std::move(module_state);
                        geometry_shader_ci = stage_ci;
                        break;
                    // TODO mesh shaders?
                    default:
                        // TODO is this an error?
                        break;
                }
            }
        }
    }
}

std::unique_ptr<const safe_VkPipelineColorBlendStateCreateInfo> ToSafeColorBlendState(
    const safe_VkPipelineColorBlendStateCreateInfo &cbs) {
    // This is needlessly copied here. Might better to make this a plain pointer, with an optional "backing unique_ptr"
    return layer_data::make_unique<const safe_VkPipelineColorBlendStateCreateInfo>(cbs);
}
std::unique_ptr<const safe_VkPipelineColorBlendStateCreateInfo> ToSafeColorBlendState(
    const VkPipelineColorBlendStateCreateInfo &cbs) {
    return layer_data::make_unique<const safe_VkPipelineColorBlendStateCreateInfo>(&cbs);
}
std::unique_ptr<const safe_VkPipelineMultisampleStateCreateInfo> ToSafeMultisampleState(
    const safe_VkPipelineMultisampleStateCreateInfo &cbs) {
    // This is needlessly copied here. Might better to make this a plain pointer, with an optional "backing unique_ptr"
    return layer_data::make_unique<const safe_VkPipelineMultisampleStateCreateInfo>(cbs);
}
std::unique_ptr<const safe_VkPipelineMultisampleStateCreateInfo> ToSafeMultisampleState(
    const VkPipelineMultisampleStateCreateInfo &cbs) {
    return layer_data::make_unique<const safe_VkPipelineMultisampleStateCreateInfo>(&cbs);
}
std::unique_ptr<const safe_VkPipelineDepthStencilStateCreateInfo> ToSafeDepthStencilState(
    const safe_VkPipelineDepthStencilStateCreateInfo &cbs) {
    // This is needlessly copied here. Might better to make this a plain pointer, with an optional "backing unique_ptr"
    return layer_data::make_unique<const safe_VkPipelineDepthStencilStateCreateInfo>(cbs);
}
std::unique_ptr<const safe_VkPipelineDepthStencilStateCreateInfo> ToSafeDepthStencilState(
    const VkPipelineDepthStencilStateCreateInfo &cbs) {
    return layer_data::make_unique<const safe_VkPipelineDepthStencilStateCreateInfo>(&cbs);
}
std::unique_ptr<const safe_VkPipelineShaderStageCreateInfo> ToShaderStageCI(const safe_VkPipelineShaderStageCreateInfo &cbs) {
    // This is needlessly copied here. Might better to make this a plain pointer, with an optional "backing unique_ptr"
    return layer_data::make_unique<const safe_VkPipelineShaderStageCreateInfo>(cbs);
}
std::unique_ptr<const safe_VkPipelineShaderStageCreateInfo> ToShaderStageCI(const VkPipelineShaderStageCreateInfo &cbs) {
    return layer_data::make_unique<const safe_VkPipelineShaderStageCreateInfo>(&cbs);
}

template <typename CreateInfo>
void SetFragmentShaderInfoPrivate(FragmentShaderState &fs_state, const ValidationStateTracker &state_data,
                                  const CreateInfo &create_info) {
    for (uint32_t i = 0; i < create_info.stageCount; ++i) {
        if (create_info.pStages[i].stage == VK_SHADER_STAGE_FRAGMENT_BIT) {
            auto module_state = state_data.Get<SHADER_MODULE_STATE>(create_info.pStages[i].module);
            if (!module_state) {
                // If module is null and there is a VkShaderModuleCreateInfo in the pNext chain of the stage info, then this
                // module is part of a library and the state must be created
                const auto shader_ci = LvlFindInChain<VkShaderModuleCreateInfo>(create_info.pStages[i].pNext);
                if (shader_ci) {
                    const uint32_t unique_shader_id = 0;  // TODO GPU-AV rework required to get this value properly
                    module_state = state_data.CreateShaderModuleState(*shader_ci, unique_shader_id);
                }
            }

            if (module_state) {
                fs_state.fragment_shader = std::move(module_state);
                fs_state.fragment_shader_ci = ToShaderStageCI(create_info.pStages[i]);
            }
        }
    }
}

// static
void FragmentShaderState::SetFragmentShaderInfo(FragmentShaderState &fs_state, const ValidationStateTracker &state_data,
                                                const VkGraphicsPipelineCreateInfo &create_info) {
    SetFragmentShaderInfoPrivate(fs_state, state_data, create_info);
}

// static
void FragmentShaderState::SetFragmentShaderInfo(FragmentShaderState &fs_state, const ValidationStateTracker &state_data,
                                                const safe_VkGraphicsPipelineCreateInfo &create_info) {
    SetFragmentShaderInfoPrivate(fs_state, state_data, create_info);
}

FragmentShaderState::FragmentShaderState(const ValidationStateTracker &dev_data, VkRenderPass rp, uint32_t subp,
                                         VkPipelineLayout layout)
    : rp_state(dev_data.Get<RENDER_PASS_STATE>(rp)), subpass(subp), pipeline_layout(dev_data.Get<PIPELINE_LAYOUT_STATE>(layout)) {}

FragmentOutputState::FragmentOutputState(const ValidationStateTracker &dev_data, VkRenderPass rp, uint32_t sp)
    : rp_state(dev_data.Get<RENDER_PASS_STATE>(rp)), subpass(sp) {}

// static
bool FragmentOutputState::IsBlendConstantsEnabled(const AttachmentVector &attachments) {
    bool result = false;
    for (const auto &attachment : attachments) {
        if (VK_TRUE == attachment.blendEnable) {
            if (((attachment.dstAlphaBlendFactor >= VK_BLEND_FACTOR_CONSTANT_COLOR) &&
                 (attachment.dstAlphaBlendFactor <= VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_ALPHA)) ||
                ((attachment.dstColorBlendFactor >= VK_BLEND_FACTOR_CONSTANT_COLOR) &&
                 (attachment.dstColorBlendFactor <= VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_ALPHA)) ||
                ((attachment.srcAlphaBlendFactor >= VK_BLEND_FACTOR_CONSTANT_COLOR) &&
                 (attachment.srcAlphaBlendFactor <= VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_ALPHA)) ||
                ((attachment.srcColorBlendFactor >= VK_BLEND_FACTOR_CONSTANT_COLOR) &&
                 (attachment.srcColorBlendFactor <= VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_ALPHA))) {
                result = true;
                break;
            }
        }
    }
    return result;
}