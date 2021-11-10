#pragma once
#include "Types.h"
#include "ColorBuffer.h"
#include "Camera.h"
#include <iostream>

class Scene;
class Buffer;

class Tracer {
public:
	void Trace(Buffer* buffer, Scene* scene, Camera* camera, const std::string& message);

public:
	int samples = 1;
	int depth = 50;
};