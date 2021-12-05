#include "Engine.h"

int main(int argc, char** argv)
{
	// create engine
	std::unique_ptr<gn::Engine> engine = std::make_unique<gn::Engine>();
	engine->Startup();
	engine->Get<gn::Renderer>()->Create("OpenGL", 800, 600);

	gn::SeedRandom(static_cast<unsigned int>(time(nullptr)));
	gn::SetFilePath("../resources");

	// create scene
	std::unique_ptr<gn::Scene> scene = std::make_unique<gn::Scene>();
	scene->engine = engine.get();

	// load scene
	rapidjson::Document document;
	bool success = gn::json::Load("scenes/main.scn", document);
	scene->Read(document);

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
		engine->Update();
		scene->Update(engine->time.deltaTime);

		// update actor
		auto actor = scene->FindActor("model");
		if (actor != nullptr)
		{
			actor->transform.rotation.y += engine->time.deltaTime;
		}

		engine->Get<gn::Renderer>()->BeginFrame();

		scene->Draw(nullptr);

		engine->Get<gn::Renderer>()->EndFrame();
	}

	return 0;
}
