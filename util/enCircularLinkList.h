#pragma once
#include <iostream>
#include <cstdint>
#include <utility>
#include <cassert>
/**
* @LC     2020/Dec/22
* @file   enCircularLinkList.h
* @author Yhaliff Said Barraza
* @date   2020/Feb/25
* @brief  is a circular link list data structure
* @bug	   No known bugs.
*/


/**
* @brief : this link-list links the last node with the first one
*/
template <class StoredType>
class enCircularLinkList
{
public:
  using containedType = StoredType;
  using containedTypePtr = StoredType*;
  using containedTypeRef = StoredType&;

public:
  /**
   * @brief represents the individual elements of the link list.
   */
  struct node
  {
    /**
    * @brief : this is the value that being stored in the node.
    */
    StoredType
    m_var;

    /**
    * @brief : this will be used to know where the node is in the Circular Link List
    */
    int64_t
    m_nodeIndex = INT64_C(0);

    /**
    * @brief : is a pointer to the next element.
    */
    node*
    m_ptrNext = nullptr;

    /**
     * @brief ; it's a pointer to a previous node.
     */
    node*
    m_ptrPrev = nullptr;

  };

public:

  /**
  * @brief : default constructor required to make the Circular Link List.
  * @bug : no known bugs
  */
  enCircularLinkList() 
    :m_firstNode(new node()),
    m_nodeCount(INT64_C(0))
  {}

  /**
  * @brief : copy constructor
  * @bug : no known bugs
  */
  enCircularLinkList(const enCircularLinkList& listToCopy)
  {
    this->m_firstNode = listToCopy.m_firstNode;
    listToCopy.m_firstNode = nullptr;
  }

  /**
  * @brief : move constructor
  * @bug : no known bugs
  */
  enCircularLinkList(enCircularLinkList&& listToMove) noexcept
    :enCircularLinkList()
  {
    // TODO : IMPLEMENT MOVE
    assert(false);
  }

  ~enCircularLinkList()
  {
    clear();
  };
  
public:
  enCircularLinkList&
  operator=(const enCircularLinkList& other)
  {
    enCircularLinkList copy(other);
    *this = std::move(copy);
    return *this;
  }

  enCircularLinkList&
  operator=(enCircularLinkList&& other) noexcept
  {
    if( this != &other )
    {
      this->clear();
      m_firstNode = other.m_firstNode;
      m_nodeCount = other.m_nodeCount;
      other.m_firstNode = nullptr;
      other.m_nodeCount = -1;    
    }
    return *this;
  }


public: // FUNCTIONS
  /**
  * @brief : set the value that going to be used by the node.
  * @param[in] value : is the value that going to be stored by the circular link list.
  * @bug : no known bugs
  */
  void
  setValue(const containedType& value,
           const int64_t Index = 0)
  {
    if( Index == 0 )
    {
      m_firstNode->m_var = value;
    }
    else
    {
      node*const result = getNode(Index);
      result->m_var = value;
    }
  }

  /**
  * @brief : adds a new node to the end of the list.
  * @param value[in] : the value that going to be stored in the new node.
  * @bug : no known bugs.
  */
  void
  addNode(const containedType& value) 
  {
    node* currentNode = getNode(m_nodeCount);
    currentNode->m_ptrNext = new node();

    node* nextNode = currentNode->m_ptrNext;
    nextNode->m_var = value;

    interconnectNodes(nextNode, m_firstNode);
    interconnectNodes(currentNode, nextNode);
    m_nodeCount++;
  }


  /**
  * @brief : adds a new node to the end of the list.
  * @param value[in] : the value that going to be stored in the new node.
  * @bug : no known bugs.
  */
  void
  addNode(containedType&& value)
  {
    node* currentNode = getNode(m_nodeCount);
    currentNode->m_ptrNext = new node();

    node* nextNode = currentNode->m_ptrNext;
    nextNode->m_var = std::forward<containedType>(value);

    interconnectNodes(nextNode, m_firstNode);
    interconnectNodes(currentNode, nextNode);
    m_nodeCount++;
  }

  bool
  removeNode(const int64_t Index)
  {
    const bool isIndexValid = (Index < m_nodeCount && Index > -1);

    if( isIndexValid )
    {
      node* nodeToRemove = getNode(Index);
      interconnectNodes(nodeToRemove->m_ptrPrev, nodeToRemove->m_ptrNext);
      delete nodeToRemove;
      --m_nodeCount;
    }

    return isIndexValid;
  }

  int64_t
  getNodeCount()const
  {
    return m_nodeCount;
  }

  containedType
  getCopy(const int64_t Index)
  {
    return Impl_getCopy(Index);
  }

  containedType*
  getPtr(const int64_t Index)
  {
    return Impl_getPtr(Index);
  }

  containedType&
  getRef(const int64_t Index)
  {
    StoredType * result = Impl_getPtr(Index);
    assert(result != nullptr && "trying to access index that does not exist");
    return  *result;
  }

  void
  clear() noexcept
  {
    if( nullptr != m_firstNode )
    {
      node* currentNode = m_firstNode->m_ptrPrev;
      while( currentNode != m_firstNode || nullptr != currentNode )
      {
        node* nextNodeToRemove = currentNode;
        delete currentNode;
        currentNode = nextNodeToRemove;
      }
      delete m_firstNode;
      m_firstNode = nullptr;
      m_nodeCount = INT64_C(0);
    }
  }

  static inline void 
  interconnectNodes(node* prevNode,
                    node* nextNode)
  {
    prevNode->m_ptrNext = nextNode; 
    nextNode->m_ptrPrev = prevNode;
  }


private: // FUNCTIONS

  /**
  *  @brief : used to find nodes
  *  @return : a pointer to the desired node if it exist
  *  @param[in] Index : which index to find
  *  @bug : no known bugs.
  */
  node*
  getNode(const int64_t Index)
  {
    if( Index == 0 )
      return m_firstNode;

    node* currentNode = m_firstNode->m_ptrNext;
    while( currentNode->m_nodeIndex != 0 )
    {
      if(currentNode->m_nodeIndex == Index )
        return currentNode;

        currentNode = currentNode->m_ptrNext; 
    }

    return nullptr;
  }

  /**
  * @brief : implementation
  * @returns : a copy of the stored value 
  * @param : the index of the element
  * @bug : no known bugs
  */
  containedType
  Impl_getCopy(const int64_t Index)
  {
    if(Index == 0)
      return m_firstNode->m_var;

    node* result = getNode(Index);
    if(result != nullptr)
    {
      return result->m_var;
    }
    return StoredType();
  }

  /**
  * @returns : a references to the stored value
  * @bug : no known bugs
  */
  containedType*
  Impl_getPtr(const int64_t Index) 
  {
    if(Index == 0)
      return &m_firstNode->m_var;

    node* result = getNode(Index);
    if( result != nullptr  )
    {
      return &result->m_var;
    }

    return nullptr;
  }



private:// variables

  /**
   * @brief the start of the linkList.
  */
  node *m_firstNode; 

  /** @brief the amount of node in the link list. */
  int64_t m_nodeCount = INT64_C(0);
};

