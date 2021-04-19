cmake_minimum_required(VERSION 3.19)
project(fsm_practice)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 11)

# GOOGLE TEST
enable_testing()
find_package(GTest REQUIRED)
include(GoogleTest)


#FetchContent_Declare(googletest
#        GIT_REPOSITORY      https://github.com/google/googletest.git
#        GIT_TAG             release-1.8.0)
#FetchContent_GetProperties(googletest)
#FetchContent_MakeAvailable(googletest)

# Teaching CMake to build an .exe
#add_executable(fsm_practice_catch2 main_catch2.cpp test/test.cpp prod/fsm.c prod/fsm.h)
add_executable(fsm_practice_gtest main_gtest.cpp prod/fsm.c test/test_fsm_using_gtest.cpp)
#target_link_libraries(fsm_practice ApprovalTests::ApprovalTests Catch2::Catch2)
target_link_libraries(fsm_practice_gtest GTest::GTest)
# gtest_discover_tests(fsm_practice_gtest)

# For target x, it will depend on the libraries listed
# If the libraries are properly CMake/configured, this will automatically
# make libraries headers libraries available to target!
# :: is the modern CMake style; it's called 'target aliases'
# It gives you early error detection of libraries, instead of late link errors.
