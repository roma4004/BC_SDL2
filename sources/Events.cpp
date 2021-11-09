//
// Created by d.romanichenko on 15-Jul-21.
//

#include <SDL2/SDL.h>
#include <Tank.hpp>

#include <Events.hpp>
#include <Battlefield.hpp>

void Events::OnKeyPressed(const SDL_Keycode &key)
{
	if		(key == SDLK_UP)	isPressedUpP1		= true;
	else if	(key == SDLK_DOWN)	isPressedDownP1		= true;
	if		(key == SDLK_LEFT)	isPressedLeftP1		= true;
	else if	(key == SDLK_RIGHT)	isPressedRightP1	= true;
	if		(key == SDLK_SPACE)	isPressedFireP1		= true;

	if		(key == SDLK_w)		isPressedUpP2		= true;
	else if	(key == SDLK_s)		isPressedDownP2		= true;
	if		(key == SDLK_a)		isPressedLeftP2		= true;
	else if	(key == SDLK_d)		isPressedRightP2	= true;
	if		(key == SDLK_LCTRL)	isPressedFireP2		= true;
}
void Events::OnKeyReleased(const SDL_Keycode &key)
{
	if		(key == SDLK_p)		bf.isGamePaused = !bf.isGamePaused;
	else if	(key == SDLK_m)		bf.isInMenu = !bf.isInMenu;

	if		(key == SDLK_UP)	isPressedUpP1		= false;
	else if	(key == SDLK_DOWN)	isPressedDownP1		= false;
	if		(key == SDLK_LEFT)	isPressedLeftP1		= false;
	else if	(key == SDLK_RIGHT)	isPressedRightP1	= false;
	if		(key == SDLK_SPACE)	isPressedFireP1		= false;

	if		(key == SDLK_w)		isPressedUpP2		= false;
	else if	(key == SDLK_s)		isPressedDownP2		= false;
	if		(key == SDLK_a)		isPressedLeftP2		= false;
	else if	(key == SDLK_d)		isPressedRightP2	= false;
	if		(key == SDLK_LCTRL)	isPressedFireP2		= false;
}

void Events::EventHandler()
{
	SDL_Event event;
	SDL_Keycode key_code;
	while (SDL_PollEvent(&event))
	{
		key_code = event.key.keysym.sym;
		if (event.type == SDL_QUIT
		|| (event.type == SDL_KEYDOWN && key_code == SDLK_ESCAPE))
		{
			isMainLoopActive = false;
				SDL_Quit();
		}
		else if (event.type == SDL_KEYDOWN)
			OnKeyPressed(event.key.keysym.sym);
		else if (event.type == SDL_KEYUP)
			OnKeyReleased(event.key.keysym.sym);
//		else if (event.type == sf::Event::MouseMoved)
//		{
			/* move cursor inside the window to observe how the counter
			   behaves while pressing the keys */
			//					std::cout << keyCounter << std::endl;
//		}
	}
}
