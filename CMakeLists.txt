cmake_minimum_required(VERSION 3.16)

project(humanGL LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(includes/SDL)

#set(includes/)
#include_directories(includes)
#target_sources(include/*.hpp)
file(GLOB_RECURSE INCLUDE_FILES CONFIGURE_DEPENDS
	includes/*.hpp
)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    src/*.cpp
)

add_executable(${PROJECT_NAME} ${INCLUDE_FILES} ${SRC_FILES})


target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)
