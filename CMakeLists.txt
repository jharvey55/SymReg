cmake_minimum_required(VERSION 3.16)
project(SymReg)

set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(src)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(SymReg main.cpp)
target_link_libraries(SymReg PRIVATE structs)
target_link_libraries(SymReg PRIVATE data_io)
target_link_libraries(SymReg PRIVATE opts)
target_link_libraries(SymReg ${CONAN_LIBS})


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# include(CTest)
enable_testing()

add_subdirectory(gtests)
