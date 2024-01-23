include(FetchContent)

cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
project(Pong)
add_subdirectory(app)
add_subdirectory(lib)

enable_testing()
add_subdirectory(tests)

#Include assets in output
add_custom_target(assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
) 
add_dependencies(Pong assets)
