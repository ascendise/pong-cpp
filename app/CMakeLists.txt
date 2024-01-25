add_executable(Pong 
    "src/main.cpp")

find_package(SDL2 REQUIRED CONFIG)

target_link_libraries(Pong 
	PRIVATE
	PongLib 
	SDL2::SDL2 
	SDL2::SDL2main
)
