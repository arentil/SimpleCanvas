cmake_minimum_required(VERSION 3.16)
project(MathTest)

# -------------------
#        GTest
# -------------------
add_subdirectory(googletest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# -------------------
#        Math
# -------------------
set(MATH_DIR ${CMAKE_SOURCE_DIR}/SimpleCanvas/Math)
include_directories(${MATH_DIR}/src)


set(SOURCE_FILES
    ${MATH_DIR}/src/Utility.h
    ${MATH_DIR}/src/Vec2.h
    ${MATH_DIR}/src/Vec2.cpp
    ${MATH_DIR}/src/Vec3.h
    ${MATH_DIR}/src/Vec3.cpp
    ${MATH_DIR}/src/Vec4.h
    ${MATH_DIR}/src/Vec4.cpp
    ${MATH_DIR}/src/Mat4.h
    ${MATH_DIR}/src/Mat4.cpp
    ${MATH_DIR}/src/Quat.h
    ${MATH_DIR}/src/Quat.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Vec3Test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Mat4Test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

add_executable(MathTest ${SOURCE_FILES})
target_link_libraries(MathTest PUBLIC gtest gtest_main)
add_test(NAME mathTests COMMAND run)
