cmake_minimum_required(VERSION 3.15)

set (PROJECT_NAME "tictactoe")
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall -ggdb -DDebug")
#set(CMAKE_CXX_FLAGS_RELEASE_INIT "-DRelease")

#=================== SDL2 ===================
set(SDL2_DIR vendor/SDL)
add_subdirectory(vendor/SDL)

#=================== Game ===================
include_directories(vendor/SDL/include)
include_directories(src/include)

add_executable(${PROJECT_NAME}
  src/main.cpp
  src/appdata.cpp
  src/common.cpp
  src/game.cpp
  src/grid.cpp
  src/sdl_data.cpp
  src/vec.cpp
)

target_link_libraries(${PROJECT_NAME}
  SDL2
)

#if (CMAKE_BUILD_TYPE EQUAL "Debug")
target_compile_options(${PROJECT_NAME} PRIVATE -DDebug)
#endif()
