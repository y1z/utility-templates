#pragma once
#include <bitset>
#include <array>
#include <cstdint>




template <class type, uint16_t arraySize>
class arrayListTemplate 
{
public:

  /** @brief defines a node for the array list */
  struct node 
  {
    /** @brief contains the individual elements. */
    std::array<type,arraySize> m_elements;

    /** @brief zero means a index is free, 1 means it's occupied. */
    std::bitset<arraySize> m_elementTracker;
  };
  
};



template<class type>
using arrayList = arrayListTemplate<type,16u>;
