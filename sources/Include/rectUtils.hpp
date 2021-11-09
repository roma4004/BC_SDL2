//
// Created by d.romanichenko on 21-Aug-21.
//

#ifndef RECTUTILS_HPP
#define RECTUTILS_HPP

#include <SDL2/SDL.h>

[[nodiscard]] static inline SDL_Rect getRectFromFRect(const SDL_FRect& r)
{
	return SDL_Rect {
		static_cast<int>(r.x),
		static_cast<int>(r.y),
		static_cast<int>(r.w),
		static_cast<int>(r.h) };
}

[[nodiscard]] static inline SDL_FRect getFRectFromRect(const SDL_Rect& r)
{
	return SDL_FRect {
		static_cast<float>(r.x),
		static_cast<float>(r.y),
		static_cast<float>(r.w),
		static_cast<float>(r.h) };
}

#endif //RECTUTILS_HPP
