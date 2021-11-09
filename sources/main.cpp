#include <iostream>
#include <ObjectImage.hpp>
#include <Tank.hpp>
#include <Battlefield.hpp>
#include <Bullet.hpp>
#include "Events.hpp"
#include "PlayerAI.hpp"
#include <chrono>
#include <Logics.hpp>
#include <Render.hpp>
#include <Player.hpp>
#include <ObjectsManager.hpp>

//TODO list:
//make reload interval
//mayShootAI
//animatedImage : public objectImage
//explosion for bullets
//sounds
//take screenshot // Save the image to a file //if (!image.saveToFile("result.png")) return -1;
//new random generator

//matrix bonus:	when bullet see player at front then bullet speed slow down by step each frame,
//				when bonus expired or player move away speed set to normal

int main(int argv, char** args)
{
	const int SCREEN_WIDTH = 1024;
	const int SCREEN_HEIGHT = 768;
//INIT
	if( SDL_Init( SDL_INIT_EVERYTHING ) != 0 )
	{

//		SDL_DisplayMode displayMode;
//		int request = SDL_GetDesktopDisplayMode(0,&displayMode);
//	SDL_Window *win = SDL_CreateWindow("Hello World!", 0, 0, displayMode.w, displayMode.h, SDL_WINDOW_SHOWN);

		std::cout << "Can't init video: " << SDL_GetError() << std::endl;
		return false;
//		SDL_INIT_TIMER — подключение таймера;
//		SDL_INIT_AUDIO — подключение аудио;
//		SDL_INIT_VIDEO — подключение видео, автоматически подключаются события;
//		SDL_INIT_JOYSTICK — подключение управления джойстиком;
//		SDL_INIT_HAPTIC — тактильная подсистема (не знаю что это, если честно);
//		SDL_INIT_GAMECONTROLER — подключает управление, автоматически подключается джойстик;
//		SDL_INIT_EVENTS — подключает обработку событий;
//		SDL_INIT_EVERYTHING — подключает всё, выше перечисленное;
//		SDL_INIT_NOPARACHUTE — проверка на совместимость.
	}
	int flags = IMG_INIT_PNG;
	if ( !( IMG_Init( flags ) & flags ) )
	{
		std::cout << "Can't init image: " << IMG_GetError() << std::endl;
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow(
			"Battle city",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		std::cout << "Can't create window: " << SDL_GetError() << std::endl;
		return false;
	}
//	SDL_WINDOW_FULLSCREEN — открывает окно в полноэкранном режиме, изменяет разрешение рабочего стола;
//	SDL_WINDOW_FULLSCREEN_DESKTOP — открывает окно в полноэкранном режиме с разрешение данного рабочего стола;
//	SDL_WINDOW_OPENGL — окно с поддержкой OpenGL;
//	SDL_WINDOW_HIDDEN — окно скрыто;
//	SDL_WINDOW_BORDERLESS — окно без рамки;
//	SDL_WINDOW_RESIZABLE — можно изменять размер окна;
//	SDL_WINDOW_MINIMIZED — окно свернуто;
//	SDL_WINDOW_MAXIMIZED — окно развернуто;

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

//	//Total number of frames of the animation
//	int totalFrames = 8;
//
//	//Amount of delay in milliseconds for each frame
//	int delayPerFrame = 100;
//
//	//SDL_GetTicks() method gives us the time in milliseconds
//
//	//'frame' will give us the index of frame we want to render
//	//For example, if 'frame' is 2, it will give us the third frame
//	int frame = (SDL_GetTicks() / delayPerFrame) % totalFrames;

	ObjectsManager objectsManager;
	Battlefield    bf(window);
	Events         e(window, bf);
	Logics logics;
	Render render;
	Tank P1(objectsManager, objectsManager, e, window, renderer, &logics, &render, bf, TANK_E);
	Tank P2(objectsManager, objectsManager, e, window, renderer, &logics, &render, bf, TANK_P2);
	logics.addObject(static_cast<IMovableObject *>(&P1));
	logics.addObject(&P2);
	render.addObject(&P1);
	render.addObject(&P2);
	bf.shapedObjects.push_back(static_cast<IShape*>(&P1));
	bf.shapedObjects.push_back(static_cast<IShape*>(&P2));



	P1.rect.x = 300.f;
	P1.rect.y = 300.f;
	P1.image.rect.x = 300.f;
	P1.image.rect.y = 300.f;
	// game loop
//	while (window.isOpen())

	Uint32 a, b, delta;

	const double frame_limit = 60.0;
	while (e.isMainLoopActive)
	{
		a = SDL_GetTicks();
		delta = a - b;


		if (delta > 1000.0 / frame_limit)
		{
//			SDL_Log("fps:  %f", 1000.0 / delta);
			b = a;

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);

			e.EventHandler();

			logics.moveAll();
			render.drawAll();
			//Copying the texture on to the window using
			//renderer, texture rectangle and window rectangle
			//	SDL_RenderCopy(renderer, spriteSheet, &textureRect, &windowRect);
			SDL_RenderPresent(renderer);
		}
	}

	return 0;
}
