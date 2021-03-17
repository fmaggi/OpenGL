#include "DisplayManager.h"

int DisplayManager::genereate(int width, int height, const std::string& title)
{
    m_width = width;
    m_height = height;
    m_title = title.c_str();
    
    aspectRatio = (float)m_width / m_height;
    projectionMatrix = glm::perspective(45.0f, aspectRatio, 0.1f, 100.f);

	if (!glfwInit())
		return -1;

    m_Window = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);
    if (!m_Window)
    {
        glfwTerminate();
        return -2;
    }

    glfwSetWindowUserPointer(m_Window, this);

    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
        DisplayManager* display = (DisplayManager*)glfwGetWindowUserPointer(window);
        display->resize(width, height);
        Events event(EventType::Resize);
        EventManager::dispatch(event);
        });

    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
        Events event(EventType::WinClose);
        EventManager::dispatch(event);
        });

    glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int mode, int mods) {
        DisplayManager* display = (DisplayManager*)glfwGetWindowUserPointer(window);

        Events event(EventType::KeyPressed);
        event.data["key"] = key;
        event.data["mode"] = mode;
        event.data["scancode"] = scancode;
        EventManager::dispatch(event);
        });

    glfwMakeContextCurrent(m_Window);
       
    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        std::cout << "Error!" << glewGetErrorString(err) <<std::endl;
        return -3;
    }
	return 0;
}

void DisplayManager::resize(int w, int h)
{
    m_width = w;
    m_height = h;
    aspectRatio = (float)m_width / m_height;
    projectionMatrix = glm::perspective(45.0f, aspectRatio, 0.1f, 100.f);
}

void DisplayManager::update()
{
    glfwSwapBuffers(m_Window);
    glfwPollEvents();
}
