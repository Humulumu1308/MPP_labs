cmake_minimum_required(VERSION 3.10)

project(LAB0_Sequence)

set(CMAKE_CXX_STANDARD 17)

add_library(sequence_lib SHARED
	src/ArraySequence.cpp 
	src/ListSequence.cpp
)
target_include_directories(sequence_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/heads)

add_executable(${PROJECT_NAME}_EXAMPLE
	src/SequenceExampleApp.cpp
)
target_link_libraries(${PROJECT_NAME}_EXAMPLE PUBLIC sequence_lib)

add_executable(${PROJECT_NAME}_TESTS
	src/SequenceTests.cpp
)
target_link_libraries(${PROJECT_NAME}_TESTS PUBLIC sequence_lib)
