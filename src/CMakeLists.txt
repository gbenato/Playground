project(Playground-ObjsLib)
enable_language(CXX)

find_package(ROOT CONFIG COMPONENTS Core Hist Tree Gpad)
find_package(Eigen3 3.3 REQUIRED NO_MODULE)

include_directories(${Playground_SOURCE_DIR}/include)

add_library(playgroundlib Global.cpp
			  Space.cpp
			  Variable.cpp
			  Parameter.cpp
			  Point.cpp
			  Log.cpp
			  Random.cpp
			  Model.cpp
			  MultiVariateModel.cpp
			  Machine.cpp )


export( TARGETS playgroundlib FILE playgroundlib-exports.cmake )

if( NOT ROOT_FOUND )
    target_link_libraries(playgroundlib PUBLIC Eigen3::Eigen)
else()
    add_definitions(-DHAVE_ROOT)
    target_compile_definitions(playgroundlib INTERFACE HAVE_ROOT)
    target_link_libraries(playgroundlib PUBLIC Eigen3::Eigen ROOT::Tree ROOT::Spectrum ROOT::Gpad)
endif()

target_include_directories(playgroundlib PUBLIC ${CMAKE_CURRENT_LIST_DIR})

