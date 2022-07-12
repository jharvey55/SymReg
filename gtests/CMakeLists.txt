project(gtests)

enable_testing()

add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(ContenderTest ContenderTest.cpp)
target_link_libraries(ContenderTest PRIVATE structs data_io)
# target_link_libraries(ContenderTest PRIVATE data_io)
target_link_libraries(ContenderTest PRIVATE gtest gtest_main)

add_executable(HeapTest HeapTest.cpp)
target_link_libraries(HeapTest PRIVATE structs data_io)
# target_link_libraries(ContenderTest PRIVATE data_io)
target_link_libraries(HeapTest PRIVATE gtest gtest_main)

include(GoogleTest)

# add_test(NAME )
gtest_discover_tests(ContenderTest)