#include "operator_new_overloads.h"
#include <iostream>
#include <cstdlib>

struct AllocData
{
  AllocData()
    :allocationCount(0u),
    deallocationCount(0u),

    totalMemoryAllocated(0u),
    totalMemoryDeallocated(0u),

    registeredAllocationCount(0u),
    registeredDeallocationCount(0u),

    registeredMemoryAllocated(0u),
    registeredMemoryDeallocated(0u)
  {}

  bool operator ==(const AllocData other)const
  {
    const uintmax_t * startOfArray = std::cbegin(arrayRepresentation);
    const auto endOfArray = std::cend(arrayRepresentation);
    std::size_t otherIndex = 0u;
    while( startOfArray != endOfArray )
    {
      if( *startOfArray != other.arrayRepresentation[otherIndex] )
      {
        return false;
      }
      ++otherIndex;
      ++startOfArray;
    }
    return true;
  }

  bool operator !=(const AllocData other)const
  {
    return !(*this == other);
  }

  union
  {

    struct
    {
      uintmax_t allocationCount;
      uintmax_t deallocationCount;

      uintmax_t totalMemoryAllocated;
      uintmax_t totalMemoryDeallocated;

      uintmax_t registeredAllocationCount;
      uintmax_t registeredDeallocationCount;

      uintmax_t registeredMemoryAllocated;
      uintmax_t registeredMemoryDeallocated;
    };
    uintmax_t arrayRepresentation[8];
  };
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

bool 
resetStats()
{
  const AllocData temp = AllocData();

  const bool shouldDataBeReset = (data == temp);

  if( shouldDataBeReset )
  {
    std::cout << "resetting stats\n\n";
    auto startArray = std::begin(data.arrayRepresentation);
    auto const endArray = std::cend(data.arrayRepresentation);
    while( startArray != endArray )
    {
      *startArray = 0u;
      ++startArray;
    }
  }
  return shouldDataBeReset;
}

void*
operator new(std::size_t AllocSize)
{
  data.allocationCount++;
  data.totalMemoryAllocated += AllocSize;


  return std::malloc(AllocSize);
}

void*
operator new[](std::size_t AllocSize)
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


