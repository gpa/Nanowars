#include "Debug/DebugManager.hpp"
#include "Core/Application.hpp"

namespace nanowars {
namespace debug {

    DebugManager::DebugManager(Application& application)
        : m_application(application)
        , m_debugRenderer(application.m_gameManager.m_gameWorld.m_world)
        , m_debugConsole(*this)
    {
        initializeCommands();
    }

    void DebugManager::initializeCommands()
    {
        m_debugConsole.registerCommand("debug", std::bind(&DebugManager::toggleDebugDraw, this, std::placeholders::_1));
        m_debugConsole.registerCommand("camera", std::bind(&DebugManager::toggleFreeCamera, this, std::placeholders::_1));
    }

    void DebugManager::update(float dt)
    {
    }

    void DebugManager::render(RenderWindow& window)
    {
        m_debugRenderer.render(window);
    }

    bool DebugManager::handleEvent(const Event& event)
    {
        m_freeCamera.handleEvent(event);
        return false;
    }

    bool DebugManager::handleContinuousEvent(const Mouse& mouse, const Keyboard& keyboard)
    {
        return false;
    }

    void DebugManager::toggleFreeCamera(DebugConsole::args_t)
    {
        if (m_application.m_gameManager.m_activeCamera == static_cast<Camera*>(&m_freeCamera))
            m_application.m_gameManager.m_activeCamera = &m_application.m_gameManager.m_followingCamera;
        else
            m_application.m_gameManager.m_activeCamera = &m_freeCamera;
    }

    void DebugManager::toggleDebugDraw(DebugConsole::args_t args)
    {
        m_debugRenderer.setOptions(args);
    }
}
}