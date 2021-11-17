#include "Texture.h"
#include "Graphics/Renderer.h"
//#include <SDL_image.h>
#include <iostream>
#include <cassert>

namespace gn {

	Texture::Texture(Renderer* renderer){
		this->renderer = renderer->renderer;
	}

	bool Texture::Load(const std::string& name, void* data){
		assert(data);
		renderer = static_cast<Renderer*>(data)->renderer;

		//SDL_Surface* surface = IMG_Load(name.c_str());
		//if (surface == nullptr) {
		//	std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		//	return false;
		//}

		////create texture
		//texture = SDL_CreateTextureFromSurface(renderer, surface);
		//SDL_FreeSurface(surface);
		//if (texture == nullptr) {
		//	std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		//	return false;
		//}

		return true;
	}
	glm::vec2 Texture::GetSize() const
	{
		SDL_Point point;
		SDL_QueryTexture(texture, nullptr, nullptr, &point.x, &point.y);

		return { point.x, point.y };
	}

	bool Texture::Create(SDL_Surface* surface){

		// create texture
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
		if (texture == nullptr)
		{
			std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
			return false;
		}

		return true;
	}
}