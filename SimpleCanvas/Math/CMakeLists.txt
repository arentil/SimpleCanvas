cmake_minimum_required(VERSION 3.16)

project(Math LANGUAGES CXX)

# -------------------
#       MathTest        
# -------------------
add_subdirectory(MathTest)

# -------------------
# Math Lib Unit Tests        
# -------------------
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(SOURCE_FILES 
	${SOURCE_DIR}/Math.h
	${SOURCE_DIR}/Math.cpp
)

add_library(Math STATIC ${SOURCE_FILES})
