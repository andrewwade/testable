cmake_minimum_required(VERSION 3.10)
project(testable C)

set(CMAKE_C_STANDARD 99)

add_subdirectory(extern/memorypool)
include_directories(extern/memorypool/include)

set(testable_include_files
        include/asserts.h
        include/groups.h
        include/platform.h
        include/tests.h
        include/testable.h
        include/mockable.h)
set(testable_source_files
        source/_assert.c
        source/_assert.h
        source/_group.c
        source/_group.h
        source/_node.c
        source/_node.h
        source/_test.h
        source/_output.h
        source/_output.c
        source/_pp.h
        source/_test.c
        source/_mock.c
        source/_mock.h
        source/_mock_call.h
        source/_mock_call.c
        source/_pool.c
        source/_pool.h
        source/_list.c
        source/_list.h
        source/_stack.c
        source/_stack.h)





include_directories(include)

add_library(testable ${testable_source_files} ${testable_include_files})
target_include_directories(testable INTERFACE include)
#target_link_libraries(testable memorypool)

link_libraries(testable)

add_executable(test_node test/_node_tests.c test/_node_tests.h test/test_node.c)
add_executable(test_mock test/_mock_tests.c test/_mock_tests.h test/test_mock.c)

add_executable(test_all
        test/_node_tests.c
        test/_node_tests.h
        test/_mock_tests.c
        test/_mock_tests.h
        test/test_all.c)