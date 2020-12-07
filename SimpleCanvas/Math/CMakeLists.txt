cmake_minimum_required(VERSION 3.16)

project(Math)

# -------------------
#      MathTest
# -------------------
add_subdirectory(MathTest)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(SOURCE_FILES 
	${SOURCE_DIR}/Vec3.h
	${SOURCE_DIR}/Vec3.cpp
	${SOURCE_DIR}/Utility.h
)

add_library(Math STATIC ${SOURCE_FILES})
