#pragma once

#include <cstring>
#include <iostream>

/**
 * @brief A custom string class that manages dynamic character array.
 *
 * MyString provides basic string operations including construction, assignment,
 * concatenation, comparison, and substring operations. It manages memory
 * automatically and supports both copy and move semantics.
 */
class MyString {
public:
  /**
   * @brief Constructs an empty string.
   *
   * Creates a string with only a null terminator, initializing size to 0
   * and capacity to 1.
   */
  MyString();

  /**
   * @brief Constructs string from C-style string.
   *
   * If the input string is null, creates an empty string.
   * Otherwise, copies the input string's contents.
   *
   * @param str Pointer to null-terminated string (can be nullptr).
   */
  MyString(const char* str);

  /**
   * @brief Copy constructor.
   *
   * Creates a new string as a copy of an existing one,
   * allocating new memory and copying the content.
   *
   * @param other The MyString instance to copy from.
   */
  MyString(const MyString& other);

  /**
   * @brief Move constructor.
   *
   * Transfers ownership of resources from other string,
   * leaving it in a valid but empty state.
   *
   * @param other The MyString instance to move from.
   */
  MyString(MyString&& other) noexcept;

  /**
   * @brief Destroys the string.
   *
   * Deallocates the internal character array.
   */
  ~MyString();

  /**
   * @brief Copy assignment operator.
   *
   * Copies content from another string, handling self-assignment correctly.
   *
   * @param other The MyString instance to copy from.
   * @return Reference to this object.
   */
  MyString& operator=(const MyString& other);

  /**
   * @brief Move assignment operator.
   *
   * Transfers ownership from other string, handling self-assignment correctly.
   *
   * @param other The MyString instance to move from.
   * @return Reference to this object.
   */
  MyString& operator=(MyString&& other) noexcept;

  /**
   * @brief Appends another string to this string.
   *
   * Reallocates memory if necessary to accommodate the new content.
   *
   * @param str The string to append.
   * @return Reference to this object.
   */
  MyString& append(const MyString& str);

  /**
   * @brief Appends a C-style string to this string.
   *
   * Converts C-style string to MyString and delegates to append(const MyString&).
   *
   * @param str The C-style string to append.
   * @return Reference to this object.
   */
  MyString& append(const char* str);

  /**
   * @brief Concatenates two strings.
   *
   * Creates a new string containing the concatenated result.
   *
   * @param other The string to concatenate with.
   * @return A new string containing the concatenated result.
   */
  MyString operator+(const MyString& other) const;

  /**
   * @brief Equality comparison operator.
   *
   * Compares both length and content of strings.
   *
   * @param other The string to compare with.
   * @return true if strings are equal, false otherwise.
   */
  bool operator==(const MyString& other) const;

  /**
   * @brief Inequality comparison operator.
   *
   * Implemented in terms of equality operator.
   *
   * @param other The string to compare with.
   * @return true if strings are not equal, false otherwise.
   */
  bool operator!=(const MyString& other) const;

  /**
   * @brief Less than comparison operator.
   *
   * Performs lexicographical comparison of strings.
   *
   * @param other The string to compare with.
   * @return true if this string is lexicographically less than other.
   */
  bool operator<(const MyString& other) const;

  /**
   * @brief Array subscript operator.
   *
   * Provides mutable access to characters in the string.
   *
   * @param pos The position to access.
   * @return Reference to character at specified position.
   */
  char& operator[](size_t pos);

  /**
   * @brief Const array subscript operator.
   *
   * Provides read-only access to characters in the string.
   *
   * @param pos The position to access.
   * @return Const reference to character at specified position.
   */
  const char& operator[](size_t pos) const;

  /**
   * @brief Returns pointer to internal C-style string.
   *
   * Provides read-only access to null-terminated string data.
   *
   * @return Const pointer to null-terminated string.
   */
  const char* c_str() const;

  /**
   * @brief Returns the length of the string.
   *
   * @return Number of characters in string (excluding null terminator).
   */
  size_t length() const;

  /**
   * @brief Checks if string is empty.
   *
   * @return true if string length is 0, false otherwise.
   */
  bool empty() const;

  /**
   * @brief Clears the string content.
   *
   * Resets string to empty state while maintaining allocated capacity.
   */
  void clear();

  /**
   * @brief Finds a substring in this string.
   *
   * Searches for substring starting from specified position.
   *
   * @param str The substring to find.
   * @param pos The position to start searching from.
   * @return Position where substring was found, or npos if not found.
   */
  size_t find(const MyString& str, size_t pos = 0) const;

  /**
   * @brief Extracts a substring.
   *
   * Creates a new string containing the specified range of characters.
   *
   * @param pos Starting position of substring.
   * @param len Length of substring (npos means until end of string).
   * @return New string containing the substring.
   */
  MyString substr(size_t pos, size_t len = npos) const;

  // Stream operators
  friend std::ostream& operator<<(std::ostream& os, const MyString& str);
  friend std::istream& operator>>(std::istream& is, MyString& str);

  static const size_t npos;  // Represents not found or invalid position

private:
  char* data_;       // Pointer to character array
  size_t size_;      // Length of string (excluding null terminator)
  size_t capacity_;  // Allocated memory size

  /**
   * @brief Reallocates internal buffer to new capacity.
   *
   * Allocates new memory, copies existing content, and updates capacity.
   *
   * @param new_capacity The new capacity to allocate.
   */
  void reallocate(size_t new_capacity);
};