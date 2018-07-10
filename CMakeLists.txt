cmake_minimum_required(VERSION 3.10)
project(testable C)

set(CMAKE_C_STANDARD 99)
include_directories(p99)

set(testable_include_files
        include/assertable.h
        include/groupable.h
        include/portable.h
        include/runnable.h
        include/testable.h
        include/testing.h)
set(testable_source_files
        source/_assert.c
        source/_assert.h
        source/_group.c
        source/_group.h
        source/_node.c
        source/_node.h
        source/_pool.c
        source/_pool.h
        source/_test.h source/_output.h source/_output.c)

set(testable_test_files
        test/_node_test.c test/_node_test.h source/_test.c)

include_directories(include)
add_library(testable ${testable_source_files} ${testable_include_files} ${testable_test_files})
target_include_directories(testable INTERFACE include)

add_executable(runner main.c)
target_link_libraries(runner testable)