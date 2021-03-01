#pragma once

// this file is made just to simplify usage of SimpleCanvas just by including this project like: #include "SimpleCanvas.h"
#include "SimpleCanvas/Application.h"
#include "SimpleCanvas/Logger.h"
#include "SimpleCanvas/EntryPoint.h"
#include "SimpleCanvas/Layer.h"
#include "SimpleCanvas/LayerContainer.h"
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
#include "SimpleCanvas/Renderer/Buffer.h"
#include "SimpleCanvas/Renderer/GLContext.h"
#include "SimpleCanvas/Renderer/OrthographicCamera.h"
#include "SimpleCanvas/Renderer/PerspectiveCamera.h"
#include "SimpleCanvas/Renderer/RenderCommand.h"
#include "SimpleCanvas/Renderer/Renderer.h"
#include "SimpleCanvas/Renderer/Shader.h"
#include "SimpleCanvas/Renderer/VertexArray.h"
#include "SimpleCanvas/Renderer/Texture.h"