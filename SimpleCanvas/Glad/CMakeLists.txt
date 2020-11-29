cmake_minimum_required(VERSION 3.16)

project(Glad LANGUAGES C DESCRIPTION "OpenGL 4.6")

set(SOURCE_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/include/KHR/khrplatform.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/glad/glad.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c
)

add_library(Glad STATIC ${SOURCE_FILES})
set_property(TARGET Glad PROPERTY POSITION_INDEPENDENT_CODE ON)

target_include_directories(Glad PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
)