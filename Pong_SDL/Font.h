#pragma once
#include <string>
#include "SDL_ttf.h"

class Font
{
	int sizeFount = 0; 
	int text_w = 0;
	int text_h = 0;
	std::string date;
	std::string pathFont;
	TTF_Font* font = nullptr;
	SDL_Texture* ftexture = nullptr;
	SDL_Surface* text_surface = nullptr;
	SDL_Rect fontRect;
public:
	Font(std::string _pathFont, SDL_Rect _fontRect, int _sizeFont, SDL_Color _textColor = { 225, 225, 225 });
	~Font();
	const SDL_Rect GetRect() { return fontRect; }
	void ChangeText(std::string text, SDL_Renderer* renderer, SDL_Color color = { 255, 255, 255, 255 });
	void ChangeText(size_t Score, SDL_Renderer* renderer, SDL_Color color = {255, 255, 255, 255});
	void ChangeColor(Uint8 r, Uint8 g, Uint8 b, SDL_Renderer* renderer);
	SDL_Texture& GetTexture() { return *ftexture; }
};
