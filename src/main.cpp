#include <iostream>
#include <climits>
#include "util/enCircularLinkList.h"
#include "include/operator_new_overloads.h"




int main()
{
  std::cout << "memory stats before test\n\n";
  printMemoryStats();
  {
    enCircularLinkList<std::string> intList;
    intList.addNode("afdsaf");
    intList.addNode("dafdsaf");
    for( int32_t i = 0; i < 10; ++i )
    {
      const char randomChar = std::rand() % std::numeric_limits<char>::max();
      const std::string randomString(10, randomChar);
      intList.addNode(randomString);
    }
    std::cout << "\n\nmemory stats after adding all the elements to the list\n\n";
    printMemoryStats();
  }
  std::cout << "\n\n memory stats after destruction of circular-link-list\n\n";
  printMemoryStats();

}
