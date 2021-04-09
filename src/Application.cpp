#include "Application.h"

#include "Physics.h"
#include "Renderer.h"
#include "DisplayManager.h"
#include "Shader.h"
#include "Input.h"
#include "OBJLoader.h"
#include "Ambient.h"
#include "Terrain.h"

Application Application::s_Application;

static Entity* player = nullptr;
static Shader shader;

static Shader terrainShader;
static Terrain* terrain = nullptr;

static Renderer m_Renderer;
static DisplayManager m_Display;
static InputHandler m_Input;

static unsigned int vaoID;


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
		player->launch();
		return;
	}
	if (key == GLFW_KEY_ESCAPE && mode == GLFW_PRESS)
	{
		m_Renderer.setClearColor( 0.6f, 0.6f, 0.6f );
		m_Display.update();
		m_Input.changeInput();
		m_Renderer.setClearColor( 0.0f, 0.0f, 0.0f );
		m_Display.update();
		return;
	}
	if (key == GLFW_KEY_R && mode == GLFW_PRESS)
	{
		player->setPosition({ 0.0f, -5.0f, -15.0f });
		player->setRotation({ 0.0f, 0.0f, 0.0f });
	}
}

int Application::Init()
{
	s_Application.isRunning = true;


	int width = 720;
	int height = 480;
	const std::string title = "Hello, world!";

	int failed = m_Display.genereate(width, height, title);
	if (failed)
	{
		std::cout << "GL error! " << failed << std::endl;
		return failed;
	}
	m_Renderer.setClearColor(0.18, 0.2, 0.8);
	m_Display.update();

	m_Input.setWindow(m_Display.getWindow());

	float coord[4 * 3] = {
		1.0f, -0.5f, 0.0f,
		1.0f, -0.5f, 1.0f,
		-1.0f, -0.5f, 0.0f,
		-1.0f, -0.5f, 1.0f
	};

	unsigned int indices[6] = {
		0, 1, 2,
		1, 3, 2
	};

	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);

	unsigned int buffer, ibo;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), coord, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	std::string model_name = "colored";
	std::cout << "loading " << model_name << std::endl;
	Model* mod = OBJLoader::LoadObj(model_name);
	if (mod == NULL)
	{
		std::cout << "Couldnt load " << model_name << std::endl;
	}
	std::cout << "Done!" << std::endl;

	player = new Entity();
	player->setModel(mod);

	player->setPosition(glm::vec3(0, 0, -15));
	player->setRotation(glm::vec3(0, 0, 0));

	player->setScale(1);

	terrain = new Terrain(0, 0, 800);
	terrain->generateTerrain();

	std::cout << "hello\n";
	
	glm::mat4 model = player->getTransformationMatrix();
	glm::mat4 Projection = m_Display.getPojectionMatrix();

	Light light(glm::vec3(3.0f, 0.0f, 0.0f), glm::vec3(1, 1, 1));

	shader.loadShader("vertexShader", "fragmentShader");
	shader.bind();

	shader.setUniformM4f("model", model);
	shader.setUniformM4f("proj", Projection);
	shader.setUniformVec3f("LightPos", light.getPosition());
	shader.setUniformVec3f("LightColor", light.getColor());

	terrainShader.loadShader("terrainV", "terrainF");
	terrainShader.bind();
	glm::mat4 terrainMod = terrain->getTransformationMatrix();
	glm::mat4 i(1);

	terrainShader.setUniformM4f("proj", Projection);
	terrainShader.setUniformM4f("model", terrainMod);

	m_Renderer.setClearColor(0.0f, 0.0f, 0.0f);
	m_Display.update();

	s_Application.m_LastFrameTime = (float)glfwGetTime();

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
			break;
		}
	}
	EventManager::handled();
}

void Application::Update()
{
	m_Display.update();
	m_Renderer.prepare();
	float time = (float)glfwGetTime();
	float timestep = time - s_Application.m_LastFrameTime;
	s_Application.m_LastFrameTime = time;

	m_Input.handle(player, timestep);

	Physics::update(player, timestep);
}

void Application::Draw()
{
	m_Renderer.renderTerrain(terrain, terrainShader);
	//terrainShader.bind();
	//glBindVertexArray(vaoID);
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	m_Renderer.render(player, shader);
}

bool Application::IsRunning()
{
	return s_Application.isRunning;
}

void Application::Delete()
{
	delete player->getModel();
	delete player;
	glfwTerminate();
}
