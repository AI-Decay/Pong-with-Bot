#pragma once
#include "Font.h"
#include <memory>
#include <vector>

class Menu
{
private:
	size_t menuPosition = 0;
public:
	std::string path;
	int sizeFont = 0;
	SDL_Color textColor = { 225, 225, 225 };
	SDL_Rect rect = {};
	bool loadMenu = true;
	std::vector<std::unique_ptr<Font>> text;
	void AddText(std::string str, SDL_Rect _rect, SDL_Renderer* renderer, SDL_Color textColor = { 225, 25, 225 });
	Menu(std::string _path, int _sizeFont);
	bool UpMenuPosition();
	bool DownMenuPosition();
	void UpdateColor(SDL_Renderer* renderer);
	const size_t GetMenuPosition() { return menuPosition; }
};