#pragma once
#include <chrono>
class GameTime
{
private:
	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

public:
	GameTime() {};
	
	void ResetTime()
	{
		start = std::chrono::steady_clock::time_point{ std::chrono::steady_clock::now() };
	}

	double Duration()
	{
		std::chrono::duration<long long> duration =
			std::chrono::duration_cast<std::chrono::seconds>(5*(std::chrono::steady_clock::now() - start));

		return static_cast<double>(duration.count());
	}
};