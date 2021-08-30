#include "DisplayManager.h"

#include "EventManager.h"

void ErrorCallback(int, const char* err_str)
{
    std::cout << "GLFW Error: " << err_str << std::endl;
}

int DisplayManager::genereate(int width, int height, const std::string& title)
{
    m_width = width;
    m_height = height;
    m_title = title.c_str();
    
    aspectRatio = (float)m_width / m_height;
    glfwSetErrorCallback(ErrorCallback);

	if (!glfwInit())
		return -1;


    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Window = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);
    if (!m_Window)
    {
        glfwTerminate();
        return -2;
    }

    glfwSetWindowUserPointer(m_Window, this);

    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
        DisplayManager* display = (DisplayManager*)glfwGetWindowUserPointer(window);
        Event event(EventType::Resize);
        event.data["w"] = width;
        event.data["h"] = height;

        display->resize(width, height);

        EventManager::dispatch(event);
        });

    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
        Event event(EventType::WinClose);
        EventManager::dispatch(event);
        });

    glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int mode, int mods) {
        DisplayManager* display = (DisplayManager*)glfwGetWindowUserPointer(window);

        Event event(EventType::KeyPressed);
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
    aspectRatio = (float)w / h;
}

void DisplayManager::update()
{
    glfwSwapBuffers(m_Window);
    glfwPollEvents();
}
