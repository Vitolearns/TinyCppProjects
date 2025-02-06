#include <iostream>
#include "my_singleton.h"

int main() {
  // First way to access method in singleton, use it like a namespace
  std::cout << "Desired global state: " << MySingleton::GetDesiredGlobalState() << std::endl;
  // Second way to access method in singleton, use it like a class
  MySingleton& singleton = MySingleton::GetInstance();
  std::cout << "Desired global state: " << singleton.GetDesiredGlobalState() << std::endl;
  return 0;
}
