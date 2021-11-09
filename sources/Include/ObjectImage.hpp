//
// Created by d.romanichenko on 10-Jul-21.
//

#ifndef OBJECTIMAGE_HPP
#define OBJECTIMAGE_HPP

#include <string>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <EnumDirectionType.hpp>
#include <EnumObjectType.hpp>
#include <rectUtils.hpp>

class ObjectImage
{
public:
	ObjectImage(
			SDL_Window* Window,
			SDL_Renderer* Renderer,
			objectType ObjectTypeName,
			directionType ImageDirection = UP,
			int Scale = 1);

	~ObjectImage() { SDL_DestroyTexture(texture); };

	SDL_Window*			window;
	SDL_Renderer*		renderer;
	SDL_Texture*		texture;

	SDL_Rect			rect { 0 };
	SDL_Rect			viewport { 0 };
	const int			scale { 1 };

	SDL_Rect		textureRect { 0 };

	bool			visible { false };
	int				imgFrame { 0 };
	directionType	direction { UP };
	int				objectTypeName { TANK_P1 };

	//onVisibleChanged: if (!visible) explosion.play()
	//anchors{fill: parent; centerIn: parent}

	void draw() const
	{
		auto coord_rect = SDL_Rect {
			static_cast<int>(rect.x),
			static_cast<int>(rect.y),
			static_cast<int>(rect.w),
			static_cast<int>(rect.h) };//TODO: add scaling

		SDL_RenderCopy(renderer, texture, &viewport, &coord_rect);
		SDL_RenderPresent(renderer);
	};

	static SDL_Surface *load_surface(char const *path)
	{
		SDL_Surface *image_surface = IMG_Load(path);
		if(!image_surface)
		{
			std::cout << "Can't load: " << IMG_GetError() << std::endl;
			return nullptr;
		}

		return image_surface;
	}

	static SDL_Texture *textureFromSurface(SDL_Renderer* renderer, SDL_Surface* image)
	{
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
		if (texture == nullptr)
		{
			std::cout << "Can't convert: " << SDL_GetError() << std::endl;
			return nullptr;
		}

		return texture;
	}

	void UpdateDirection(directionType Direction);
	[[nodiscard]] SDL_Point GetSpriteOffsetBy() const;

	void move(const SDL_FPoint& moveDelta)
	{
		rect.x += static_cast<int>(moveDelta.x);
		rect.y += static_cast<int>(moveDelta.y);
	}

	//Image
	// {
		// id: image
		//anchors{fill: parent; centerIn: parent}
		//source: parent.sourceImg
		//visible: false
		//onVisibleChanged: if (!visible) explosion.play()
	//}
	[[nodiscard]] inline int getImgGridSize() const;

};

#endif //OBJECTIMAGE_HPP
