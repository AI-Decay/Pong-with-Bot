#pragma once
#include <random>
#include <math.h>
#include <ctime>
#include "SDL.h"

constexpr double PI = 3.14;

class Ball
{
private:
	SDL_Rect rect;
	float speed_x = 0;
	float speed_y = 0;
	float start_x_speed = 0;
	float start_y_speed = 0;
	float max_speed = 16;
	std::mt19937 mt;
public:
	const SDL_Rect GetRect() { return rect; };
	Ball(int _x, int _y, int _size, float speed_x = 4, float speed_y = 1);
	Ball(SDL_Rect& _rect);
	~Ball();
	void RandomPosition(int width, int height, int range);
	void Move(const SDL_Rect& _fRect, const SDL_Rect& _sRect, const SDL_Rect& _wRect, size_t& delta_time, int f_delta_speed = 0, int s_delta_speed = 0);
	void SetMaxSpeed(float _max_speed) { max_speed = _max_speed; }
	std::pair<float, float> GetSpeed() { return { speed_x, speed_y }; }
};