cmake_minimum_required(VERSION 3.16)
project(SymReg)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_DEBUG_POSTFIX _d)
# set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(src)


add_executable(SymReg main.cpp)
set_target_properties(SymReg PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
target_link_libraries(SymReg PRIVATE structs)
target_link_libraries(SymReg PRIVATE data_io)
target_link_libraries(SymReg PRIVATE opts)
target_link_libraries(SymReg ${CONAN_LIBS})

add_executable(rfg randFuncGen.cpp)
set_target_properties(rfg PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
target_link_libraries(rfg PRIVATE structs)
target_link_libraries(rfg PRIVATE data_io)
target_link_libraries(rfg PRIVATE opts)
target_link_libraries(rfg ${CONAN_LIBS})


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# include(CTest)
enable_testing()

add_subdirectory(gtests)

add_subdirectory(sandbox)
