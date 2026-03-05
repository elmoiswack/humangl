cmake_minimum_required(VERSION 3.16)

project(humanGL LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(includes/SDL)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    src/*.cpp
)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/includes
)

# target_compile_options(${PROJECT_NAME}
#     PRIVATE
#         -Wall
#         -Wextra
#         -Werror
# )

target_compile_options(${PROJECT_NAME}
    PRIVATE
        -g
        -fsanitize=address
)

target_link_options(${PROJECT_NAME}
    PRIVATE
        -fsanitize=address
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE SDL3::SDL3
)