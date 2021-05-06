#pragma once

// this file is made just to simplify usage of SimpleCanvas just by including this project like: #include "SimpleCanvas.h"
#include "SimpleCanvas/Application.h"
#include "SimpleCanvas/Logger.h"
//#include "SimpleCanvas/EntryPoint.h"  // this mess #include "SimpleCanvas.h" because of exterm
#include "SimpleCanvas/Canvas.h"

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
#include "SimpleCanvas/Renderer/RenderCommand.h"
#include "SimpleCanvas/Renderer/Renderer.h"
#include "SimpleCanvas/Renderer/Shader.h"
#include "SimpleCanvas/Renderer/Texture.h"
#include "SimpleCanvas/Renderer/Cubemap.h"
#include "SimpleCanvas/Renderer/Texture2d.h"
#include "SimpleCanvas/Renderer/TextureContainer.h"
#include "SimpleCanvas/Renderer/AssetsContainer.h"

/**
 *  Renrerables classes
 */
#include "SimpleCanvas/ObjectLogic/Lights.h"
#include "SimpleCanvas/ObjectLogic/BaseMesh.h"
#include "SimpleCanvas/ObjectLogic/Mesh.h"
#include "SimpleCanvas/ObjectLogic/Model.h"
#include "SimpleCanvas/ObjectLogic/AABB.h"
#include "SimpleCanvas/ObjectLogic/ObjLoader.h"

/**
 *  ObjectTree classes
 */
#include "SimpleCanvas/ObjectLogic/ObjectTree/SCNode.h"
#include "SimpleCanvas/ObjectLogic/ObjectTree/SCObject.h"


/**
 *  Camera classes
 */
#include "SimpleCanvas/Camera/Camera.h"
#include "SimpleCanvas/Camera/FPSCamera.h"
#include "SimpleCanvas/Camera/OrthographicCamera.h"
#include "SimpleCanvas/Camera/PerspectiveCamera.h"
#include "SimpleCanvas/Camera/CameraController.h"