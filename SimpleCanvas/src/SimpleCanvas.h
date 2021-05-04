#pragma once

// this file is made just to simplify usage of SimpleCanvas just by including this project like: #include "SimpleCanvas.h"
#include "SimpleCanvas/Application.h"
#include "SimpleCanvas/Logger.h"
//#include "SimpleCanvas/EntryPoint.h"  // this mess #include "SimpleCanvas.h" because of exterm
#include "SimpleCanvas/Canvas.h"
#include "SimpleCanvas/CameraController.h"

/**
 *  Event classes
 */
#include "SimpleCanvas/Events/Event.h"
#include "SimpleCanvas/Events/ApplicationEvent.h"
#include "SimpleCanvas/Events/KeyEvent.h"
#include "SimpleCanvas/Events/MouseEvent.h"

/**
 *  Input classes
 */
#include "SimpleCanvas/Input/Input.h"
#include "SimpleCanvas/Input/InputBindings.h"

/**
 *  Renderer classes
 */
#include "SimpleCanvas/Renderer/GLContext.h"
#include "SimpleCanvas/Renderer/OrthographicCamera.h"
#include "SimpleCanvas/Renderer/PerspectiveCamera.h"
#include "SimpleCanvas/Renderer/RenderCommand.h"
#include "SimpleCanvas/Renderer/Renderer.h"
#include "SimpleCanvas/Renderer/Shader.h"
#include "SimpleCanvas/Renderer/Texture.h"
#include "SimpleCanvas/Renderer/Cubemap.h"
#include "SimpleCanvas/Renderer/Texture2d.h"

/**
 *  Renrerables classes
 */
#include "SimpleCanvas/Renderables/Lights.h"
#include "SimpleCanvas/Renderables/BaseMesh.h"
#include "SimpleCanvas/Renderables/Mesh.h"
#include "SimpleCanvas/Renderables/Model.h"
#include "SimpleCanvas/Renderables/AABB.h"
#include "SimpleCanvas/Renderables/ObjLoader.h"

/**
 *  ObjectTree classes
 */
#include "SimpleCanvas/Renderables/ObjectTree/SCNode.h"
#include "SimpleCanvas/Renderables/ObjectTree/SCObject.h"