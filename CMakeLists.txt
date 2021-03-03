cmake_minimum_required(VERSION 3.17)
project(button_fsm_practice)
set(CMAKE_CXX_STANDARD 14)
include_directories(./)

#Include(FetchContent)
#
#FetchContent_Declare(
#  Catch2
#  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
#  GIT_TAG        v2.13.1)
#
#FetchContent_MakeAvailable(Catch2)
add_executable(button_fsm_practice test.cpp catch_amalgamated.cpp)
