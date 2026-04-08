cmake_minimum_required(VERSION 3.10)
project(DoublyLinkedList)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES "*.cpp")
if(SOURCES)
    add_executable(code ${SOURCES})
else()
    add_executable(code dummy.cpp)
endif()