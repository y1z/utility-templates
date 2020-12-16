#include "operator_new_overloads.h"
#include <iostream>
#include <cstdlib>

struct AllocData
{
  uintmax_t allocationCount = 0u;
  uintmax_t deallocationCount = 0u;

  uintmax_t totalMemoryAllocated = 0u;
  uintmax_t totalMemoryDeallocated = 0u;

  uintmax_t registeredAllocationCount = 0u;
  uintmax_t registeredDeallocationCount = 0u;

  uintmax_t registeredMemoryAllocated = 0u;
  uintmax_t registeredMemoryDeallocated = 0u;
}data;

void
printMemoryStats()
{
  std::cout << "total Allocations = " <<  data.allocationCount << '\n'
    << "total Deallocations = " << data.deallocationCount << '\n'
    << "total memory allocated = "  << data.totalMemoryAllocated << " Bytes" << '\n'
    << "total memory deallocated = " << data.totalMemoryDeallocated << " Bytes" << '\n';
}

void
printRegisteredMemoryStats()
{
  std::cout << "registered Allocations = " << data.registeredAllocationCount << '\n'
    << "registered Deallocations = " << data.registeredDeallocationCount << '\n';
}

void
printDifferenceBetweenRegisteredAndMemoryStats()
{
  std::cout << "memory allocation delta total vs Registered = "
    << data.allocationCount - data.registeredAllocationCount << '\n';

  std::cout << "memory deallocation delta total vs Registered = "
    << data.deallocationCount - data.registeredDeallocationCount << '\n';

  std::cout << "memory allocated total delta current vs registered = "
    << data.totalMemoryAllocated - data.registeredMemoryAllocated << " Bytes" << '\n';

  std::cout << "memory deallocated total delta current vs registered = "
    << data.totalMemoryDeallocated - data.registeredMemoryDeallocated << " Bytes" << '\n';
}

void
registerMemoryStats()
{
  data.registeredAllocationCount = data.allocationCount;
  data.registeredDeallocationCount = data.deallocationCount;
  data.registeredMemoryAllocated = data.totalMemoryAllocated;
  data.registeredMemoryDeallocated = data.totalMemoryDeallocated;
}



void*
operator new(std::size_t AllocSize)
{
  data.allocationCount++;
  data.totalMemoryAllocated += AllocSize;


  return std::malloc(AllocSize);
}

void*
operator new[] (std::size_t AllocSize) 
{
  data.allocationCount++;
  data.totalMemoryAllocated += AllocSize;

  return std::malloc(AllocSize);
}

void
operator delete(void* Ptr) noexcept
{
  data.deallocationCount++;

  std::free(Ptr);
}

void
operator delete[](void* Ptr) noexcept 
{
  data.deallocationCount++;

  std::free(Ptr);
}

void 
operator delete(void* ptr,
                std::size_t DeallocSize) noexcept
{
  data.deallocationCount++;
  data.totalMemoryDeallocated += DeallocSize;

  std::free(ptr);
}

void 
operator delete[](void* ptr,
                  std::size_t DeallocSize) noexcept 
{
  data.deallocationCount++;
  data.totalMemoryDeallocated += DeallocSize;

  std::free(ptr);
}

