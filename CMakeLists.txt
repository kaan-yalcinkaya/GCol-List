cmake_minimum_required(VERSION 3.25)
project(GCol_List C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED 11)

file(GLOB SRC ${CMAKE_SOURCE_DIR}/src/*.c)
include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(GCol_List ${SRC})
#add_executable(main test/main.c test/test_person.c)

#target_link_libraries(main GCol_List)