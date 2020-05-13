cmake_minimum_required(VERSION 3.16)
project(trees)

set(CMAKE_CXX_STANDARD 14)

add_executable(trees main.cpp node.h visitor.h)