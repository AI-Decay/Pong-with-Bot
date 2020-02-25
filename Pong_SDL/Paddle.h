#pragma once
#include <SDL.h>

class Paddle
{
private:
	SDL_Rect rect;
	bool moveUp = false;
	bool moveDown = false;
	int countUp = 0;
	int countDown = 0;
	int speed = 2;
public:
	Paddle(int _x, int _y, int _width, int _height, int _speed = 10);
	Paddle(SDL_Rect& _rect);
	void MoveUp(int min = 0);
	void MoveDown(int max = 800);
	void enableMoveUp() { moveUp = true; }
	void enableMoveDown() { moveDown = true; }
	void Move(int min = 0, int max = 800);
	int GetCurrentSpeed();
	SDL_Rect GetRect() { return rect; }
};