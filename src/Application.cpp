#include "Application.h"
#include "Input.h"

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

void Application::keyPressed(Event& e)
{
	int key = e.data["key"];
	int mode = e.data["mode"];
	if (key == GLFW_KEY_SPACE && mode == GLFW_PRESS)
	{
		s_Application.player->launch();
	}
}

int Application::Init()
{
	s_Application.isRunning = true;

	Light light(glm::vec3(3.0f, 0.0f, 0.0f), glm::vec3(1, 1, 1));

	int width = 1920;
	int height = 1080;
	const std::string title = "Hello, world!";

	int failed = s_Application.m_Display.genereate(width, height, title);
	if (failed)
	{
		std::cout << "GL error! " << failed << std::endl;
		return failed;
	}

	InputHandler::setWindow(s_Application.m_Display.getWindow());

	std::string model_name = "Saturn V";
	std::cout << "loading " << model_name << std::endl;
	Model* mod = OBJLoader::LoadObj(model_name);
	if (mod == NULL)
	{
		std::cout << "Couldnt load " << model_name << std::endl;
	}
	std::cout << "Done!" << std::endl;

	s_Application.player = new Entity();
	s_Application.player->setModel(mod);
	s_Application.player->setPosition(glm::vec3(0, -5, -15));
	s_Application.player->setRotation(glm::vec3(0, 0, 0));
	s_Application.player->setScale(0.3f);

	glm::mat4 model = s_Application.player->getTransformationMatrix();
	glm::mat4 Projection = s_Application.m_Display.getPojectionMatrix();

	s_Application.shader.loadShader("vertexShader", "fragmentShader");
	s_Application.shader.bind();

	s_Application.shader.setUniformM4f("model", model);
	s_Application.shader.setUniformM4f("proj", Projection);
	s_Application.shader.setUniformVec3f("LightPos", light.getPosition());
	s_Application.shader.setUniformVec3f("LightColor", light.getColor());

	return 0;
}

void Application::OnEvent()
{
	std::vector<Event> events = EventManager::pollEvents();
	for (Event e : events)
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
	}
	EventManager::handled();
}

void Application::Update()
{
	OnEvent();
	s_Application.m_Display.update();
	s_Application.m_Renderer.prepare();
	float time = (float)glfwGetTime();
	float timestep = time - s_Application.m_LastFrameTime;
	s_Application.m_LastFrameTime = time;

	Command* command = InputHandler::getCommand();
	if (command)
		command->execute(s_Application.player, timestep);

	s_Application.player->update(timestep);
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
