//
// Created by d.romanichenko on 20-Aug-21.
//

#ifndef PLAYER_HPP
#define PLAYER_HPP

//#include <Tank.hpp>
//
//class Player
//	:
//		public IDestructibleObject,
//		public IMovableObject,
//		public IDrawable,
//		public IShape
//{
//public:
//	Player(
//		Events& Events,
//		SDL_Window* Window,
//		SDL_Renderer* Renderer,
//		Logics* Logics,
//		Render* Render,
//		Battlefield& Bf,
//		objectType ObjectTypeName,
//		directionType ImageDirection = UP)
//	:
//		events(Events),
//		window(Window),
//		renderer(Renderer),
//		logics(Logics),
//		render(Render),
//		bf(Bf),
//		control(Events, ObjectTypeName),
//		tank(Events, Window, Renderer, Logics, Render, Bf, ObjectTypeName)
//	{
//
//	};
//
//	Tank tank;
//
//	Events&				events;
//	SDL_Window*			window;
//	SDL_Renderer*		renderer;
//	Logics*				logics;
//	Render*				render;
//	Battlefield&		bf;
//	TankControls		control;
//
//	//	const std::atomic<bool>& getIsHelmetBonusAct() const;
//	//	void setIsHelmetBonusAct(const std::atomic<bool>& isHelmetBonusAct);
//
//	//IDestructibleObject
//	[[nodiscard]] bool isPassObsticle() const						override { return false; };
//	[[nodiscard]] bool isDestructible() const						override { return true; };
//
//	//IMovableObject
//	void move()														override;
//	void moveRect(const SDL_FPoint& moveDelta)						override { tank.moveRect(moveDelta); };
//	bool moveForward(directionType direction)						override { return tank.moveForward(direction); };
//	bool moveForward()												override { return tank.moveForward(); };
//	[[nodiscard]] bool isCanMove(directionType direction) const		override { return tank.isCanMove(direction); };
//	[[nodiscard]] bool isCanMove() const							override { return tank.isCanMove(); };
//	void addObject(IMovableObject* newObject)						override { logics->addObject(newObject); };
//
//	//IDrawable
//	void draw() const												override { tank.draw(); }
//	void addObject(IDrawable* newObject)							override { render->addObject(newObject); };
//
//	//IShape
//	[[nodiscard]] SDL_FRect getRect() const							override { return tank.rect; };
//
//};

#endif //PLAYER_HPP
