#include "Application.h"

Application Application::s_Application;

void Application::resize()
{
	glm::mat4 proj = m_Display.getPojectionMatrix();
	shader.setUniformM4f("proj", proj);
}

void Application::close()
{
	s_Application.isRunning = false;
}

void Application::keyPressed(Events& e)
{
	int key = e.dataMap["key"];
	int mode = e.dataMap["mode"];
	if (key == GLFW_KEY_SPACE && mode == GLFW_PRESS)
	{
		//s_Application.player.launch();
		std::cout << "Launching\n";
	}
}

int Application::Init()
{
	s_Application.isRunning = true;

	Light light(glm::vec3(3.0f, 0.0f, 0.0f), glm::vec3(1, 1, 1));
	s_Application.m_Renderer.setLight(&light);

	int width = 1280;
	int height = 720;
	float aspectRatio = (float)width / height;
	const std::string title = "Hello, world!";

	int failed = s_Application.m_Display.genereate(width, height, title);
	if (failed)
	{
		std::cout << "GL error! " << failed << std::endl;
		return failed;
	}

	s_Application.window = s_Application.m_Display.getWindow();

	std::string model_name = "Saturn V";
	std::cout << "loading " << model_name << std::endl;
	Model* mod = OBJLoader::LoadObj(model_name);
	if (mod == NULL)
	{
		std::cout << "Couldnt load " << model_name << std::endl;
	}
	std::cout << "Done!" << std::endl;

	s_Application.player = new Entity;
	s_Application.player->setModel(mod);
	s_Application.player->setPosition(glm::vec3(0, 0, -7));
	s_Application.player->setRotation(glm::vec3(0, 0, 0));
	s_Application.player->setScale(0.7f);

	glm::mat4 model = s_Application.player->getTransformationMatrix();

	glm::mat4 Projection = glm::perspective(45.0f, aspectRatio, 0.1f, 100.f);

	s_Application.shader.loadShader("vertexShader", "fragmentShader");
	s_Application.shader.bind();

	s_Application.shader.setUniformM4f("model", model);
	s_Application.shader.setUniformM4f("proj", Projection);
	s_Application.shader.setUniformVec3f("LightPos", light.getPosition());
	s_Application.shader.setUniformVec3f("LightColor", light.getColor());

	return 0;
}

void Application::Event()
{
	std::vector<Events> events = EventManager::pollEvents();
	for (Events e : events)
	{
		EventType t = e.getType();
		switch (t)
		{
		case EventType::Resize:
			s_Application.resize();
			break;
		case EventType::WinClose:
			s_Application.close();
			break;
		case EventType::KeyPressed:
			s_Application.keyPressed(e);
			break;
		default:
			continue;
		}
		e.handled = true;
	}
	EventManager::handled();
}

void Application::Update()
{
	Event();
	s_Application.m_Display.update();
	s_Application.m_Renderer.prepare();
	float time = (float)glfwGetTime();
	float timestep = time - s_Application.m_LastFrameTime;
	s_Application.m_LastFrameTime = time;

	s_Application.player->update(timestep, s_Application.window);
}

void Application::Draw()
{
	glm::mat4 model = s_Application.player->getTransformationMatrix();
	s_Application.shader.setUniformM4f("model", model);
	s_Application.m_Renderer.renderEntity(s_Application.player);
}

bool Application::IsRunning()
{
	return s_Application.isRunning;
}

void Application::Delete()
{
	delete s_Application.player;
	glfwTerminate();
}
