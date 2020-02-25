#include "Paddle.h"

Paddle::Paddle(int _x, int _y, int _width, int _height, int _speed)
	:rect{ _x, _y, _width, _height }, speed(_speed) {}

Paddle::Paddle(SDL_Rect& _rect)
	:rect{ _rect } {}

void Paddle::MoveUp(int min)
{
		rect.y -= speed + countUp / 0.65;
		countUp++;

	if (rect.y < min)
		rect.y = min;
	
	if (countUp >= 10)
	{
		moveUp = false;
		countUp = 0;
	}
	
}

void Paddle::MoveDown(int max)
{
		rect.y += speed + countDown / 0.65;
		countDown++;

	if (rect.y > max)
		rect.y = max;

	if (countDown >= 10)
	{
		moveDown = false;
		countDown = 0;
	}
}

void Paddle::Move(int min, int max)
{
	if (moveUp)
		MoveUp(min);
	else if(moveDown)
		MoveDown(max);
}

int Paddle::GetCurrentSpeed()
{
	if (moveDown)
		return speed + countDown / 4;
	else if (moveUp)
		return speed + countUp / 4;
	else
		return 0;
}