#include <gtest/gtest.h>
#include "my_string.h"

TEST(MyStringTest, Constructor) {
  MyString s1;
  EXPECT_TRUE(s1.empty());
  EXPECT_EQ(s1.length(), 0);

  MyString s2("hello");
  EXPECT_EQ(s2.length(), 5);
  EXPECT_STREQ(s2.c_str(), "hello");

  MyString s3(s2);
  EXPECT_EQ(s3.length(), 5);
  EXPECT_STREQ(s3.c_str(), "hello");
}

TEST(MyStringTest, Assignment) {
  MyString s1("hello");
  MyString s2;
  s2 = s1;
  EXPECT_STREQ(s2.c_str(), "hello");

  MyString s3;
  s3 = "world";
  EXPECT_STREQ(s3.c_str(), "world");
}

TEST(MyStringTest, StringOperations) {
  MyString s1("hello");
  s1.append(" world");
  EXPECT_STREQ(s1.c_str(), "hello world");

  MyString s2("hello");
  MyString s3(" world");
  MyString s4 = s2 + s3;
  EXPECT_STREQ(s4.c_str(), "hello world");
}

TEST(MyStringTest, Comparison) {
  MyString s1("hello");
  MyString s2("hello");
  MyString s3("world");

  EXPECT_TRUE(s1 == s2);
  EXPECT_FALSE(s1 == s3);
  EXPECT_TRUE(s1 != s3);
  EXPECT_TRUE(s1 < s3);
}

TEST(MyStringTest, IndexAccess) {
  MyString s("hello");
  EXPECT_EQ(s[0], 'h');
  EXPECT_EQ(s[4], 'o');
  
  s[0] = 'H';
  EXPECT_EQ(s[0], 'H');
}

TEST(MyStringTest, FindAndSubstr) {
  MyString s("hello world");
  EXPECT_EQ(s.find("world"), 6);
  EXPECT_EQ(s.find("xyz"), MyString::npos);

  MyString sub = s.substr(0, 5);
  EXPECT_STREQ(sub.c_str(), "hello");
}

TEST(MyStringTest, MoveSemantics) {
  MyString s1("hello");
  MyString s2 = std::move(s1);
  EXPECT_STREQ(s2.c_str(), "hello");
  EXPECT_TRUE(s1.empty());  // s1 should be empty after move
}