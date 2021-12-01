#include "Engine.h"
#include <glad\glad.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <iostream>
#include <sdl.h>

// vertices
const float vertices[] =
{
	// front
	-1.0f, -1.0f,  1.0, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	 1.0f, -1.0f,  1.0, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	 1.0f,  1.0f,  1.0, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
	-1.0f,  1.0f,  1.0, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
	// back
	-1.0f, -1.0f, -1.0, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	 1.0f, -1.0f, -1.0, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	 1.0f,  1.0f, -1.0, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
	-1.0f,  1.0f, -1.0, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f
};

const GLuint indices[] =
{
	// front
	0, 1, 2,
	2, 3, 0,
	// right
	1, 5, 6,
	6, 2, 1,
	// back
	7, 6, 5,
	5, 4, 7,
	// left
	4, 0, 3,
	3, 7, 4,
	// bottom
	4, 5, 1,
	1, 0, 4,
	// top
	3, 2, 6,
	6, 7, 3
};

int main(int argc, char** argv)
{
	//Create Engine
	gn::Engine engine;
	engine.Startup();
	engine.Get<gn::Renderer>()->Create("OpenGL", 800, 600);

	//Create Scene
	std::unique_ptr<gn::Scene> scene = std::make_unique<gn::Scene>();
	scene->engine = &engine;

	gn::SeedRandom(static_cast<unsigned int>(time(nullptr)));
	gn::SetFilePath("../resources");

	std::shared_ptr<gn::Program> program = engine.Get<gn::ResourceSystem>()->Get<gn::Program>("light_shader");
	std::shared_ptr<gn::Shader> vshader = engine.Get<gn::ResourceSystem>()->Get<gn::Shader>("shaders/light.vert", (void*)GL_VERTEX_SHADER);
	std::shared_ptr<gn::Shader> fshader = engine.Get<gn::ResourceSystem>()->Get<gn::Shader>("shaders/light.frag", (void*)GL_FRAGMENT_SHADER);
	program->AddShader(vshader);
	program->AddShader(fshader);
	program->Link();
	program->Use();

	//Vertex Buffers
	std::shared_ptr<gn::VertexBuffer> vertexBuffer = engine.Get<gn::ResourceSystem>()->Get<gn::VertexBuffer>("cube_mesh");
	vertexBuffer->CreateVertexBuffer(sizeof(vertices), 8, (void*)vertices);
	vertexBuffer->CreateIndexBuffer(GL_UNSIGNED_INT, 36, (void*)indices);
	vertexBuffer->SetAttribute(0, 3, 8 * sizeof(float), 0);
	vertexBuffer->SetAttribute(1, 3, 8 * sizeof(float), 3 * sizeof(float));
	vertexBuffer->SetAttribute(2, 2, 8 * sizeof(float), 6 * sizeof(float));

	//Texture
	auto texture = engine.Get<gn::ResourceSystem>()->Get<gn::Texture>("textures/llama.jpg");
	texture->Bind();

	texture = engine.Get<gn::ResourceSystem>()->Get<gn::Texture>("textures/rocks.bmp");
	texture->Bind();

	texture = engine.Get<gn::ResourceSystem>()->Get<gn::Texture>("textures/wood.png");
	texture->Bind();

	texture = engine.Get<gn::ResourceSystem>()->Get<gn::Texture>("textures/spot.png");
	texture->Bind();

	
		// create camera
		auto actor = gn::ObjectFactory::Instance().Create<gn::Actor>("Actor");
		actor->name = "camera";
		actor->transform.position = glm::vec3{ 0, 0, 5 };
		{
			auto component = gn::ObjectFactory::Instance().Create<gn::CameraComponent>("CameraComponent");
			component->SetPerspective(45.0f, 800.0f / 600.0f, 0.01f, 100.0f);
			actor->AddComponent(std::move(component));
		}
		{
			auto component = gn::ObjectFactory::Instance().Create<gn::FreeCameraController>("FreeCameraController");
			component->speed = 3;
			component->sensitivity = 0.01f;
			actor->AddComponent(std::move(component));
		}
		scene->AddActor(std::move(actor));

	{
		// create cube
		auto actor = gn::ObjectFactory::Instance().Create<gn::Actor>("Actor");
		actor->name = "cube";
		actor->transform.position = glm::vec3{ 0, 0, 0 };

		auto component = gn::ObjectFactory::Instance().Create<gn::ModelComponent>("ModelComponent");
		component->program = engine.Get<gn::ResourceSystem>()->Get<gn::Program>("light_shader");
		component->model = engine.Get<gn::ResourceSystem>()->Get<gn::Model>("models/spot.obj");

		actor->AddComponent(std::move(component));
		scene->AddActor(std::move(actor));
	}

	//lighting
	auto shader = engine.Get<gn::ResourceSystem>()->Get<gn::Program>("light_shader");
	shader->SetUniform("light.ambient", glm::vec3{ 0.2f });
	shader->SetUniform("material.ambient", glm::vec3{ 1 });

	shader->SetUniform("light.diffuse", glm::vec3{ 1 });
	shader->SetUniform("material.diffuse", glm::vec3{ 1 });

	shader->SetUniform("light.specular", glm::vec3{ 1 });
	shader->SetUniform("material.specular", glm::vec3{ 1 });

	shader->SetUniform("light.position", glm::vec4{ 4, 4, 4, 1 });

	glm::vec3 translate{ 0 };
	float angle = 0;
	bool quit = false;

	while (!quit)
	{
		SDL_Event event;
		SDL_PollEvent(&event);

		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				quit = true;
			}
		}

		SDL_PumpEvents();
		engine.Update();
		scene->Update(engine.time.deltaTime);

		// update actor
		auto actor = scene->FindActor("cube");
		if (actor != nullptr)
		{
			actor->transform.rotation.y += engine.time.deltaTime;
		}

		engine.Get<gn::Renderer>()->BeginFrame();

		scene->Draw(nullptr);

		engine.Get<gn::Renderer>()->EndFrame();
	}

	return 0;
}
