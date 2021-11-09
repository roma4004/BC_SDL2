//
// Created by d.romanichenko on 23-Aug-21.
//

#ifndef ISHOOTABLE_HPP
#define ISHOOTABLE_HPP

#include <EnumDirectionType.hpp>
#include <SDL2/SDL.h>

class IShootable
{
public:
	inline virtual bool shoot(SDL_Point spawnPosition, directionType direction) = 0;
};

#endif //ISHOOTABLE_HPP
