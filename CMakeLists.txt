cmake_minimum_required(VERSION 3.19)
project(fsm_practice)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 11)
set(USE_GOOGLE_TEST 1)

if(USE_GOOGLE_TEST)
    # Install GoogleTest using:
    #    sudo apt install libgtest-dev
    enable_testing()
    find_package(GTest REQUIRED)
    include(GoogleTest)
    add_executable(fsm_practice_gtest main_gtest.cpp prod/fsm.c test/test_fsm_using_gtest.cpp)
    target_link_libraries(fsm_practice_gtest GTest::GTest)
endif()

if(USE_CATCH2)
    # ApprovaltestsCpp + catch2
    FetchContent_Declare(googletest
            GIT_REPOSITORY      https://github.com/google/googletest.git
            GIT_TAG             release-1.8.0)
    FetchContent_GetProperties(googletest)
    FetchContent_MakeAvailable(googletest)

    # Teaching CMake to build an .exe
    add_executable(fsm_practice_catch2 main_catch2.cpp test/test.cpp prod/fsm.c prod/fsm.h)
    target_link_libraries(fsm_practice ApprovalTests::ApprovalTests Catch2::Catch2)
endif()
