#include <gtest/gtest.h>
#include "my_singleton.h"
#include <thread>
#include <vector>

TEST(MySingletonTest, SingleInstance) {
  // Get two references to the singleton
  MySingleton& instance1 = MySingleton::GetInstance();
  MySingleton& instance2 = MySingleton::GetInstance();

  // Verify that both references point to the same instance
  EXPECT_EQ(&instance1, &instance2);
}

TEST(MySingletonTest, GlobalState) {
  // Get instance and verify the same value through two methods
  MySingleton& instance = MySingleton::GetInstance();
  EXPECT_DOUBLE_EQ(instance.GetDesiredGlobalState(), MySingleton::GetDesiredGlobalState());
}

TEST(MySingletonTest, ThreadSafety) {
  const int num_threads = 100;
  const int iterations = 1000;
  std::vector<std::thread> threads;
  
  // Create threads that just read and write
  for (int i = 0; i < num_threads; ++i) {
    threads.push_back(std::thread([]() {
      for (int j = 0; j < iterations; ++j) {
        double value = MySingleton::GetDesiredGlobalState();
        MySingleton::SetDesiredGlobalState(++value);
        MySingleton::SetDesiredGlobalState(--value);
      }
    }));
  }

  // Wait for all threads to complete
  for (auto& thread : threads) {
    thread.join();
  }
  
  // Test passes if no crashes or data races occurred
}