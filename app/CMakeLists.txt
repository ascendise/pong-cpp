add_executable(Pong 
    "src/main.cpp")

find_package(SDL2 REQUIRED CONFIG)

target_link_libraries(Pong 
	PRIVATE
	PongLib 
	$<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
	$<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)
