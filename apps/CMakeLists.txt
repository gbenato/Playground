project(Playground-Apps)
enable_language(CXX)

include_directories(${Playground_SOURCE_DIR}/include)
link_directories(${Playground_SOURCE_DIR}/include)



add_executable(ParameterGenerator ParameterGenerator.cxx)
target_link_libraries(ParameterGenerator PUBLIC playgroundlib)


#set_target_properties( targets...
#    PROPERTIES
#    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
#    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
#    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
#)

