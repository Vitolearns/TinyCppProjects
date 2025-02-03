#include <thread>
#include <vector>
#include <gtest/gtest.h>
#include "my_shared_ptr.h"

TEST(MySharedPtrTest, NullPointer) {
  MySharedPtr<int> sp(nullptr);
  EXPECT_EQ(sp.use_count(), 0);
}

TEST(MySharedPtrTest, SinglePointer) {
  MySharedPtr<int> sp(new int(42));
  EXPECT_EQ(sp.use_count(), 1);
}

TEST(MySharedPtrTest, CopyConstructor) {
  MySharedPtr<int> sp(new int(42));
  EXPECT_EQ(sp.use_count(), 1);
  {
    MySharedPtr<int> sp2(sp);
    EXPECT_EQ(sp.use_count(), 2);
    EXPECT_EQ(sp2.use_count(), 2);
  }
  EXPECT_EQ(sp.use_count(), 1);
}

TEST(MySharedPtrTest, AssignmentOperator) {
  MySharedPtr<int> sp(new int(100));
  MySharedPtr<int> sp2;
  EXPECT_EQ(sp.use_count(), 1);
  EXPECT_EQ(sp2.use_count(), 0);
  
  sp2 = sp;
  EXPECT_EQ(sp.use_count(), 2);
  EXPECT_EQ(sp2.use_count(), 2);

  // Reassign sp2 to a new object; sp should remain unchanged.
  sp2 = MySharedPtr<int>(new int(200));
  EXPECT_EQ(sp2.use_count(), 1);
  EXPECT_EQ(sp.use_count(), 1);
}

TEST(MySharedPtrTest, SelfAssignment) {
  MySharedPtr<int> sp(new int(10));
  sp = sp;  // Self-assignment should leave the count unchanged.
  EXPECT_EQ(sp.use_count(), 1);
}

TEST(MySharedPtrTest, StressTest) {
  const int iterations = 100000;
  MySharedPtr<int> sp(new int(42));

  // Create a dynamic array to store many copies for stress testing.
  MySharedPtr<int>* copies = new MySharedPtr<int>[iterations];
  for (int i = 0; i < iterations; ++i) {
    copies[i] = sp;
    // After each copy, the use_count should be 1 (for sp) plus i+1 copies.
    EXPECT_EQ(sp.use_count(), i + 2);
  }
  EXPECT_EQ(sp.use_count(), iterations + 1);

  // Deallocate the array of copies; their destruction should drop the use_count back to 1.
  delete[] copies;
  EXPECT_EQ(sp.use_count(), 1);
}

TEST(MySharedPtrTest, ThreadSafety) {
  MySharedPtr<int> sp(new int(42));
  const int num_threads = 8;
  const int iterations = 1000;
  
  std::vector<std::thread> threads;
  for (int i = 0; i < num_threads; ++i) {
    threads.push_back(std::thread([&sp, iterations]() {
      for (int j = 0; j < iterations; ++j) {
        // Each thread makes a copy of sp.
        MySharedPtr<int> local_copy = sp;
        // (Optional) Additional dummy operations could be performed here.
      }
    }));
  }
  
  for (auto& t : threads) {
    t.join();
  }
  
  // After all threads finish, only the original sp should remain.
  EXPECT_EQ(sp.use_count(), 1);
}


// Define a test class to verify object destruction.
class TestObject {
 public:
  static int instances;
  TestObject() { ++instances; }
  ~TestObject() { --instances; }
};

int TestObject::instances = 0;

TEST(MySharedPtrTest, ObjectDestruction) {
  {
    MySharedPtr<TestObject> sp(new TestObject());
    EXPECT_EQ(TestObject::instances, 1);
    {
      MySharedPtr<TestObject> sp2(sp);
      EXPECT_EQ(sp.use_count(), 2);
      EXPECT_EQ(sp2.use_count(), 2);
      EXPECT_EQ(TestObject::instances, 1);
    }
    // After sp2 goes out of scope, sp should still keep the object alive.
    EXPECT_EQ(sp.use_count(), 1);
    EXPECT_EQ(TestObject::instances, 1);
  }
  // Once sp goes out of scope, the managed object should be destroyed.
  EXPECT_EQ(TestObject::instances, 0);
}

