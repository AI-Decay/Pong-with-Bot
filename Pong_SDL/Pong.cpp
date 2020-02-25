#include "Pong.h"


Pong::Pong() {}

void Pong::Init(const std::string title, int x_pos, int y_pos, int width, int height, bool fullscreen) 
{
	int flags = 0;

	if (fullscreen) flags = SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title.c_str(), x_pos, y_pos, width, height, flags);

		if (window)
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		}

		isRunning = true;
	}
	else
		isRunning = false;


	int line_width = 10;
	int line_height = 50;
	int line_distance = 35;

	for (int i = 0; i < height; i += line_height + line_distance)
	{
		line.push_back(SDL_Rect{width/2 - line_width/2, i, line_width, line_height});
	}
	
	SDL_Rect first_rect{ 50, height/2 - 50, 20, 100 };
	SDL_Rect second_rect{ 1370, height / 2 - 50, 20, 100 };
	SDL_Rect first_font{ 200, 100 };
	SDL_Rect second_font{ width - 220, 100 };
	windowRect = { x_pos, y_pos, width, height };
	
	int size_ball = 10;

	menu->AddText("Player vs Player", { width / 2 - 230, height - 650 }, renderer);
	menu->AddText("Player vs Bot",    { width / 2 - 230, height - 400 }, renderer);
	menu->UpdateColor(renderer);

	player_first  = std::unique_ptr<Player>( std::make_unique<Player>(std::make_unique<Paddle>(first_rect), std::make_unique<Font>(fontpath, first_font,  fontsize)));
	player_second = std::unique_ptr<Player>( std::make_unique<Player>(std::make_unique<Paddle>(second_rect), std::make_unique<Font>(fontpath, second_font, fontsize)));


	ball = std::make_unique<Ball>(0, 0, size_ball);
	ball->RandomPosition(width, height, 200);

	player_first->UpdateText(renderer);
	player_second->UpdateText(renderer);
}

void Pong::Event()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	if (event.type == SDL_QUIT)
	{
		isRunning = false;
	}

	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	if (!menu->loadMenu)
	{
		if (currentKeyStates[SDL_SCANCODE_UP])
		{
			player_first->MovePaddleUp();
		}
		if (currentKeyStates[SDL_SCANCODE_DOWN])
		{
			player_first->MovePaddleDown();
		}
		if (curStatus == Status::PVP)
		{
			if (currentKeyStates[SDL_SCANCODE_LEFT])
			{
				player_second->MovePaddleUp();
			}
			if (currentKeyStates[SDL_SCANCODE_RIGHT])
			{
				player_second->MovePaddleDown();
			}
		}
	}
	else
	{
		if (SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_UP)
			{
				if(menu->DownMenuPosition())
				   menu->UpdateColor(renderer);
			}
		
			if (event.key.keysym.sym == SDLK_DOWN)
			{ 
				if (menu->UpMenuPosition())
					menu->UpdateColor(renderer);
			}
			if (event.key.keysym.sym == SDLK_RETURN)
			{
				switch (static_cast<Status>(menu->GetMenuPosition()))
				{
					case Status::PVP:
					{
						curStatus = Status::PVP;
						menu->loadMenu = false;
					}
						break;
					case Status::PVB:
					{
						curStatus = Status::PVB;
						player_second->EnableBot();
						menu->loadMenu = false;
					}
						break;
					default:
						break;
				}
			}
		}
		
	}

}

void Pong::Update()
{
	if (!menu->loadMenu)
	{
		player_first->MovePaddle();
		player_second->MovePaddle(ball->GetRect());
		ball->Move(player_first->GetRectPaddle(), player_second->GetRectPaddle(), windowRect, min, player_first->GetSpeedPaddle(), player_second->GetSpeedPaddle());
		ScoreChange();
		Timer();
	}
}

void Pong::Render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	if (!menu->loadMenu)
	{
		SDL_RenderCopy(renderer, &player_first->GetTextTexture(), NULL, &player_first->GetFontRect());
		SDL_RenderCopy(renderer, &player_second->GetTextTexture(), NULL, &player_second->GetFontRect());

		SDL_RenderFillRect(renderer, &player_first->GetRectPaddle());
		SDL_RenderFillRect(renderer, &player_second->GetRectPaddle());
		SDL_RenderFillRect(renderer, &ball->GetRect());

		for (const auto x : line)
		{
			SDL_RenderFillRect(renderer, &x);
		}
	}
	else
	{
		for (const auto& x : menu->text)
		{
			SDL_RenderCopy(renderer, &x->GetTexture(), NULL, &x->GetRect());
		}
	}
	SDL_RenderPresent(renderer);

}

void Pong::ScoreChange()
{

	if (ball->GetRect().x > windowRect.w)
	{
		player_first->ScoreUp();
		player_first->UpdateText(renderer);
		ball->RandomPosition(windowRect.w, windowRect.h, 200);
		
	}

	else if (ball->GetRect().x < 0)
	{
		player_second->ScoreUp();
		player_second->UpdateText(renderer);
		ball->RandomPosition(windowRect.w, windowRect.h, 200);
	}
}

void Pong::Timer()
{
	tick++;
	if (tick / 600 >= 1) // 600 = 120 * 5 - speed up every 10 sec
	{
		min++;
		tick = 0;
	}
}

Pong::~Pong() 
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

