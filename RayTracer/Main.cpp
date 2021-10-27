#include "Renderer.h"
#include "Framebuffer.h"
#include "PostProcess.h"
#include "Image.h"
#include "Tracer.h"
#include "Scene.h"

#include <iostream>
#include <SDL.h>

int main(int, char**){
	const int WIDTH = 800;
	const int HEIGHT = 600;

	std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>();
	renderer->Initialize(WIDTH, HEIGHT);

	std::unique_ptr<Framebuffer> framebuffer = std::make_unique<Framebuffer>(renderer.get(), renderer.get()->width, renderer.get()->height);

	// ray tracer
	std::unique_ptr<Tracer> tracer = std::make_unique<Tracer>();

	// scene
	std::unique_ptr<Scene> scene = std::make_unique<Scene>();

	// plane
	scene->Add(std::move(std::make_unique<Plane>(glm::vec3{ 0, -5, 0 }, glm::vec3{ 0, 1, 0 })));

	// sphere
	std::unique_ptr<Sphere> sphere = std::make_unique<Sphere>(glm::vec3{ 0, 0, -10 }, 3.0f);
	scene->Add(std::move(sphere));
	
		framebuffer->Clear({0,0,0,0});
		tracer->Trace(framebuffer->colorBuffer, scene.get());
		framebuffer->Update();

	bool quit = false;
	SDL_Event event;
	while (!quit)
	{
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}


		renderer->CopyBuffer(framebuffer.get());

		renderer->Present();
	}

	SDL_Quit();

	return 0;
}