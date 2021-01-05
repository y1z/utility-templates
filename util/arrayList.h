#pragma once
#include <bitset>
#include <array>
#include <cstdint>




/**
 * @class arrayListTemplate : Is a link list but every node contains a array of 
 * elements instead of individual elements
 */
template <class type, 
  uint16_t arraySize>
class arrayListTemplate 
{
public:

  /** @brief defines a node for the array list */
  struct node 
  {
    /** @brief a pointer to the next node.*/
    node* m_next = nullptr;

    /** @brief contains the individual elements. */
    std::array<type,arraySize> m_elements;

    /** @brief zero means a index is free, 1 means it's occupied. */
    std::bitset<arraySize> m_indexTracker;
  };

public:
  bool
  init(const type& element)
  {
    if( nullptr == m_firstNode )
    {
      m_firstNode = new node();
      m_firstNode->addElem( );
    }
    else
    {
      return false;
    }
    
  }

private:
  node* m_firstNode = nullptr;
};



template<class type>
using arrayList = arrayListTemplate<type,16u>;
