#pragma once
#include <cstddef>

void 
printMemoryStats();

void
printRegisteredMemoryStats();

void
printDifferenceBetweenRegisteredAndMemoryStats();

void
registerMemoryStats();

/** @returns true when the stats are reset, false otherwise.*/
bool
resetStats();

void* 
operator new(std::size_t AllocSize);

void*
operator new[](std::size_t AllocSize);


void
operator delete(void* Ptr) noexcept;


void
operator delete[](void* Ptr) noexcept;

void 
operator delete(void* ptr,
                std::size_t DeallocSize) noexcept;

void 
operator delete[](void* ptr,
                  std::size_t DeallocSize) noexcept;


