project(Playground-Apps)
enable_language(CXX)

include_directories(${Playground_SOURCE_DIR}/include)
link_directories(${Playground_SOURCE_DIR}/include)


add_executable(ParameterGenerator ParameterGenerator.cxx)

target_link_libraries(ParameterGenerator PUBLIC playgroundlib)


