#include "Player.h"

Player::Player(std::unique_ptr<Paddle> _paddle, std::unique_ptr<Font> _font)
	:paddle{ std::move(_paddle) }, font{ std::move(_font) } {}

void Player::UpdateText(SDL_Renderer* renderer)
{
	font->ChangeText(Score, renderer);
}

void Player::MovePaddleDown()
{
	paddle->enableMoveDown();
}

void Player::MovePaddleUp()
{
	paddle->enableMoveUp();
}

const SDL_Rect Player::GetRectPaddle()
{
	return paddle->GetRect();
}

int Player::GetSpeedPaddle()
{
	return paddle->GetCurrentSpeed();
}

SDL_Texture& Player::GetTextTexture()
{
	return font->GetTexture();
}

Player::~Player() {}

void Player::MovePaddle(const SDL_Rect& ball_rect)
{
	if (enableBot)
	{
		auto rect = paddle->GetRect();

		if (rect.y + rect.h / 2 > ball_rect.y && (rect.y > ball_rect.y || rect.y + rect.h / 2 < ball_rect.y))
		{
			MovePaddleUp();
			paddle->Move();
		}
		else if (rect.y + rect.h / 2 < ball_rect.y && (rect.y > ball_rect.y || rect.y + rect.h / 2 < ball_rect.y))
		{
			MovePaddleDown();
			paddle->Move();
		}
	}
	else
		paddle->Move();
}