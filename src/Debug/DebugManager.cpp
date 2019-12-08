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

    void DebugManager::handleInput(InputQueue& inputQueue)
    {
        if (m_debugCamera)
        {
            while (inputQueue.hasEvent())
            {
                auto* camera = static_cast<FreeCamera*>(m_debugCamera.get());
                if (camera->handleEvent(inputQueue.getEvent()))
                    inputQueue.consumeEvent();
                else
                    inputQueue.skipEvent();
            }
        }
    }

    void DebugManager::toggleFreeCamera(DebugConsole::args_t)
    {
        if (m_application.m_gameManager.m_gameRenderer.m_activeCamera.get() == m_debugCamera.get())
            m_application.m_gameManager.m_gameRenderer.m_activeCamera = m_originalCamera;
        else
        {
            m_originalCamera = m_application.m_gameManager.m_gameRenderer.m_activeCamera;
            m_application.m_gameManager.m_gameRenderer.m_activeCamera = m_debugCamera;
            m_debugCamera->setView(m_originalCamera->getView());
        }
    }

    void DebugManager::toggleDebugDraw(DebugConsole::args_t args)
    {
        b2World* world = const_cast<b2World*>(&m_application.m_gameManager.m_game->getGameWorld().m_world);
        m_debugRenderer = DebugRenderer(world);
        m_debugRenderer.setOptions(args);
    }
}
}