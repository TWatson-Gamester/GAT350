#pragma once

namespace gn {
	void SeedRandom(unsigned int seed);

	float Random(); // 0 - 1
	float RandomRange(float min, float max); // min - max

	int RandomInt();
	int RandomInt(int max);
	int RandomRangeInt(int min, int max);

}
