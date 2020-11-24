cmake_minimum_required(VERSION 3.19)

project(SimpleCanvas)

# -------------------
#        GLFW        
# -------------------
find_package(OpenGL REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW lib only")
set(GLFW_INSTALL OFF CACHE BOOL "GLFW lib only")

add_subdirectory(glfw)

# -------------------
#        GLAD        
# -------------------
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Glad)

add_subdirectory(Glad)

# -------------------
#    SimpleCanvas        
# -------------------
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(SOURCE_FILES
	${SOURCE_DIR}/SimpleCanvas.h
	${SOURCE_DIR}/SimpleCanvas/Application.cpp
	${SOURCE_DIR}/SimpleCanvas/Application.h
	${SOURCE_DIR}/SimpleCanvas/Core.h
	${SOURCE_DIR}/SimpleCanvas/EntryPoint.h
	${SOURCE_DIR}/SimpleCanvas/Events/ApplicationEvent.h
	${SOURCE_DIR}/SimpleCanvas/Events/Event.h
	${SOURCE_DIR}/SimpleCanvas/Events/KeyEvent.h
	${SOURCE_DIR}/SimpleCanvas/Events/MouseEvent.h
	${SOURCE_DIR}/SimpleCanvas/Layer.cpp
	${SOURCE_DIR}/SimpleCanvas/Layer.h
	${SOURCE_DIR}/SimpleCanvas/LayerContainer.cpp
	${SOURCE_DIR}/SimpleCanvas/LayerContainer.h
	${SOURCE_DIR}/SimpleCanvas/Logger.cpp
	${SOURCE_DIR}/SimpleCanvas/Logger.h
	${SOURCE_DIR}/SimpleCanvas/Window.cpp
	${SOURCE_DIR}/SimpleCanvas/Window.h
)

add_compile_definitions(SC_BUILD_DLL)

add_library(SimpleCanvas SHARED ${SOURCE_FILES})
target_link_libraries(SimpleCanvas ${OPENGL_LIBRARIES} Glad glfw)

target_include_directories(SimpleCanvas PUBLIC
	${SOURCE_DIR}
	${SOURCE_DIR}/SimpleCanvas
	${SOURCE_DIR}/SimpleCanvas/Events
)

target_precompile_headers(SimpleCanvas PUBLIC ${SOURCE_DIR}/stdafx.h)