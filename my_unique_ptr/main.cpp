#include <iostream>
#include "my_unique_ptr.h"

/**
 * @brief A test class for MyUniquePtr.
 *
 * This class is used to test the functionality of the custom MyUniquePtr implementation.
 * It prints messages upon construction and destruction to help observe the lifecycle of
 * objects managed by MyUniquePtr.
 */
class Object {
 public:
  /**
   * @brief Constructs an Object.
   *
   * Prints a message indicating that the Object has been constructed.
   */
  Object() {
    std::cout << "Object constructor" << std::endl;
  }
  
  /**
   * @brief Destroys the Object.
   *
   * Prints a message indicating that the Object is being destroyed.
   */
  ~Object() {
    std::cout << "Object destructor" << std::endl;
  }
};

int main() {
  MyUniquePtr<Object> ptr1(new Object());
  std::cout << "ptr1 " << (ptr1.get() ? "has" : "does not have") << " an object" << std::endl;
  std::cout << "--------------------------------" << std::endl;

  MyUniquePtr<Object> ptr2(std::move(ptr1));
  std::cout << "ptr1 " << (ptr1.get() ? "has" : "does not have") << " an object" << std::endl;
  std::cout << "ptr2 " << (ptr2.get() ? "has" : "does not have") << " an object" << std::endl;
  std::cout << "--------------------------------" << std::endl;

  MyUniquePtr<Object> ptr3 = std::move(ptr2);
  std::cout << "ptr1 " << (ptr1.get() ? "has" : "does not have") << " an object" << std::endl;
  std::cout << "ptr2 " << (ptr2.get() ? "has" : "does not have") << " an object" << std::endl;  
  std::cout << "ptr3 " << (ptr3.get() ? "has" : "does not have") << " an object" << std::endl;
} 