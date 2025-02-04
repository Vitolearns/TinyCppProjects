#include "my_string.h"
#include <algorithm>
#include <cstring>
#include <cassert>

// Define static member
const size_t MyString::npos = static_cast<size_t>(-1);

// Default constructor
MyString::MyString() : data_(new char[1]), size_(0), capacity_(1) {
  data_[0] = '\0';
}

// Construct from C-style string
MyString::MyString(const char* str) {
  if (str) {
    size_ = strlen(str);
    capacity_ = size_ + 1;
    data_ = new char[capacity_];
    memcpy(data_, str, size_ + 1);
  } else {
    data_ = new char[1];
    data_[0] = '\0';
    size_ = 0;
    capacity_ = 1;
  }
}

// Copy constructor
MyString::MyString(const MyString& other) 
    : size_(other.size_), capacity_(other.capacity_) {
  data_ = new char[capacity_];
  memcpy(data_, other.data_, size_ + 1);
}

// Move constructor
MyString::MyString(MyString&& other) noexcept
    : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
  other.data_ = nullptr;
  other.size_ = 0;
  other.capacity_ = 0;
}

// Destructor
MyString::~MyString() {
  delete[] data_;
}

// Copy assignment operator
MyString& MyString::operator=(const MyString& other) {
  if (this != &other) {
    delete[] data_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    data_ = new char[capacity_];
    memcpy(data_, other.data_, size_ + 1);
  }
  return *this;
}

// Move assignment operator
MyString& MyString::operator=(MyString&& other) noexcept {
  if (this != &other) {
    delete[] data_;
    data_ = other.data_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
  }
  return *this;
}

// Reallocate memory with new capacity
void MyString::reallocate(size_t new_capacity) {
  char* new_data = new char[new_capacity];
  memcpy(new_data, data_, size_ + 1);
  delete[] data_;
  data_ = new_data;
  capacity_ = new_capacity;
}

// Append another string
MyString& MyString::append(const MyString& str) {
  size_t new_size = size_ + str.size_;
  if (new_size >= capacity_) {
    reallocate(new_size * 2 + 1);
  }
  memcpy(data_ + size_, str.data_, str.size_ + 1);
  size_ = new_size;
  return *this;
}

// Append C-style string
MyString& MyString::append(const char* str) {
  return append(MyString(str));
}

// String concatenation
MyString MyString::operator+(const MyString& other) const {
  MyString result(*this);
  result.append(other);
  return result;
}

// Equality comparison
bool MyString::operator==(const MyString& other) const {
  return size_ == other.size_ && strcmp(data_, other.data_) == 0;
}

// Inequality comparison
bool MyString::operator!=(const MyString& other) const {
  return !(*this == other);
}

// Less than comparison
bool MyString::operator<(const MyString& other) const {
  return strcmp(data_, other.data_) < 0;
}

// Array subscript operator
char& MyString::operator[](size_t pos) {
  assert(pos < size_);
  return data_[pos];
}

// Const array subscript operator
const char& MyString::operator[](size_t pos) const {
  assert(pos < size_);
  return data_[pos];
}

// Get C-style string
const char* MyString::c_str() const {
  return data_;
}

// Get string length
size_t MyString::length() const {
  return size_;
}

// Check if string is empty
bool MyString::empty() const {
  return size_ == 0;
}

// Clear string content
void MyString::clear() {
  data_[0] = '\0';
  size_ = 0;
}

// Find substring
size_t MyString::find(const MyString& str, size_t pos) const {
  if (pos > size_) return npos;
  const char* result = strstr(data_ + pos, str.data_);
  return result ? result - data_ : npos;
}

// Get substring
MyString MyString::substr(size_t pos, size_t len) const {
  if (pos > size_) return MyString();
  if (len == npos || pos + len > size_) {
    len = size_ - pos;
  }
  
  char* temp = new char[len + 1];
  memcpy(temp, data_ + pos, len);
  temp[len] = '\0';
  MyString result(temp);
  delete[] temp;
  return result;
}

// Stream output operator
std::ostream& operator<<(std::ostream& os, const MyString& str) {
  return os << str.data_;
}

// Stream input operator
std::istream& operator>>(std::istream& is, MyString& str) {
  char temp[1024];
  is >> temp;
  str = MyString(temp);
  return is;
}