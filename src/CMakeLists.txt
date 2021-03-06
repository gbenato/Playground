project(Playground-ObjsLib)
enable_language(CXX)

include_directories(${Playground_SOURCE_DIR}/include)

add_library(playgroundlib Parameter.cpp
			  Log.cpp )
