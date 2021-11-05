#pragma once
#pragma once
#include <memory>
#include "ColorBuffer.h"
#include <string>

class Image
{
	friend class Framebuffer;
public:
	Image() = default;
	Image(const std::string& filename, uint8_t alpha = 255);

	bool Load(const std::string& filename, uint8_t alpha = 255);
	void Flip();

	//<a variable to hold the width and a variable to hold the height of the image>
	ColorBuffer colorBuffer;
private:
};
