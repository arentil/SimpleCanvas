cmake_minimum_required(VERSION 3.16)

project(SimpleCanvas VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_SOURCE_DIR}/SimpleCanvas/src)

add_subdirectory(SimpleCanvas)

# if build type is not specified, cmake will assume it is a Release build type
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

if (MSVC)
  add_compile_options(/W4 /std:c++latest) #/WX
  set(CMAKE_CXX_FLAGS_DEBUG "/Od")
  set(CMAKE_CXX_FLAGS_RELEASE "/O2")
  #set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Sandbox)
else()
  add_compile_options(-std=c++17 -Wall -Wextra -pedantic -Wconversion -Wcast-align -Wunused -Wshadow -Wold-style-cast -lgcov)
  set(CMAKE_CXX_FLAGS_DEBUG "-g")
  set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif ()


add_executable(Sandbox ${CMAKE_SOURCE_DIR}/Sandbox/src/Sandbox.cpp)
target_link_libraries(Sandbox PUBLIC SimpleCanvas)

# move assets folder into binary folder
add_custom_command(TARGET Sandbox PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:Sandbox>/assets)