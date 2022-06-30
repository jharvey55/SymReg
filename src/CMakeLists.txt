add_library(
        structs
        Structures/Node.h
        Structures/Node.cpp
        Structures/Contender.h
        Structures/Contender.cpp
        Structures/Point.h
        Structures/Point.cpp

)
target_include_directories(structs PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Structures")

add_library(
        opts
        Optimizers/Optimizers.h
        Optimizers/Optimizers.cpp
)
target_include_directories(opts PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Optimizers")

add_library(
        data_io
        DataIO/DataLogger.h
        DataIO/DataLogger.cpp
)
target_include_directories(data_io PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/DataIO")

