#pragma once

#include "Ball.h"
#include "Player.h"
#include "Menu.h"

enum class Status { PVP = 0, PVB = 1 };

class Pong
{
public:
	Pong();
	~Pong();

	void Init(const std::string title, int x_pos, int y_pos, int width, int height, bool fullscreen);
	void Update();
	void Render();
	void Event();
	void ScoreChange();
	void Timer();
	bool Running() { return isRunning; }
private:
	int fontsize = 68;
	bool isRunning = false;
	std::string fontpath = "arial.ttf";
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	Status curStatus;
	SDL_Rect windowRect = { 0, 0, 0, 0 };
	size_t min = 0;
	size_t tick = 0;
	std::vector<SDL_Rect> line;
	std::unique_ptr<Ball> ball = nullptr;
	std::unique_ptr<Player> player_first = nullptr;
	std::unique_ptr<Player> player_second = nullptr;
	std::unique_ptr<Menu> menu{ new Menu(fontpath, fontsize) };
};