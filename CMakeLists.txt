include(FetchContent)

cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
project(Pong)
add_subdirectory(app)
add_subdirectory(lib)

enable_testing()
add_subdirectory(tests)

#SDL2
find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2 SDL2main)
target_link_libraries(Pong PRIVATE SDL2::SDL2 SDL2::SDL2main)
target_link_libraries(PongLib PRIVATE SDL2::SDL2 SDL2::SDL2main)
target_link_libraries(Tests PRIVATE SDL2::SDL2 SDL2::SDL2main)

#SDL_Image
find_package(SDL2_image)
target_link_libraries(PongLib PRIVATE SDL2_image::SDL2_image)
set(SDL2IMAGE_INSTALL OFF)
set(BUILD_SHARED_LIBS FALSE)

#Include assets in output
add_custom_target(assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
) 
add_dependencies(Pong assets)
