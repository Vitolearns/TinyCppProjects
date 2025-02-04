#include <gtest/gtest.h>
#include "my_unique_ptr.h"

// Define a test class to verify object destruction.
class TestObject {
 public:
  static int instance_count;
  TestObject() { ++instance_count; }
  ~TestObject() { --instance_count; }
};

int TestObject::instance_count = 0;

TEST(MyUniquePtrTest, NullPointer) {
  MyUniquePtr<int> ptr(nullptr);
  EXPECT_EQ(ptr.get(), nullptr);
}

TEST(MyUniquePtrTest, BasicOperation) {
  MyUniquePtr<int> ptr(new int(42));
  EXPECT_NE(ptr.get(), nullptr);
  EXPECT_EQ(*ptr, 42);
  *ptr = 100;
  EXPECT_EQ(*ptr, 100);
}

TEST(MyUniquePtrTest, MoveConstructor) {
  MyUniquePtr<int> ptr1(new int(10));
  MyUniquePtr<int> ptr2(std::move(ptr1));
  EXPECT_EQ(ptr1.get(), nullptr);
  EXPECT_NE(ptr2.get(), nullptr);
  EXPECT_EQ(*ptr2, 10);
}

TEST(MyUniquePtrTest, MoveAssignment) {
  MyUniquePtr<int> ptr1(new int(20));
  MyUniquePtr<int> ptr2(new int(30));
  ptr2 = std::move(ptr1);
  EXPECT_EQ(ptr1.get(), nullptr);
  EXPECT_NE(ptr2.get(), nullptr);
  EXPECT_EQ(*ptr2, 20);
}

TEST(MyUniquePtrTest, Release) {
  MyUniquePtr<int> ptr(new int(50));
  int* raw = ptr.release();
  EXPECT_EQ(ptr.get(), nullptr);
  EXPECT_NE(raw, nullptr);
  EXPECT_EQ(*raw, 50);
  delete raw;  // manual cleanup since release doesn't delete the object.
}

TEST(MyUniquePtrTest, Reset) {
  MyUniquePtr<int> ptr(new int(60));
  ptr.reset(new int(70));
  EXPECT_NE(ptr.get(), nullptr);
  EXPECT_EQ(*ptr, 70);
  ptr.reset();
  EXPECT_EQ(ptr.get(), nullptr);
}

TEST(MyUniquePtrTest, ObjectDestruction) {
  EXPECT_EQ(TestObject::instance_count, 0);
  {
    MyUniquePtr<TestObject> ptr(new TestObject());
    EXPECT_EQ(TestObject::instance_count, 1);
  }
  EXPECT_EQ(TestObject::instance_count, 0);
} 