cmake_minimum_required(VERSION 3.16)

project(SCMath)

# -------------------
#      SCMathTest
# -------------------
add_subdirectory(SCMathTest)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(SOURCE_FILES
	${SOURCE_DIR}/Utility.h
	${SOURCE_DIR}/Vec2.h
	${SOURCE_DIR}/Vec2.cpp
	${SOURCE_DIR}/Vec3.h
	${SOURCE_DIR}/Vec3.cpp
	${SOURCE_DIR}/Vec4.h
	${SOURCE_DIR}/Vec4.cpp
	${SOURCE_DIR}/Mat4.h
	${SOURCE_DIR}/Mat4.cpp
	${SOURCE_DIR}/Quat.h
	${SOURCE_DIR}/Quat.cpp
)

add_library(SCMath STATIC ${SOURCE_FILES})
