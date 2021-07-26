/*
* Shouldn't be just one header file for this but oh well
* Only used for OP mode.
*/
#pragma once
#include <minwindef.h>
#include <memoryapi.h>
#include <vector>

namespace mem {
	void Patch(BYTE* dst, BYTE* src, const size_t size)
    {
        DWORD old_protect;
        VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &old_protect);
        memcpy(dst, src, size);
        VirtualProtect(dst, size, old_protect, &old_protect);
    }

    void Nop(BYTE* dst, const size_t size)
    {
        DWORD old_protect;
        VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &old_protect);
        memset(dst, 0x90, size);
        VirtualProtect(dst, size, old_protect, &old_protect);
    }

    uintptr_t FindDMAAddy(const uintptr_t ptr, const std::vector<unsigned int>& offsets)
    {
        uintptr_t addr = ptr;

        for (unsigned int offset : offsets)
        {
            addr = *reinterpret_cast<uintptr_t*>(addr);
            addr += offset;
        }
        return addr;
    }
}