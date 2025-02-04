cc_library(
    name = "my_string",
    srcs = ["src/my_string.cc"],
    hdrs = ["include/my_string.h"],
    includes = ["include"],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "my_string_main",
    srcs = ["main.cpp"],
    deps = [":my_string"],
)

cc_test(
    name = "my_string_test",
    srcs = ["test/my_string_test.cc"],
    deps = [
        ":my_string",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
) 