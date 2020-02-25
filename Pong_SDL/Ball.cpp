#include "Ball.h"

Ball::Ball(int _x, int _y, int _size, float _speed_x, float _speed_y)
	:rect{ _x, _y, _size, _size }, speed_x(_speed_x), start_x_speed(_speed_x), speed_y(_speed_y), start_y_speed(_speed_y) {}

Ball::Ball(SDL_Rect& _rect)
	: rect{_rect} {}

Ball::~Ball() {}

void Ball::Move(const SDL_Rect& _fRect, const SDL_Rect& _sRect, const SDL_Rect& _wRect, size_t& delta_time, int f_delta_speed, int s_delta_speed)
{
	if(speed_x > 0 && speed_x < max_speed)
		speed_x += delta_time;
	else if(speed_x < -max_speed)
		speed_x -= delta_time;

	if (delta_time != 0)
	{
		delta_time = 0;
	}

	if (SDL_HasIntersection(&_fRect, &rect))
	{
		speed_y = abs(speed_y - static_cast<float>(f_delta_speed));

		rect.x += 5;
		speed_x *= -1;
	}
	else if (SDL_HasIntersection(&_sRect, &rect))
	{
		speed_y = abs(speed_y - static_cast<float>(s_delta_speed));

		rect.x -= 5;
		speed_x *= -1;
	}
	else if (rect.y > _wRect.h - 20 || rect.y < 0)
	{
		speed_y *= -1;
	}


	rect.x += speed_x;
	rect.y += speed_y;
}

void Ball::RandomPosition(int width, int height, int range)
{
	mt.seed(time(0));
	std::uniform_int_distribution<> uid_x(width / 2 - range/2, width / 2 + range/2);
	std::uniform_int_distribution<> uid_y(range/2, height - range/2);
	std::uniform_int_distribution<> uid_speed_x(0, 1);
	rect.x = uid_x(mt);
	rect.y = uid_y(mt);

	speed_x = start_x_speed;
	speed_y = start_y_speed;

	if (uid_speed_x(mt))
		speed_x *= -1;

	
}

