//
// Created by d.romanichenko on 19-Jul-21.
//

#ifndef IMOVABLEOBJECT_HPP
#define IMOVABLEOBJECT_HPP

#include <SDL2/SDL.h>
#include <EnumDirectionType.hpp>

class IMovableObject
{
public:
	virtual void move() = 0;
	virtual void moveRect(const SDL_FPoint& moveDelta) = 0;
	virtual bool moveForward(directionType newDirection) = 0;
	virtual bool moveForward() = 0;
	[[nodiscard]] virtual bool isCanMove(directionType newDirection) const = 0;
	[[nodiscard]] virtual bool isCanMove() const = 0;
	virtual void addObject(IMovableObject* newObject) = 0;
};

#endif //IMOVABLEOBJECT_HPP
