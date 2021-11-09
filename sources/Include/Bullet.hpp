//
// Created by d.romanichenko on 22-Jul-21.
//

#ifndef BULLET_HPP
#define BULLET_HPP

#include <iostream>

#include <IDestructibleObject.hpp>
#include <IMovableObject.hpp>
#include <IDrawable.hpp>
#include <IShape.hpp>

#include <EnumDirectionType.hpp>
#include <EnumObjectType.hpp>

#include <Events.hpp>
#include <Logics.hpp>
#include <Render.hpp>
#include <Tank.hpp>
#include <ObjectImage.hpp>
#include "Tank.hpp"

class Bullet : public IDestructibleObject, public IMovableObject, public IDrawable, public IShape
{
public:
	Bullet(
		Events& Events,
		SDL_Window* Window,
		SDL_Renderer* Renderer,
		Logics* Logics,
		Render* Render,
		Battlefield& Bf,
		const Tank& Parent)
	:
		parent(Parent),
		image(Window, Renderer, BULLET, Parent.image.direction),
		health(1.f),
		events(Events),
		window(Window),
		renderer(Renderer),
		logics(Logics),
		render(Render),
		bf(Bf),
		direction(Parent.image.direction),
		speed(Parent.bulletSpeed),
		minDamage(Parent.bulletMinDamage),
		maxDamage(Parent.bulletMaxDamage),
		isTankBonusAct(Parent.isTankBonusAct)
	{
		auto newRect = getFRectFromRect(image.rect);
		rect = newRect;

		PlaceInFrontOfTank();		//get width and height of object

	}
//	~Bullet() { };

	Events&				events;
	SDL_Window*			window;
	SDL_Renderer*		renderer;
	Logics*				logics;
	Render*				render;
	Battlefield&		bf;

	const Tank& parent;

	//image prop
	ObjectImage image;
	directionType		direction { UP };
	objectType			objectTypeName { BULLET };

	float health;
	float speed;
	float minDamage;
	float maxDamage;
	bool  isTankBonusAct;
	SDL_FRect rect {};

	void PlaceInFrontOfTank();

	//IDestructibleObject
	[[nodiscard]] bool isPassObsticle() const						override { return false; };
	[[nodiscard]] bool isDestructible() const						override { return true; };

	//IMovableObject
	void move()														override;
	void moveRect(const SDL_FPoint& moveDelta)						override;
	bool moveForward(directionType newDirection)					override;
	bool moveForward()												override;
	[[nodiscard]] bool isCanMove() const							override;
	[[nodiscard]] bool isCanMove(directionType newDirection) const	override;
	void addObject(IMovableObject* newObject)						override { logics->addObject(newObject); };

	//IDrawable
	void draw() const												override { image.draw(); }
	void addObject(IDrawable* newObject)							override { render->addObject(newObject); };

	//IShape
	[[nodiscard]] SDL_FRect getRect() const							override { return rect; };


	bool isNeedExplode { false };

//	AnimatedSprite
//	{
//		anchors.centerIn: parent
//		width: 32
//		height: 32
//		source: "qrc:/img/spriteExpl5.png"
//		frameCount: 5
//		frameWidth: 32
//		frameHeight: 32
//		frameDuration: 500/frameCount
//		visible: running
//		running: isNeedExplode
//	}
};

#endif //BULLET_HPP
