#include <memory>
#include "Pong.h"


int width = 1440;
int height = 900;

int SDL_main(int argc, char* argv[])
{
	
	const int FPS = 120;
	constexpr int frameDelay = 1000 / FPS;
	
	int frametime;

	std::unique_ptr<Pong> gPong{ new Pong() };

	gPong->Init("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, false);

	while (gPong->Running())
	{
		frametime = SDL_GetTicks();

		gPong->Event();
		gPong->Update();
		gPong->Render();

		frametime = SDL_GetTicks() - frametime;

		if (frameDelay > frametime)
			SDL_Delay(frameDelay - frametime);
	}


	return 0;
}