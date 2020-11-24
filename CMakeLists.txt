cmake_minimum_required(VERSION 3.19)

project(SimpleCanvas VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_SOURCE_DIR}/SimpleCanvas/src)

add_subdirectory(SimpleCanvas)

add_executable(Sandbox ${CMAKE_SOURCE_DIR}/Sandbox/src/Sandbox.cpp)

target_link_libraries(Sandbox PUBLIC SimpleCanvas)

# windows additional flags
if (MSVC)
	#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup")
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Sandbox)
endif()

# custom command for copying SimpleCanvas.dll file into output directory
add_custom_command(TARGET Sandbox POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:SimpleCanvas>
        $<TARGET_FILE_DIR:Sandbox>)