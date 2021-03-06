cmake_minimum_required(VERSION 3.17)
project(fsm_practice)
set(CMAKE_CXX_STANDARD 14)

# FetchContent needs CMake 3.14 or above
include(FetchContent)
# -------------------------------------------------------------------
# ApprovalTests.cpp
FetchContent_Declare(ApprovalTests
        GIT_REPOSITORY https://github.com/approvals/ApprovalTests.cpp.git
        GIT_TAG master)

# Tell the ApprovalTests CMake files that we want to use its copy of Catch2:
set(APPROVAL_TESTS_BUILD_THIRD_PARTY_CATCH2 ON CACHE BOOL "")

FetchContent_MakeAvailable(ApprovalTests)

# Teaching CMake to build an .exe
add_executable(fsm_practice main.cpp test/test.cpp prod/fsm.c prod/fsm.h)
target_link_libraries(fsm_practice ApprovalTests::ApprovalTests Catch2::Catch2)

# For target x, it will depend on the libraries listed
# If the libraries are properly CMake/configured, this will automatically
# make libraries headers libraries available to target!
# :: is the modern CMake style; it's called 'target aliases'
# It gives you early error detection of libraries, instead of late link errors.
