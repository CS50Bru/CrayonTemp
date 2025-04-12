//keeps a buffer together with its memory allocation

#pragma once
#include "Libraries/vma/vk_mem_alloc.h"


namespace Crayon
{
    struct AllocatedBuffer
    {
    public:
        VkBuffer buffer = VK_NULL_HANDLE;
        VmaAllocation allocation = {};
        size_t size = 0;
    };


    struct FastGpuBuffer
    {
        AllocatedBuffer gpuBuffer;
        AllocatedBuffer stagingBuffer;
    };

}