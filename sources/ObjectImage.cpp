//
// Created by d.romanichenko on 10-Jul-21.
//

#include <iostream>

#include "ObjectImage.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <ObjectsManager.hpp>

ObjectImage::ObjectImage(
		SDL_Window* Window,
		SDL_Renderer* Renderer,
		objectType ObjectTypeName,
		directionType ImageDirection,
		int Scale)
	:
		window(Window),
		renderer(Renderer),
		objectTypeName(ObjectTypeName),
		direction(ImageDirection),
		scale(Scale)
{
	SDL_Surface* img = load_surface(R"(..\Images\battleCitySprites.png)");
	texture = SDL_CreateTextureFromSurface(renderer, img);
	SDL_FreeSurface(img);

	rect.w = getImgGridSize() * scale; //Ширина полотна
	rect.h = getImgGridSize() * scale; //Высота полотна

	//gets the width and height of the texture
	SDL_QueryTexture(
		texture,
		nullptr,
		nullptr,
		&textureRect.w,
		&textureRect.h);

	UpdateDirection(direction);
}

inline int ObjectImage::getImgGridSize() const
{
	switch (objectTypeName)
	{
		case BULLET:
			return 8;
		default:
			return 16;
	}
}

SDL_Point ObjectImage::GetSpriteOffsetBy() const
{
	const int directionAmount   = 4;
//	const int frameAmount       = 2;
	const int directionGridSize = 32;
	const int bulletGridSize    = 8;

	int imageGridSize           = getImgGridSize();
	const int directionFrame    = direction * directionGridSize;
	const int currentFrame      = imgFrame  *     imageGridSize;

	SDL_Point frameOffset;
	switch (objectTypeName)
	{
	case TANK_P1:
		return SDL_Point { directionFrame + currentFrame, 0 };
	case TANK_P2:
		return SDL_Point { directionFrame + currentFrame,
							directionGridSize * directionAmount };
	case TANK_E:
		return SDL_Point { directionAmount * directionGridSize
							+ directionFrame + currentFrame,
							0 };
	case BULLET: // TODO: Fix bulletGridSize and view port
		if (direction == UP || direction == DOWN)
			return SDL_Point { 10 * directionGridSize
									 + direction * bulletGridSize + 3,
									 12 * imageGridSize + 6 };
		else //if (direction == directionType::LEFT || direction == directionType::RIGHT)
			return SDL_Point { 10 * directionGridSize
									 + direction * bulletGridSize + 2,
									 12 * imageGridSize + 6 };
//		case ObjectImage::BRICK:				break;
//		case ObjectImage::BRICK_WHITE:			break;
	}

//	SDL_Log("image.position() x: %i position() y: %i."
//			,frameOffset.x
//			,frameOffset.y);
	return SDL_Point { };
}

void ObjectImage::UpdateDirection(directionType newDirection)
{
	direction = newDirection;
	imgFrame = imgFrame ? 0 : 1;

	SDL_Point gridSize;
	switch (objectTypeName)
	{
	case BULLET:
		if (direction == UP || direction == DOWN)
			gridSize = SDL_Point { 3, 4 };
		else //if (direction == LEFT || direction == RIGHT)
			gridSize = SDL_Point { 4, 3 };
		break;
	default:
		gridSize = SDL_Point { 16, 16 };
		break;
	}

	const auto offset = GetSpriteOffsetBy();
	viewport = SDL_Rect { offset.x, offset.y, gridSize.x, gridSize.y };
//
//	SDL_Log("image.position() x: %i position() y: %i. image.size() x: %i size() y: %i. "
//	,offset.x
//	,offset.y
//	,gridSize.x
//	,gridSize.y);
}
