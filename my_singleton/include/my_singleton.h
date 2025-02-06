#pragma once
#include <mutex>

class MySingleton {
public:
  static MySingleton& GetInstance() {
    // Define a static instance of the class here
    // so we don't have to define it in some translation unit
    static MySingleton instance;
    return instance;
  }

  static double GetDesiredGlobalState() {
    std::lock_guard<std::mutex> lock(mutex_); // for thread safety
    return GetInstance().GetDesiredGlobalStateImpl();
    // ofcourse in this case, we could just return the desired_global_state_,
    // but we want to design this class in a way that we can change the
    // implementation of this method, and we don't have to change the
    // interface of the class
  }

  static void SetDesiredGlobalState(double desired_global_state) {
    std::lock_guard<std::mutex> lock(mutex_); // for thread safety
    GetInstance().SetDesiredGlobalStateImpl(desired_global_state);
  }

private:
  static std::mutex mutex_;
  // Private constructor, forbids instantiation outside of this class
  MySingleton() {}
  // Delete the copy constructor
  MySingleton(MySingleton const&) = delete;

  double GetDesiredGlobalStateImpl() {
    return desired_global_state_;
  }

  void SetDesiredGlobalStateImpl(double desired_global_state) {
    desired_global_state_ = desired_global_state;
  }

  double desired_global_state_{0.7f};
};

std::mutex MySingleton::mutex_;
