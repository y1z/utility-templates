#include <iostream>
#include "util/enCircularLinkList.h"
#include "include/operator_new_overloads.h"

int main()
{
  {
    enCircularLinkList<int> intList;

    for( int32_t i = 0; i < 10; ++i )
    {

      intList.addNode(1);
    }
    intList.addNode(2);
  }


  std::cout << "hello c++ 20 \n";
}