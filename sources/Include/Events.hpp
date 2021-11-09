//
// Created by d.romanichenko on 15-Jul-21.
//

#ifndef EVENTS_HPP
#define EVENTS_HPP

#include <list>

#include <SDL2/SDL.h>

#include <IMovableObject.hpp>
#include <Battlefield.hpp>
#include <IDrawable.hpp>

class Events
{
public:
	Events(
		SDL_Window* Window,
		Battlefield& Bf)
	:
		window(Window),
		bf(Bf)
	{ }

	SDL_Window* window;
	Battlefield& bf;

	bool isMainLoopActive = true;

	bool isPressedUpP1    = false;
	bool isPressedLeftP1  = false;
	bool isPressedDownP1  = false;
	bool isPressedRightP1 = false;
	bool isPressedFireP1  = false;

	bool isPressedUpP2    = false;
	bool isPressedLeftP2  = false;
	bool isPressedDownP2  = false;
	bool isPressedRightP2 = false;
	bool isPressedFireP2  = false;


	void EventHandler();

	void OnKeyPressed (const SDL_Keycode &key);
	void OnKeyReleased(const SDL_Keycode &key);
};

#endif //EVENTS_HPP
