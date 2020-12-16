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

void* 
operator new(std::size_t AllocSize);

void*
operator new[](std::size_t AllocSize);


void
operator delete(void* Ptr) noexcept;


void
operator delete[](void* Ptr) noexcept;

void 
operator delete  (void* ptr,
                  std::size_t DeallocSize) noexcept;

void 
operator delete[](void* ptr,
                  std::size_t DeallocSize) noexcept;


