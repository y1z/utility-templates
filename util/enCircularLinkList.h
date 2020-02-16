#pragma once
#include <iostream>
#include <cstddef>
#include <utility>
#include <cassert>
/**
* @LC     2020/Feb/08
* @file   enCircularLinkList.h
* @author Yhaliff Said Barraza
* @date   2020/Feb/15
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

  /**
  * @brief : default constructor required to make the Circular Link List.
  * @bug : no known bugs
  */
  enCircularLinkList() 
  {
    m_rootNode.mptr_next = &this->m_rootNode;
  }

  /**
  * @brief : copy constructor
  * @bug : no known bugs
  */
  enCircularLinkList(const enCircularLinkList& listToCopy)
    :enCircularLinkList()
  {
    this->m_rootNode.m_var = listToCopy.m_rootNode.m_var;

    node * otherListCurrentNode = listToCopy.mptr_firstNode->mptr_next;
    node * currentNode = this->mptr_firstNode;
    while( otherListCurrentNode != listToCopy.mptr_firstNode )
    {
      currentNode->mptr_next = new node();
      currentNode = currentNode->mptr_next;

      currentNode->m_var = otherListCurrentNode->m_var;
      currentNode->nodeIndex = otherListCurrentNode->nodeIndex;
      otherListCurrentNode = otherListCurrentNode->mptr_next;
    }
    currentNode->mptr_next = this->mptr_firstNode;
  }

  /**
  * @brief : move constructor
  * @bug : no known bugs
  */
  enCircularLinkList(enCircularLinkList&& listToMove)
    :enCircularLinkList()
  {
    this->m_rootNode.mptr_next = listToMove.m_rootNode.mptr_next;
    listToMove.m_rootNode.mptr_next = &listToMove.m_rootNode;
    this->m_rootNode.m_var = std::move(this->m_rootNode.m_var);

  }

  ~enCircularLinkList()
  {
    node* currentNode = mptr_firstNode->mptr_next;
    node* prevNode = mptr_firstNode;
    while( currentNode->nodeIndex != 0)
    {
      prevNode = currentNode;
      currentNode = currentNode->mptr_next; 

      prevNode->mptr_next = nullptr; 
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
    nodeIndex = 0u;

    /**
    * @brief : is a pointer to the next element or the beginning of the circular list.
    */
    node*
    mptr_next = nullptr;

  };

private
  /**
  * @brief :this is the first node in the list and it's index will be 0.
  */:
  node  m_rootNode;

  /**
  * @brief : this is a pointer to the first node will be used to know when
  * we have gone through the entire list
  */
  node *const mptr_firstNode = &m_rootNode;

  size_t m_nodeCount = 0u;

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
      result->m_var;
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
    node* currentNode =  m_rootNode.mptr_next;
    size_t nodeIndex = 1u;
    while( currentNode->mptr_next != mptr_firstNode)
    {
      currentNode = currentNode->mptr_next;
      nodeIndex++;
    }

    currentNode->mptr_next = new node();
    currentNode = currentNode->mptr_next;

    currentNode->m_var = value;
    currentNode->nodeIndex = nodeIndex;
    currentNode->mptr_next = mptr_firstNode;
    m_nodeCount++;
  }


  /**
  * @brief : adds a new node to the end of the list.
  * @param value[in] : the value that going to be stored in the new node.
  * @bug : no known bugs.
  */
  template<class StoredType> void
  addNode(StoredType && value) 
  {
    node* currentNode = m_rootNode.mptr_next;
    size_t nodeIndex = 1u;
    while( currentNode != mptr_firstNode)
    {
      currentNode = currentNode->mptr_next;
      nodeIndex++;
    }

    currentNode->mptr_next = new node();
    currentNode = currentNode->mptr_next;

    currentNode->m_var = value;
    currentNode->nodeIndex = nodeIndex;
    currentNode->mptr_next = mptr_firstNode;
    m_nodeCount++;
  }

  size_t
  getNodeCount()const
  {
    return m_nodeCount;
  }

  StoredType 
  getCopy(size_t Index = 0)
  {
    return Impl_getCopy<StoredType>(Index);
  }

  StoredType *
  getPtr(size_t Index = 0)
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
  Impl_getCopy(size_t Index = 0)  
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
  Impl_getPtr(size_t  Index = 0) 
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
      return mptr_firstNode;

    enCircularLinkList<StoredType>::node* currentNode = m_rootNode.mptr_next;
    while( currentNode->nodeIndex != 0 )
    {
      if(currentNode->nodeIndex == Index )
        return currentNode;

        currentNode = currentNode->mptr_next; 
    }

    return nullptr;
  }
};


