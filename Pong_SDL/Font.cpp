#include "Font.h"

Font::Font(std::string _pathFont, SDL_Rect _fontRect, int _sizeFont, SDL_Color _textColor)
	: pathFont(_pathFont), fontRect(_fontRect), sizeFount(_sizeFont)
{
	if (TTF_Init() >= 0)
		font = TTF_OpenFont(pathFont.c_str(), sizeFount);

};


void Font::ChangeText(size_t Score, SDL_Renderer* renderer, SDL_Color color)
{
	ChangeText(std::to_string(Score), renderer, color);
}

void Font::ChangeText(std::string text, SDL_Renderer* renderer, SDL_Color color)
{
	date = std::move(text);
	if (font != NULL)
	{
		text_surface = TTF_RenderText_Solid(font, date.c_str(), color);
		if (text_surface != NULL)
		{
			SDL_DestroyTexture(ftexture);

			ftexture = SDL_CreateTextureFromSurface(renderer, text_surface);

			if (ftexture != NULL)
			{
				text_w = text_surface->w;
				text_h = text_surface->h;

				SDL_FreeSurface(text_surface);

				fontRect = { fontRect.x, fontRect.y, text_w, text_h };
			}
		}
	}
}

void Font::ChangeColor(Uint8 r, Uint8 g, Uint8 b, SDL_Renderer* renderer)
{
	ChangeText(date, renderer, SDL_Color{ r,g,b });
}

Font::~Font()
{
	SDL_DestroyTexture(ftexture);
}