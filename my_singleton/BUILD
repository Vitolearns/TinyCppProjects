cc_library(
    name = "my_singleton",
    srcs = ["src/my_singleton.cc"],
    hdrs = ["include/my_singleton.h"],
    includes = ["src", "include"],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "my_singleton_main",
    srcs = ["main.cc"], 
    deps = [":my_singleton"],
)

cc_test(
    name = "my_singleton_test",
    srcs = ["test/my_singleton_test.cc"],
    deps = [":my_singleton",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)
