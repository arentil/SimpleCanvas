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
find_package(OpenGL REQUIRED)
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
	${SOURCE_DIR}/SimpleCanvas/CameraController.cpp
	${SOURCE_DIR}/SimpleCanvas/CameraController.h
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
	${SOURCE_DIR}/SimpleCanvas/Renderer/Buffer.cpp
	${SOURCE_DIR}/SimpleCanvas/Renderer/Buffer.h
	${SOURCE_DIR}/SimpleCanvas/Renderer/Camera.cpp
	${SOURCE_DIR}/SimpleCanvas/Renderer/Camera.h
	${SOURCE_DIR}/SimpleCanvas/Renderer/Cubemap.cpp
	${SOURCE_DIR}/SimpleCanvas/Renderer/Cubemap.h
	${SOURCE_DIR}/SimpleCanvas/Renderer/GLContext.cpp
	${SOURCE_DIR}/SimpleCanvas/Renderer/GLContext.h
	${SOURCE_DIR}/SimpleCanvas/Renderer/OrthographicCamera.cpp
	${SOURCE_DIR}/SimpleCanvas/Renderer/OrthographicCamera.h
	${SOURCE_DIR}/SimpleCanvas/Renderer/PerspectiveCamera.cpp
	${SOURCE_DIR}/SimpleCanvas/Renderer/PerspectiveCamera.h
	${SOURCE_DIR}/SimpleCanvas/Renderer/RenderCommand.h
	${SOURCE_DIR}/SimpleCanvas/Renderer/Renderer.cpp
	${SOURCE_DIR}/SimpleCanvas/Renderer/Renderer.h
	${SOURCE_DIR}/SimpleCanvas/Renderer/Shader.cpp
	${SOURCE_DIR}/SimpleCanvas/Renderer/Shader.h
	${SOURCE_DIR}/SimpleCanvas/Renderer/Texture2d.cpp
	${SOURCE_DIR}/SimpleCanvas/Renderer/Texture2d.h
	${SOURCE_DIR}/SimpleCanvas/Renderer/Texture.h
	${SOURCE_DIR}/SimpleCanvas/Renderer/VertexArray.cpp
	${SOURCE_DIR}/SimpleCanvas/Renderer/VertexArray.h
	${SOURCE_DIR}/SimpleCanvas/Tools/FileReader.h
	${SOURCE_DIR}/SimpleCanvas/Tools/StringUtils.h
	${SOURCE_DIR}/SimpleCanvas/Tools/stb_image.cpp
	${SOURCE_DIR}/SimpleCanvas/Tools/stb_image.h
	${SOURCE_DIR}/SimpleCanvas/Tools/tiny_obj_loader.cpp
	${SOURCE_DIR}/SimpleCanvas/Tools/tiny_obj_loader.h
	${SOURCE_DIR}/SimpleCanvas/Window.cpp
	${SOURCE_DIR}/SimpleCanvas/Window.h
	${SOURCE_DIR}/SimpleCanvas/Renderables/ObjLoader.h
	${SOURCE_DIR}/SimpleCanvas/Renderables/ObjLoader.cpp
	${SOURCE_DIR}/SimpleCanvas/Renderables/BaseMesh.h
	${SOURCE_DIR}/SimpleCanvas/Renderables/Mesh.cpp
	${SOURCE_DIR}/SimpleCanvas/Renderables/Mesh.h
	${SOURCE_DIR}/SimpleCanvas/Renderables/Model.cpp
	${SOURCE_DIR}/SimpleCanvas/Renderables/Model.h
	${SOURCE_DIR}/SimpleCanvas/Renderables/ObjectTree/SCNode.h
	${SOURCE_DIR}/SimpleCanvas/Renderables/ObjectTree/SCNode.cpp
	${SOURCE_DIR}/SimpleCanvas/Renderables/ObjectTree/SCObject.h
	${SOURCE_DIR}/SimpleCanvas/Renderables/ObjectTree/SCObject.cpp
)

add_library(SimpleCanvas STATIC ${SOURCE_FILES})
target_link_libraries(SimpleCanvas ${OPENGL_LIBRARIES} Glad glfw SCMath)

target_include_directories(SimpleCanvas PUBLIC
	${SOURCE_DIR}
	${SOURCE_DIR}/SimpleCanvas
	${SOURCE_DIR}/SimpleCanvas/Events
)

target_precompile_headers(SimpleCanvas PUBLIC ${SOURCE_DIR}/stdafx.h)
