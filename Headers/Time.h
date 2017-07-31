#pragma once

namespace Silver {
	class Time
	{
	private:
		static size_t lastTickTime;
		static float dt;	//Delta-time between frames
	public:
		static void Update();
		static inline float GetDt() { return dt; }
	};
}