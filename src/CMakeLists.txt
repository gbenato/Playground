project(Playground-ObjsLib)
enable_language(CXX)

find_package(ROOT CONFIG COMPONENTS Core Hist Tree Gpad)

include_directories(${Playground_SOURCE_DIR}/include)

add_library(playgroundlib Parameter.cpp
			  Global.cpp
			  Log.cpp
			  Random.cpp )


export( TARGETS playgroundlib FILE playgroundlib-exports.cmake )

if( NOT ROOT_FOUND )
    target_link_libraries(playgroundlib)
else()
    add_definitions(-DHAVE_ROOT)
    target_compile_definitions(playgroundlib INTERFACE HAVE_ROOT)
    target_link_libraries(playgroundlib PUBLIC ROOT::Tree ROOT::Spectrum ROOT::Gpad)
endif()

target_include_directories(playgroundlib PUBLIC ${CMAKE_CURRENT_LIST_DIR})

