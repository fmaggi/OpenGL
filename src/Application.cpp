#include "Application.h"

#include "Physics.h"
#include "Renderer.h"
#include "DisplayManager.h"
#include "Shader.h"
#include "Input.h"
#include "OBJLoader.h"
#include "Ambient.h"

Application Application::s_Application;

static Entity* player = nullptr;
static Shader shader;
static Camera* camera = new Camera(glm::vec3(0, 0, 0));

static Shader terrainShader;

static Renderer m_Renderer;
static DisplayManager m_Display;
static InputHandler m_Input;

static unsigned int vaoID, vbo, ibo;

static float floor_cord[12] = {
	-0.5f, 0.0f, -0.50f,
	0.50f, 0.0f, -0.50f,
	0.50f, 00.0f, 0.50f,
	-0.50f, 00.0f, 0.50f
};

static unsigned int indices[6] = {
	0, 1, 2, // bl, br, tr
	2, 3, 0 // tr, tl, bl
};

void Application::resize(Event& e)
{
	int width = e.data["w"];
	int height = e.data["h"];
	m_Renderer.setViewPort(width, height);
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
		player->setPosition({ 0.0f, 0.0f, -10.0f });
		player->setRotation({ 0.0f, 0.0f, 0.0f });
		return;
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

	m_Renderer.setViewPort(width, height);
	m_Renderer.setCamera(camera);

	m_Input.setWindow(m_Display.getWindow());

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

	camera->setPlayer(player);

	player->setPosition(glm::vec3(0, 0, -10));
	player->setRotation(glm::vec3(0, 0, 0));
	player->setScale(1);
	player->calculateTransformationMatrix();
	
	Light light(glm::vec3(3.0f, 0.0f, 0.0f), glm::vec3(1, 1, 1));

	shader.loadShader("vertexShader", "fragmentShader");
	shader.bind();

	shader.setUniformVec3f("LightPos", light.getPosition());
	shader.setUniformVec3f("LightColor", light.getColor());

	m_Renderer.setClearColor(0.4f, 0.5f, 0.8f);
	m_Display.update();

	terrainShader.loadShader("terrainV", "terrainF");

	s_Application.m_LastFrameTime = (float)glfwGetTime();

	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), floor_cord, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

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
			s_Application.resize(e);
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

	m_Input.handle(camera, timestep);
	Physics::update(player, timestep);
}

void Application::Draw()
{
	glBindVertexArray(vaoID);
	terrainShader.bind();
	glm::mat4 view = camera->getViewMatrix();
	glm::mat4 proj = m_Renderer.getProjectionMatrix();
	glm::mat4 sc = glm::scale(glm::mat4(1), glm::vec3(5, 1, 5));
	glm::mat4 tr = glm::translate(glm::mat4(1), glm::vec3(0, -3, -10));
	glm::mat4 model = tr * sc;
	terrainShader.setUniformM4f("proj", proj);
	terrainShader.setUniformM4f("view", view);
	terrainShader.setUniformM4f("model", model);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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
	delete camera;
	glfwTerminate();
}
