cmake_minimum_required(VERSION 3.16)

project(SimpleCanvas VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_VERBOSE_MAKEFILE on)

include_directories(${CMAKE_SOURCE_DIR}/SimpleCanvas/src)
add_subdirectory(SimpleCanvas)

if (MSVC)
  add_compile_options(/W4 /std:c++latest)
  set(CMAKE_CXX_FLAGS_DEBUG "/Od /Wall /std:c++latest")
  set(CMAKE_CXX_FLAGS_RELEASE "/W0 /O2 /DNDEBUG")
else()
  add_compile_options(-std=c++17 -Wall -Wextra -pedantic -Wconversion -Wcast-align -Wunused -Wshadow -Wold-style-cast -lgcov)
  set(CMAKE_CXX_FLAGS_DEBUG "-g")
  set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
endif ()

set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/Sandbox/src)
set(SOURCE_FILES
  ${SOURCE_DIR}/Sandbox.cpp
  ${SOURCE_DIR}/Objects/TextureCube.h
  ${SOURCE_DIR}/Objects/TextureCube.cpp
  ${SOURCE_DIR}/Objects/ColorCube.h
  ${SOURCE_DIR}/Objects/ColorCube.cpp
  ${SOURCE_DIR}/Objects/Teapot.h
  ${SOURCE_DIR}/Objects/Teapot.cpp
  ${SOURCE_DIR}/Objects/Sponza.h
  ${SOURCE_DIR}/Objects/Sponza.cpp
  ${SOURCE_DIR}/Objects/Triangle.h
  ${SOURCE_DIR}/Objects/Triangle.cpp
  ${SOURCE_DIR}/Objects/TileMap.h
  ${SOURCE_DIR}/Objects/TileMap.cpp
  ${SOURCE_DIR}/Objects/BlendTexSquare.h
  ${SOURCE_DIR}/Objects/BlendTexSquare.cpp
  ${SOURCE_DIR}/Objects/Skybox.h
  ${SOURCE_DIR}/Objects/Skybox.cpp
  ${SOURCE_DIR}/Scenes/Scene.cpp
  ${SOURCE_DIR}/Scenes/Scene.h
  ${SOURCE_DIR}/World/World.cpp
  ${SOURCE_DIR}/World/World.h
)

include_directories(${CMAKE_SOURCE_DIR}/Sandbox/src)
add_executable(Sandbox  ${SOURCE_FILES})
target_link_libraries(Sandbox PUBLIC SimpleCanvas)

# move assets folder into binary folder
add_custom_command(TARGET Sandbox PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:Sandbox>/assets)