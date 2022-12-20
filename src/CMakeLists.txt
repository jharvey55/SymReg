add_library(
        structs
        Structures/Node.h
        Structures/Node.cpp
        Structures/Point.h
        Structures/Point.cpp
        Structures/Heap.h
        Structures/Heap.cpp)
target_include_directories(structs PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Structures")

add_library(
        data_io
        DataIO/DataLog.h
        DataIO/DataLog.cpp)
target_include_directories(data_io PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/DataIO")
target_link_libraries(data_io PRIVATE structs)

add_library(
        opts
        Optimizers/Optimizers.h
        Optimizers/Optimizers.cpp
        Optimizers/Contender.h
        Optimizers/Contender.cpp
)

target_include_directories(opts PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Optimizers")
target_link_libraries(opts PRIVATE structs)
target_link_libraries(opts PRIVATE data_io)

