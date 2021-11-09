//
// Created by d.romanichenko on 17-Aug-21.
//

#ifndef ISHAPE_HPP
#define ISHAPE_HPP

#include <SDL2/SDL.h>

class IShape
{
public:
	[[nodiscard]] virtual SDL_FRect getRect() const = 0;
};

#endif //ISHAPE_HPP
