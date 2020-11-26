cmake_minimum_required(VERSION 3.16)

project(Glad LANGUAGES C DESCRIPTION "OpenGL 4.6")

set(SOURCE_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/include/KHR/khrplatform.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/glad/glad.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c
)

add_library(Glad STATIC ${SOURCE_FILES})

target_include_directories(Glad PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
)