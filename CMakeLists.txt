cmake_minimum_required(VERSION 3.2)
set (CMAKE_C_STANDARD 11)
set (CMAKE_CXX_STANDARD 11)
project (GameEngine)

include_directories("${PROJECT_SOURCE_DIR}/Engine/Util")
include_directories("${PROJECT_SOURCE_DIR}/Engine/Interface")
include_directories("${PROJECT_SOURCE_DIR}/Engine/Common")
include_directories("${PROJECT_SOURCE_DIR}/Engine/Log")

add_subdirectory(Engine)
add_subdirectory(Platform)
add_subdirectory(Test)