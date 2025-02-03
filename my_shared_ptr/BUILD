cc_library(
    name = "my_shared_ptr",
    # 注意：这里将 my_shared_ptr.cc 作为实现文件
    srcs = ["include/my_shared_ptr.cc"],
    hdrs = ["src/my_shared_ptr.h"],
    # 指定头文件所在的目录，便于后续 include
    includes = ["src", "include"],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "my_shared_ptr_main",
    srcs = ["main.cpp"], 
    deps = [":my_shared_ptr"],
)
