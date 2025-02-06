cc_library(
    name = "my_unique_ptr",
    srcs = ["src/my_unique_ptr.cc"],
    hdrs = ["include/my_unique_ptr.h"],
    includes = ["src", "include"],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "my_unique_ptr_main",
    srcs = ["main.cc"], 
    deps = [":my_unique_ptr"],
)

cc_test(
    name = "my_unique_ptr_test",
    srcs = ["test/my_unique_ptr_test.cc"],
    deps = [
        ":my_unique_ptr",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)
