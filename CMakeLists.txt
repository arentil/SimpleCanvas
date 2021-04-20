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
  #set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Sandbox)
else()
  add_compile_options(-std=c++17 -Wall -Wextra -pedantic -Wconversion -Wcast-align -Wunused -Wshadow -Wold-style-cast -lgcov)
  set(CMAKE_CXX_FLAGS_DEBUG "-g")
  set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
endif ()

set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/Sandbox/src)
set(SOURCE_FILES
  ${SOURCE_DIR}/Sandbox.cpp
  ${SOURCE_DIR}/Cube.h
  ${SOURCE_DIR}/Cube.cpp
  ${SOURCE_DIR}/Teapot.h
  ${SOURCE_DIR}/Teapot.cpp
  ${SOURCE_DIR}/Sponza.h
  ${SOURCE_DIR}/Sponza.cpp
  ${SOURCE_DIR}/Triangle.h
  ${SOURCE_DIR}/Triangle.cpp
)

add_executable(Sandbox  ${SOURCE_FILES})
target_link_libraries(Sandbox PUBLIC SimpleCanvas)

# move assets folder into binary folder
add_custom_command(TARGET Sandbox PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:Sandbox>/assets)