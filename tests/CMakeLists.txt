cmake_minimum_required(VERSION 3.5)

project(tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/../lib/gtest" "googletest" EXCLUDE_FROM_ALL)

add_executable(tests_1 tests_1.cpp)

target_include_directories(tests_1 PRIVATE ../src)

target_link_libraries(tests_1
  #    ${Boost_LIBRARIES}
  gtest_main
)

add_test(NAME tests_1 COMMAND tests_1)


#сmake_minimum_required (VERSION 3.8)

#find_package (Boost COMPONENTS unit_test_framework REQUIRED)
#add_definitions (-DBOOST_TEST_DYN_LINK)
#include_directories ( ${CMAKE_SOURCE_DIR}/Sources
#                      ${Boost_INCLUDE_DIRS})

#set (TESTS Vector3fTest Vector2fTest) #MovableObjectTest)

#foreach (_test ${TESTS})
#  add_executable (${_test} ${_test}.cpp)
#  target_link_libraries (${_test} ${Boost_LIBRARIES})
#  add_test (NAME ${_test} COMMAND ${_test)
#endforeach ()
