cmake_minimum_required(VERSION 3.10)
project(testable C)

set(CMAKE_C_STANDARD 99)


set(testable_include_files
        include/asserts.h
        include/groups.h
        include/platform.h
        include/tests.h
        include/clarity/testing.h
        include/clarity/mocking.h)

set(testable_source_files
        source/testing/_assert.c
        source/testing/_assert.h
        source/testing/_group.c
        source/testing/_group.h
        source/utilities/_node.c
        source/utilities/_node.h
        source/testing/_test.h
        source/utilities/_output.h
        source/utilities/_output.c
        source/utilities/_pp.h
        source/testing/_test.c
        source/mocking/_mock.c
        source/mocking/_mock.h
        source/mocking/_mock_call.h
        source/mocking/_mock_call.c
        source/utilities/_pool.c
        source/utilities/_pool.h
        source/utilities/_list.c
        source/utilities/_list.h
        source/utilities/_stack.c
        source/utilities/_stack.h
        source/testing/_runner.c
        source/testing/_runner.h
        include/runners.h source/testing/_query.c source/testing/_query.h source/utilities/_callback.c source/utilities/_callback.h)


include_directories(include)

add_library(testable ${testable_source_files} ${testable_include_files})
target_include_directories(testable INTERFACE include)
#target_link_libraries(testable memorypool)

link_libraries(testable)

add_executable(test_node test/utilities/_node_tests.c test/utilities/_node_tests.h test/utilities/test_node.c)
add_executable(test_mock test/mocking/_mock_tests.c test/mocking/_mock_tests.h test/mocking/test_mock.c)

add_executable(test_all
        test/utilities/_node_tests.c
        test/utilities/_node_tests.h
        test/mocking/_mock_tests.c
        test/mocking/_mock_tests.h
        test/test_all.c
        test/utilities/_list_tests.c
        test/utilities/_list_tests.h
        test/utilities/_pool_tests.c
        test/utilities/_pool_tests.h
        test/testing/_query_tests.c
        test/testing/_query_tests.h
        test/testing/_test_tests.c
        test/testing/_test_tests.h)