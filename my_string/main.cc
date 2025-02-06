#include <iostream>
#include "my_string.h"

int main() {
  // Create and concatenate strings
  MyString s1("Hello");
  MyString s2(" World");
  MyString s3 = s1 + s2;

  std::cout << "s3: " << s3 << std::endl;
  std::cout << "Length: " << s3.length() << std::endl;

  // Test substring operations
  MyString sub = s3.substr(0, 5);
  std::cout << "Substring: " << sub << std::endl;

  // Test find operations
  size_t pos = s3.find("World");
  if (pos != MyString::npos) {
    std::cout << "Found 'World' at position: " << pos << std::endl;
  }

  // Test comparison operations
  MyString s4("Hello");
  if (s1 == s4) {
    std::cout << "s1 equals s4" << std::endl;
  }

  // Test modification operations
  s3[0] = 'h';
  std::cout << "Modified s3: " << s3 << std::endl;

  return 0;
}