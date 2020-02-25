#pragma once
#include <memory>
#include "Paddle.h"
#include "Font.h"

class Player
{
private:
	bool enableBot = false;
protected:
	std::unique_ptr<Font> font = nullptr;
	std::unique_ptr<Paddle> paddle = nullptr;
	int Score = 0;
	int text_w = 0;
	int text_h = 0;
public:
	const SDL_Rect GetFontRect() { return font->GetRect(); }
	void ScoreUp() { Score++; }
	void UpdateText(SDL_Renderer* renderer);
	void MovePaddleUp();
	void MovePaddleDown();
	void MovePaddle(const SDL_Rect& ball_rect = { 0, 0, 0, 0 });
	void EnableBot() { enableBot = true; }
	int  GetSpeedPaddle();
	const SDL_Rect GetRectPaddle();
	SDL_Texture& GetTextTexture();
	Player(std::unique_ptr<Paddle> _paddle, std::unique_ptr<Font> _font);
	~Player();
};
