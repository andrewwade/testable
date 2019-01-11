cmake_minimum_required(VERSION 3.10)
project(testable C)

set(CMAKE_C_STANDARD 99)
include_directories(p99)

set(testable_include_files
        include/asserts.h
        include/groups.h
        include/platform.h
        include/tests.h
        include/testable.h)
set(testable_source_files
        src/_assert.c
        src/_assert.h
        src/_group.c
        src/_group.h
        src/_node.c
        src/_node.h
        src/_pool.c
        src/_pool.h
        src/_test.h
        src/_output.h
        src/_output.c src/_pp.h)

set(testable_test_files
        test/_node_test.c test/_node_test.h src/_test.c src/_mock.c extern/macro_helpers.h include/mockable.h src/_mock.h test.h test.c src/_mock_call.h src/_mock_call.c)



include_directories(include)

add_library(testable ${testable_source_files} ${testable_include_files} ${testable_test_files})
target_include_directories(testable INTERFACE include)

add_executable(runner main.c)
target_link_libraries(runner testable)
