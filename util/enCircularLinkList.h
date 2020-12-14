#pragma once
#include <iostream>
#include <cstddef>
#include <utility>
#include <cassert>
/**
* @LC     2020/Feb/08
* @file   enCircularLinkList.h
* @author Yhaliff Said Barraza
* @date   2020/Feb/25
* @brief  is a circular link list data structure
*
* @bug	   No known bugs.
*/


  /**
  * @brief : this link-list links the last node with the first one
  */
template <class StoredType>
class enCircularLinkList
{
public:
  using type = StoredType;
  using typePtr = StoredType*;
  using typeRef = StoredType&;
public:

  /**
  * @brief : default constructor required to make the Circular Link List.
  * @bug : no known bugs
  */
  enCircularLinkList() 
  {
    m_rootNode.m_ptrNext = &this->m_rootNode;
    m_rootNode.m_ptrPrev = &this->m_rootNode;
  }

  /**
  * @brief : copy constructor
  * @bug : no known bugs
  */
  enCircularLinkList(const enCircularLinkList& listToCopy)
    :enCircularLinkList()
  {
    this->m_rootNode.m_var = listToCopy.m_rootNode.m_var;

    node * otherListCurrentNode = listToCopy.m_firstNode->m_ptrNext;
    node * currentNode = this->m_firstNode;
    while( otherListCurrentNode != listToCopy.m_firstNode )
    {
      currentNode->m_ptrNext = new node();
      currentNode = currentNode->m_ptrNext;

      currentNode->m_var = otherListCurrentNode->m_var;
      currentNode->m_nodeIndex = otherListCurrentNode->m_nodeIndex;
      otherListCurrentNode = otherListCurrentNode->m_ptrNext;
    }
    currentNode->m_ptrNext = this->m_firstNode;
  }

  /**
  * @brief : move constructor
  * @bug : no known bugs
  */
  enCircularLinkList(enCircularLinkList&& listToMove) noexcept
    :enCircularLinkList()
  {
    this->m_rootNode.m_ptrNext = listToMove.m_rootNode.m_ptrNext;
    listToMove.m_rootNode.m_ptrNext = &listToMove.m_rootNode;
    this->m_rootNode.m_var = std::move(this->m_rootNode.m_var);
  }

  ~enCircularLinkList()
  {
    node* currentNode = m_firstNode->m_ptrNext;
    node* prevNode = m_firstNode;
    while( currentNode->m_nodeIndex != 0)
    {
      prevNode = currentNode;
      currentNode = currentNode->m_ptrNext; 

      prevNode->m_ptrNext = nullptr; 
      delete prevNode;
    }

  };

  /**
  * @brief :this will represent the individual element's in the list 
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
    size_t
    m_nodeIndex = 0u;

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

  enCircularLinkList&
  operator=(enCircularLinkList&& other )
  {
    if( this != &other )
    {
      
    }
    
    return *this;
  }


public: // FUNCTIONS
  /**
  * @brief : set the value that going to be used by the node.
  * @param[in] value : is the value that going to be stored by the circular link list.
  * @bug : no known bugs
  */
  template<class StoredType> void
  setValue(const StoredType& value, size_t Index = 0) 
  {
    if( Index == 0 )
      m_rootNode.m_var = value;
    else
    {
      node* result = getNodeInIndex<StoredType>(Index);
      result->m_var = value;
    }
  }

  /**
  * @brief : adds a new node to the end of the list.
  * @param value[in] : the value that going to be stored in the new node.
  * @bug : no known bugs.
  */
  template<class StoredType> void
  addNode(StoredType & value) 
  {
    node* currentNode = &m_rootNode;
    node* prevNode = &m_rootNode;

    if( m_nodeCount != 0u )
    {
      while( currentNode->m_ptrNext != m_firstNode )
      {
        prevNode = currentNode;
        currentNode = currentNode->m_ptrNext;
      }

      currentNode->m_ptrNext = new node();
      currentNode->m_ptrPrev = prevNode;
      currentNode = currentNode->m_ptrNext;

      currentNode->m_var = value;
      currentNode->m_nodeIndex = m_nodeCount++;
      currentNode->m_ptrNext = m_firstNode;
    }
    else
    {
      m_rootNode.m_var = value;
      m_nodeCount++;
    }

  }


  /**
  * @brief : adds a new node to the end of the list.
  * @param value[in] : the value that going to be stored in the new node.
  * @bug : no known bugs.
  */
  template<class StoredType> void
  addNode(StoredType && value) 
  {
    node* currentNode = &m_rootNode;
    node* prevNode = &m_rootNode;

    if( m_nodeCount != 0u )
    {
      while( currentNode->m_ptrNext != m_firstNode )
      {
        prevNode = currentNode;
        currentNode = currentNode->m_ptrNext;
      }

      currentNode->m_ptrNext = new node();
      currentNode->m_ptrPrev = prevNode;
      currentNode = currentNode->m_ptrNext;

      currentNode->m_var = value;
      currentNode->m_nodeIndex = m_nodeCount++;
      currentNode->m_ptrNext = m_firstNode;
    }
    else
    {
      m_rootNode.m_var = value;
      m_nodeCount++;
    }
  }

  size_t
  getNodeCount()const
  {
    return m_nodeCount;
  }

  StoredType 
  getCopy(size_t Index)
  {
    return Impl_getCopy<StoredType>(Index);
  }

  StoredType *
  getPtr(size_t Index)
  {
    return Impl_getPtr<StoredType>(Index);
  }

  StoredType&
  getRef(size_t Index = 0)
  {
    StoredType * result = Impl_getPtr<StoredType>(Index);
    assert(result != nullptr && "trying to access index hat does not exist");
    return  *result;
  }

private: // FUNCTIONS


  /**
  * @brief : implementation
  * @returns : a copy of the stored value 
  * @param : the index of the element
  * @bug : no known bugs
  */
  template<class StoredType > StoredType
  Impl_getCopy(size_t Index)  
  {
    if(Index == 0)
      return m_rootNode.m_var;

    node* result = getNodeInIndex<StoredType>(Index);
    if(result != nullptr)
    {
      return result->m_var;
    }

    return StoredType();
   // throw std::out_of_range;
  }

  /**
  * @returns : a references to the stored value
  * @bug : no known bugs
  */
  template<class StoredType> StoredType*
  Impl_getPtr(size_t Index) 
  {
    if(Index == 0)
      return &m_rootNode.m_var;

    node* result = this->getNodeInIndex<StoredType>(Index); 
    if( result != nullptr  )
    {
      return &result->m_var;
    }

    return nullptr;
  }


  /**
  *  @brief : used to find nodes
  *  @return : a pointer to the desired node if it exist
  *  @param[in] Index : which index to find
  *  @bug : no known bugs.
  */
  template<class StoredType> node*
  getNodeInIndex(size_t Index)
  {
    if( Index == 0 )
      return m_firstNode;

    enCircularLinkList<StoredType>::node* currentNode = m_rootNode.m_ptrNext;
    while( currentNode->m_nodeIndex != 0 )
    {
      if(currentNode->m_nodeIndex == Index )
        return currentNode;

        currentNode = currentNode->m_ptrNext; 
    }

    return nullptr;
  }

private:// variables
  /**
  * @brief :this is the first node in the list and it's index will be 0.
  */
  node  m_rootNode;

  /**
  * @brief : this is a pointer to the first node will be used to know when
  * we have gone through the entire list
  */
  node *const m_firstNode = &m_rootNode;

  size_t m_nodeCount = 0u;
};


