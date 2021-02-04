cmake_minimum_required(VERSION 3.16)

project(SimpleCanvas)

# -------------------
#        GLFW        
# -------------------
set(GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW lib only")
set(GLFW_INSTALL OFF CACHE BOOL "GLFW lib only")

add_subdirectory(glfw)

# -------------------
#        GLAD        
# -------------------
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Glad)

add_subdirectory(Glad)

# -------------------
#        SCMath        
# -------------------
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/SCMath)
add_subdirectory(SCMath)

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
	${SOURCE_DIR}/SimpleCanvas/Input/Input.cpp
	${SOURCE_DIR}/SimpleCanvas/Input/Input.h
	${SOURCE_DIR}/SimpleCanvas/Input/InputBindings.h
	${SOURCE_DIR}/SimpleCanvas/Layer.cpp
	${SOURCE_DIR}/SimpleCanvas/Layer.h
	${SOURCE_DIR}/SimpleCanvas/LayerContainer.cpp
	${SOURCE_DIR}/SimpleCanvas/LayerContainer.h
	${SOURCE_DIR}/SimpleCanvas/Logger.cpp
	${SOURCE_DIR}/SimpleCanvas/Logger.h
	${SOURCE_DIR}/SimpleCanvas/Window.cpp
	${SOURCE_DIR}/SimpleCanvas/Window.h
	${SOURCE_DIR}/SimpleCanvas/Renderer/GLContext.h
	${SOURCE_DIR}/SimpleCanvas/Renderer/GLContext.cpp
	${SOURCE_DIR}/SimpleCanvas/Renderer/Shader.h
	${SOURCE_DIR}/SimpleCanvas/Renderer/Shader.cpp
	${SOURCE_DIR}/SimpleCanvas/Renderer/Buffer.h
	${SOURCE_DIR}/SimpleCanvas/Renderer/Buffer.cpp
	${SOURCE_DIR}/SimpleCanvas/Renderer/VertexArray.h
	${SOURCE_DIR}/SimpleCanvas/Renderer/VertexArray.cpp
	${SOURCE_DIR}/SimpleCanvas/Renderer/Renderer.h
	${SOURCE_DIR}/SimpleCanvas/Renderer/Renderer.cpp
	${SOURCE_DIR}/SimpleCanvas/Renderer/RenderCommand.h
	#${SOURCE_DIR}/SimpleCanvas/Renderer/OrthoCamera.h
	#${SOURCE_DIR}/SimpleCanvas/Renderer/OrthoCamera.cpp
)

add_library(SimpleCanvas STATIC ${SOURCE_FILES})
target_link_libraries(SimpleCanvas ${OPENGL_LIBRARIES} Glad glfw SCMath)

target_include_directories(SimpleCanvas PUBLIC
	${SOURCE_DIR}
	${SOURCE_DIR}/SimpleCanvas
	${SOURCE_DIR}/SimpleCanvas/Events
)

target_precompile_headers(SimpleCanvas PUBLIC ${SOURCE_DIR}/stdafx.h)
