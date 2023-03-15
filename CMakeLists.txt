include(FetchContent)

cmake_minimum_required(VERSION 3.25)
set(CMAKE_CXX_STANDARD 14)
project(Pong)
add_subdirectory(src)

enable_testing()
add_subdirectory(tests)

#googletest
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.13.0)
FetchContent_MakeAvailable(googletest)