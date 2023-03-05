cmake_minimum_required(VERSION 3.5)

project(matrix_p LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#add_subdirectory(../lib/version_lib)

set(SOURCES main.cpp)
set(HEADERS matrix.h)

add_executable(matrix_e ${SOURCES} ${HEADERS})

target_include_directories(matrix_e PRIVATE
  ../lib/version_lib
)

target_link_libraries(matrix_e PRIVATE
    version_l
)


