#include <iostream>
#include "my_shared_ptr.h"

/**
 * @brief A test class for MySharedPtr.
 *
 * This class is used to test the functionality of the custom MySharedPtr implementation.
 * It prints messages upon construction and destruction to help observe the lifecycle of
 * objects managed by MySharedPtr.
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
  Object* obj = new Object();
  
  MySharedPtr<Object> ptr1(obj);
  std::cout << "ptr1 use_count: " << ptr1.use_count() << std::endl;

  MySharedPtr<Object> ptr2(nullptr);
  std::cout << "ptr2 use_count: " << ptr2.use_count() << std::endl;
  ptr2 = ptr1;
  std::cout << "ptr2 use_count: " << ptr2.use_count() << std::endl;

  MySharedPtr<Object> ptr3(ptr1);
  std::cout << "ptr3 use_count: " << ptr3.use_count() << std::endl;
} 