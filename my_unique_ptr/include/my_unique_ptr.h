#pragma once

#include <utility>

/**
 * @brief A custom unique pointer implementation that manages exclusive ownership of a dynamically allocated object.
 *
 * MyUniquePtr is a simple implementation of a unique pointer, ensuring that only one instance can own the
 * resource at a time. It supports move semantics but disallows copy semantics. When the unique pointer is destroyed,
 * the managed object is deleted.
 *
 * @tparam T The type of the object managed by this pointer.
 */
template<typename T>
class MyUniquePtr {
public:
  /**
   * @brief Constructs a new MyUniquePtr managing a raw pointer.
   *
   * Initializes a new MyUniquePtr to manage the given raw pointer.
   *
   * @param ptr Pointer to the object to be managed (can be nullptr).
   */
  explicit MyUniquePtr(T* ptr = nullptr) : ptr_(ptr) {}

  // Forbid copy constructor
  MyUniquePtr(const MyUniquePtr&) = delete;

  // Forbid copy assignment operator
  MyUniquePtr& operator=(const MyUniquePtr&) = delete;

  /**
   * @brief Move constructor.
   *
   * Transfers ownership from another MyUniquePtr to this one.
   *
   * @param other The MyUniquePtr instance to move from.
   */
  MyUniquePtr(MyUniquePtr&& other) noexcept : ptr_(other.ptr_) {
    other.ptr_ = nullptr;
  }

  /**
   * @brief Move assignment operator.
   *
   * Transfers ownership from another MyUniquePtr to this one.
   *
   * @param other The MyUniquePtr instance to move from.
   * @return A reference to the updated MyUniquePtr.
   */
  MyUniquePtr& operator=(MyUniquePtr&& other) noexcept {
    if (this != &other) {
      // delete the current managed object
      delete ptr_;
      ptr_ = other.ptr_;
      other.ptr_ = nullptr;
    }
    return *this;
  }

  /**
   * @brief Destructor.
   *
   * Deletes the managed object.
   */
  ~MyUniquePtr() {
    if (ptr_) {
      delete ptr_;
    }
  }

  /**
   * @brief Dereference operator.
   *
   * Provides access to the object managed by this pointer.
   *
   * @return A reference to the managed object.
   */
  T& operator*() const {
    return *ptr_;
  }

  /**
   * @brief Member access operator.
   *
   * Allows access to the managed object's members.
   *
   * @return A pointer to the managed object.
   */
  T* operator->() const {
    return ptr_;
  }

  /**
   * @brief Returns the managed pointer.
   *
   * @return The raw pointer to the managed object.
   */
  T* get() const {
    return ptr_;
  }
  
  /**
   * @brief Checks if the managed object is non-null.
   *
   * @return true if the managed object is non-null, false otherwise.
   */
  explicit operator bool() const noexcept {
    return ptr_ != nullptr;
  }

  /**
   * @brief Releases ownership of the managed object.
   *
   * The managed object is not deleted and the unique pointer becomes nullptr.
   *
   * @return The raw pointer to the managed object.
   */
  T* release() {
    T* temp = ptr_;
    ptr_ = nullptr;
    return temp;
  }

  /**
   * @brief Replaces the managed object.
   *
   * Deletes the currently managed object and takes ownership of ptr.
   *
   * @param ptr The new pointer to manage.
   */
  void reset(T* ptr = nullptr) {
    if (ptr_ != ptr) {
      delete ptr_;
      ptr_ = ptr;
    }
  }

private:
  T* ptr_;   ///< Pointer to the managed object.
}; 