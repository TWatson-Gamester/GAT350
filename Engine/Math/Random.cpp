#include "Random.h"
#include <random>
#include <stdlib.h>
#include <limits>

namespace gn {

	std::default_random_engine g_engine;

	void SeedRandom(unsigned int seed){
		g_engine.seed(seed);
	}

	float Random() { // 0 - 1
		std::uniform_real_distribution<float> distribuition{ 0, 1 };
		return distribuition(g_engine);
	}

	float RandomRange(float min, float max) {
		std::uniform_real_distribution<float> distribuition{ min, max };
		return distribuition(g_engine);
	}

	int RandomInt(){
		std::uniform_int_distribution<int> distribuition{ 0, std::numeric_limits<int>::max() };
		return distribuition(g_engine);
	}

	int RandomInt(int max){
		std::uniform_int_distribution<int> distribuition{ 0, max - 1 };
		return distribuition(g_engine);
	}

	int RandomRangeInt(int min, int max){
		std::uniform_int_distribution<int> distribuition{ min, max };
		return distribuition(g_engine);
	}
}