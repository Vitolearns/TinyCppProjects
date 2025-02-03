#include <iostream>
#include <mutex>
// #include "my_shared_ptr.h"

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

/**
 * @brief A custom shared pointer implementation that manages shared ownership of a dynamically allocated object.
 *
 * MySharedPtr is a simple implementation of a shared pointer, which manages a reference count and cleans up the
 * managed object when the count reaches zero. It supports copy semantics and thread-safe reference counting.
 *
 * @tparam T The type of the object managed by this pointer.
 */
template<typename T>
class MySharedPtr {
public:
  /**
   * @brief Constructs a MySharedPtr.
   *
   * Initializes a new MySharedPtr to manage the given raw pointer. If the pointer is non-null, 
   * the reference count is set to 1; otherwise, it is set to 0.
   *
   * @param ptr Pointer to the object to be managed (can be nullptr).
   */
  MySharedPtr(T* ptr = nullptr) : ptr_(ptr) {
    mutex_ = new std::mutex();
    if (!ptr) {
      // If ptr is nullptr, initialize count to 0.
      count_ = new size_t(0);
    } else {
      count_ = new size_t(1);
    }
  }

  /**
   * @brief Destroys the MySharedPtr.
   *
   * Decrements the reference count and, if it reaches zero, deletes the managed object
   * along with the associated reference count and mutex.
   */
  ~MySharedPtr() {
    sub_count();
  }

  /**
   * @brief Copy constructor.
   *
   * Constructs a new MySharedPtr as a copy of an existing one, sharing ownership of the
   * managed object and incrementing the reference count.
   *
   * @param other The MySharedPtr instance to copy.
   */
  MySharedPtr(const MySharedPtr& other) {
    ptr_ = other.ptr_;
    count_ = other.count_;
    mutex_ = other.mutex_;
    add_count();
  }
  
  /**
   * @brief Assignment operator.
   *
   * Assigns another MySharedPtr to this instance, updating reference counts appropriately.
   * Handles self-assignment and decrements the previous pointer's reference count.
   *
   * @param other The MySharedPtr instance to assign from.
   * @return A reference to the updated MySharedPtr.
   */
  MySharedPtr& operator=(const MySharedPtr& other) {
    if (this == &other) {
      return *this;
    }
    // Before assignment, decrement the current resource's reference count.
    sub_count();

    ptr_ = other.ptr_;
    count_ = other.count_;
    mutex_ = other.mutex_;
    add_count();
    return *this;
  }

  /**
   * @brief Dereference operator.
   *
   * Provides access to the object managed by this pointer.
   *
   * @return A reference to the managed object.
   */
  T& operator*() {
    return *ptr_;
  }
  
  /**
   * @brief Member access operator.
   *
   * Allows access to the managed object's members.
   *
   * @return A pointer to the managed object.
   */
  T* operator->() {
    return ptr_;
  }

  /**
   * @brief Increments the reference count.
   *
   * This function is used when a new shared pointer is created from an existing one, indicating
   * that there is an additional owner.
   */
  void add_count() {
    std::lock_guard<std::mutex> lock(*mutex_);
    (*count_)++;
  }

  /**
   * @brief Decrements the reference count and deletes the managed object if no owners remain.
   *
   * Safely decrements the reference count under a lock. If the count drops to zero, the managed
   * object and the reference count are deleted, and the mutex is deallocated after the lock is released.
   */
  void sub_count() {
    bool should_delete_mutex{false};
    {
      std::lock_guard<std::mutex> lock(*mutex_);
      (*count_)--;
      if (*count_ == 0) {
        // When count_ reaches 0, no MySharedPtr instances are sharing this object,
        // so delete the managed object and the reference count.
        delete ptr_;
        delete count_;
        // The mutex cannot be deleted directly while within the lock_guard scope;
        // mark it for deletion after leaving the scope.
        should_delete_mutex = true;
      }
    }
    if (should_delete_mutex) {
      delete mutex_;
    }
  }
  
  /**
   * @brief Retrieves the current number of shared owners.
   *
   * Returns the reference count associated with the managed object, indicating how many
   * MySharedPtr instances share ownership.
   *
   * @return The number of shared owners.
   */
  size_t use_count() const {
    std::lock_guard<std::mutex> lock(*mutex_);
    return *count_;
  }

private:
  T* ptr_;               ///< Pointer to the managed object.
  size_t* count_;        ///< Pointer to the reference count.
  std::mutex* mutex_;    ///< Pointer to the mutex used for thread-safe operations.
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