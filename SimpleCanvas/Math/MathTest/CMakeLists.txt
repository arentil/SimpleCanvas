cmake_minimum_required(VERSION 3.16)
project(MathTest)

# -------------------
#        GTest        
# -------------------
add_subdirectory(googletest)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# -------------------
# Math Lib Unit Tests        
# -------------------
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(SOURCE_FILES 
	${SOURCE_DIR}/MathTest.cpp
)


add_executable(MathTests ${SOURCE_FILES})
target_link_libraries(MathTests PUBLIC gtest gtest_main)

enable_testing()
add_test(NAME MathTests COMMAND run)
