cc_library(
    name = "foobar",
    srcs = [
        "bar.cc",
        "foo.c",
    ],
    hdrs = [
        "bar.h",
        "foo.h",
    ],
)

cc_binary(
    name = "main",
    srcs = ["main.cc"],
    deps = [":foobar"],
)
