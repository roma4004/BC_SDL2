//
// Created by d.romanichenko on 22-Jul-21.
//

#include <Tank.hpp>
#include <Bullet.hpp>
#include <iostream>

#include <SDL.h>
#include <SDL_video.h>

#include <IShape.hpp>
#include <rectUtils.hpp>

void Bullet::PlaceInFrontOfTank()
{
	const SDL_FRect& tank   = parent.rect;
	const SDL_FRect& bullet =        rect;

	const SDL_FPoint tankCenter   { tank.w   / 2.0f, tank.h   / 2.0f };
	const SDL_FPoint bulletCenter { bullet.w / 2.0f, bullet.h / 2.0f };

	const SDL_FPoint tankUpOffset    { tank.x + tankCenter.x, tank.y                };
	const SDL_FPoint tankLeftOffset  { tank.x               , tank.y + tankCenter.y };
	const SDL_FPoint tankDownOffset  { tank.x + tankCenter.x, tank.y + tank.h       };
	const SDL_FPoint tankRightOffset { tank.x + tank.w      , tank.y + tankCenter.y };

	const SDL_FPoint bulletUpOffset    { bullet.x + bulletCenter.x, bullet.y };
	const SDL_FPoint bulletLeftOffset  { bullet.x                 , bullet.y + bulletCenter.y };
	const SDL_FPoint bulletDownOffset  { bullet.x + bulletCenter.x, bullet.y + bullet.h       };
	const SDL_FPoint bulletRightOffset { bullet.x + bullet.w      , bullet.y + bulletCenter.y };

	const SDL_FPoint moveUp    { tankUpOffset.x    - bulletUpOffset.x           , tankUpOffset.y    - bulletUpOffset.y    - speed };
	const SDL_FPoint moveLeft  { tankLeftOffset.x  - bulletLeftOffset.x  - speed, tankLeftOffset.y  - bulletLeftOffset.y          };
	const SDL_FPoint moveDown  { tankDownOffset.x  - bulletDownOffset.x         , tankDownOffset.y  - bulletDownOffset.y  + speed };
	const SDL_FPoint moveRight { tankRightOffset.x - bulletRightOffset.x + speed, tankRightOffset.y - bulletRightOffset.y         };

	switch (direction)
	{
		case NONE: break;
		case UP:	moveRect(moveUp);	break;
		case LEFT:	moveRect(moveLeft);	break;
		case DOWN:	moveRect(moveDown);	break;
		case RIGHT:	moveRect(moveRight);break;
	}
}

bool Bullet::isCanMove() const
{
	return isCanMove(image.direction);
}
///
/// \brief isCanMove - check whether the path is free, before move;
/// \param delta - direction * speed vector
/// \return      - true - way clear; false - movement blocked
///
bool Bullet::isCanMove(directionType newDirection) const
{
	if (newDirection == NONE)
		newDirection = direction;

	const SDL_FPoint moveUp    { 0.f, -speed };
	const SDL_FPoint moveLeft  { -speed, 0.f };
	const SDL_FPoint moveDown  { 0.f, speed  };
	const SDL_FPoint moveRight { speed, 0.f  };

	SDL_FPoint delta;
	switch (newDirection)
	{
		case NONE: break;
		case UP: 	delta = moveUp;    break;
		case LEFT:	delta = moveLeft;  break;
		case DOWN:	delta = moveDown;  break;
		case RIGHT:	delta = moveRight; break;
	}

	float x = rect.x + delta.x;
	float y = rect.y + delta.y;
	auto  w = rect.w;
	auto  h = rect.h;
	int width;
	int height;
	SDL_GetWindowSize(window, &width, &height);
	auto maxWidth  = static_cast<float>(width);
	auto maxHeight = static_cast<float>(height);
	// check window edges
	switch (direction)
	{
		case NONE: break;
		case UP: 	if (y     < 0        ) return false; break;
		case LEFT:	if (x     < 0        ) return false; break;
		case DOWN:	if (y + h > maxHeight) return false; break;
		case RIGHT:	if (x + w > maxWidth ) return false; break;
	}

	//TODO: check std::all_of() loop
	// move intersect to destruct obj
	for (const IShape* object : bf.shapedObjects)
	{
		//self skip
		if (object == static_cast<const IShape*>(this))
			continue;

		auto thisGB = getRectFromFRect(        getRect());
		auto objGB  = getRectFromFRect(object->getRect());

		// delta to check next move step
		thisGB.x += static_cast<int>(delta.x);
		thisGB.y += static_cast<int>(delta.y);

		return !SDL_HasIntersection(&thisGB, &objGB);
	}

	return true;
}

bool Bullet::moveForward()
{
	return moveForward(direction);
}

bool Bullet::moveForward(directionType newDirection)
{
	if (newDirection != NONE)
		direction = newDirection;

	const SDL_FPoint moveUp    { 0.f, -speed };
	const SDL_FPoint moveLeft  { -speed, 0.f };
	const SDL_FPoint moveDown  { 0.f, speed };
	const SDL_FPoint moveRight { speed, 0.f };

	// move if way is clear (except for tank bonus)
	bool isMove = isCanMove();
	switch (direction)
	{
		case NONE:	break;
		case UP:	if (isMove)	moveRect(moveUp);		break;
		case DOWN:	if (isMove)	moveRect(moveDown);		break;
		case LEFT:	if (isMove)	moveRect(moveLeft);		break;
		case RIGHT:	if (isMove)	moveRect(moveRight);	break;
	}

	//call every frame to animate tank trucks when its moving
	image.UpdateDirection(direction);

	if (isMove)
		return true;

	//run explosion with accept damage
	return false;
}

void Bullet::moveRect(const SDL_FPoint& moveDelta)
{
	rect.x += moveDelta.x;
	rect.y += moveDelta.y;

	//update image
	SDL_Rect newImageRect = getRectFromFRect(rect);
	image.rect = newImageRect;
}

void Bullet::move()
{
	//std::cout << "bullet moves" << image.sprite.getGlobalBounds().left << " "
	//							 << image.sprite.getGlobalBounds().left << std::endl;
	moveForward();
}
