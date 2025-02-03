cc_library(
    name = "my_shared_ptr",
    srcs = ["src/my_shared_ptr.cc"],
    hdrs = ["include/my_shared_ptr.h"],
    includes = ["src", "include"],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "my_shared_ptr_main",
    srcs = ["main.cpp"], 
    deps = [":my_shared_ptr"],
)

cc_test(
    name = "my_shared_ptr_test",
    srcs = ["test/my_shared_ptr_test.cc"],
    deps = [
        ":my_shared_ptr",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)
