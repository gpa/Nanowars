#include "Debug/DebugManager.hpp"
#include "Core/Application.hpp"

namespace nanowars {
namespace debug {

    DebugManager::DebugManager(Application& application)
        : m_application(application)
        , m_debugConsole(*this)
        , m_debugCamera(std::make_shared<FreeCamera>())
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
        if (m_debugCamera)
            static_cast<FreeCamera*>(m_debugCamera.get())->handleEvent(event);
        
        return false;
    }

    bool DebugManager::handleContinuousEvent(const Mouse& mouse, const Keyboard& keyboard)
    {
        return false;
    }

    void DebugManager::toggleFreeCamera(DebugConsole::args_t)
    {
        if (m_application.m_gameManager.m_activeCamera.get() != m_originalCamera.get())
            m_application.m_gameManager.m_activeCamera = m_originalCamera;
        else
            m_application.m_gameManager.m_activeCamera = m_debugCamera;
    }

    void DebugManager::toggleDebugDraw(DebugConsole::args_t args)
    {
        m_debugRenderer = DebugRenderer(&m_application.m_gameManager.m_gameWorld.get()->m_world);
        m_debugRenderer.setOptions(args);
    }
}
}