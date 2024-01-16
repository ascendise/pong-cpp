include(FetchContent)

cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_CXX_CLANG_TIDY "clang-tidy;--header-filter='.*'")
project(Pong)
add_subdirectory(app)
add_subdirectory(lib)

enable_testing()
add_subdirectory(tests)

#googletest
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.13.0
        SYSTEM
)
FetchContent_MakeAvailable(googletest)

#SDL2
FetchContent_Declare(
        SDL2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-2.26.4
        SYSTEM
)
FetchContent_MakeAvailable(SDL2)

#SDL_Image
FetchContent_Declare(
        SDL_Image
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
        GIT_TAG d3c6d5963dbe438bcae0e2b6f3d7cfea23d02829
        SYSTEM
)

set(SDL2IMAGE_INSTALL OFF)
set(BUILD_SHARED_LIBS FALSE)

FetchContent_MakeAvailable(SDL_Image)

#Include assets in output
add_custom_target(assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
) 
add_dependencies(Pong assets)