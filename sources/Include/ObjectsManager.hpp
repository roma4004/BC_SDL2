//
// Created by d.romanichenko on 22-Aug-21.
//

#ifndef OBJECTSMANAGER_HPP
#define OBJECTSMANAGER_HPP

#include <vector>
#include <utility>
//#include <cstddef>

#include <SDL2/SDL.h>

#include <EnumObjectType.hpp>

#include "IShootable.hpp"

//#include <Tank.hpp>
//#include <Bullet.hpp>

class ObjectsManager
	:
		public IShootable
{

public:
	using type = objectType;
	using element = std::pair<
						SDL_FRect,
						std::pair<SDL_Texture*, SDL_Rect>>;

	std::vector<element> bullest {};
	std::vector<element> tanks   {};

	std::size_t buletsIndex { 0 };
	std::size_t tanksIndex { 0 };

	auto newIndex(type selector)
	{
		switch (selector)
		{
			case TANK_P1: [[fallthrough]];
			case TANK_P2: [[fallthrough]];
			case TANK_E: return tanksIndex++;
			case BULLET: return buletsIndex++;
//			case BRICK: break;
//			case BRICK_WHITE: break;
		}
	}

//	auto getIndex(type selector)
//	{
//		switch (selector)
//		{
//			case tank:   return tanksIndex;
//			case bullet: return buletsIndex;
//		}
//	}

[[nodiscard]] SDL_FRect*	getLogicRect(const type selector, std::size_t index)
	{
		switch (selector)
		{
			case TANK_P1: [[fallthrough]];
			case TANK_P2: [[fallthrough]];
			case TANK_E: return   &tanks[index].first;
			case BULLET: return &bullest[index].first;
//			case BRICK: break;
//			case BRICK_WHITE: break;
		}
//		return SDL_FRect {};
	};

	[[nodiscard]] SDL_Texture*	getTexture(const type selector, std::size_t index)
	{
		switch (selector)
		{
			case TANK_P1: [[fallthrough]];
			case TANK_P2: [[fallthrough]];
			case TANK_E: return   tanks[index].second.first;
			case BULLET: return bullest[index].second.first;
//			case BRICK: break;
//			case BRICK_WHITE: break;
		}
	};

	[[nodiscard]] SDL_Rect		getTextureRect(const type selector, std::size_t index)
	{
		switch (selector)
		{
			case TANK_P1: [[fallthrough]];
			case TANK_P2: [[fallthrough]];
			case TANK_E: return   tanks[index].second.second;
			case BULLET: return bullest[index].second.second;
//			case BRICK: break;
//			case BRICK_WHITE: break;
		}
	};


	void setLogicRect(const type selector, std::size_t index, SDL_FRect value)
	{
		switch (selector)
		{
			case TANK_P1: [[fallthrough]];
			case TANK_P2: [[fallthrough]];
			case TANK_E:   tanks[index].first = value; break;
			case BULLET: bullest[index].first = value; break;
//			case BRICK: break;
//			case BRICK_WHITE: break;
		}
	};
	void setTexture(const type selector, std::size_t index, SDL_Texture* value)
	{
		switch (selector)
		{
			case TANK_P1: [[fallthrough]];
			case TANK_P2: [[fallthrough]];
			case TANK_E:   tanks[index].second.first = value; break;
			case BULLET: bullest[index].second.first = value; break;
//			case BRICK: break;
//			case BRICK_WHITE: break;
		}
	};
	void setTextureRect(const type selector, std::size_t index, SDL_Rect value)
	{
		switch (selector)
		{
			case TANK_P1: [[fallthrough]];
			case TANK_P2: [[fallthrough]];
			case TANK_E:   tanks[index].second.second = value; break;
			case BULLET: bullest[index].second.second = value; break;
//			case BRICK: break;
//			case BRICK_WHITE: break;
		}
	};

	auto add(const type selector, element value)
	{
		switch (selector)
		{
			case TANK_P1: [[fallthrough]];
			case TANK_P2: [[fallthrough]];
			case TANK_E:   tanks.push_back(value); break;
			case BULLET: bullest.push_back(value); break;
//			case BRICK: break;
//			case BRICK_WHITE: break;
		}

		return newIndex(selector);
	};

	auto add(const type selector)
	{
		switch (selector)
		{
			case TANK_P1: [[fallthrough]];
			case TANK_P2: [[fallthrough]];
			case TANK_E:   tanks.emplace_back(); break;
			case BULLET: bullest.emplace_back(); break;
//			case BRICK: break;
//			case BRICK_WHITE: break;
		}

		return newIndex(selector);
	};

	//IShootable
	inline bool shoot(SDL_Point spawnPosition, directionType direction) override
	{
		SDL_Log("fire start");
//		if (isCanShootReload)
//		{
//			isCanShootReload = false;
//			startReloadTimer();
			//		auto* bullet = new Bullet(events, window, renderer, logics, render, bf, *this);
			//		//TODO: refactor to common method process with internal draw and move for unified processing for all objects in one collection
			//		addObject(static_cast<IMovableObject*>(bullet));
			//		addObject(static_cast<IDrawable*>(bullet));
			//		bf.shapedObjects.push_back(bullet);
//		}
	return true;
	}
};

#endif //OBJECTSMANAGER_HPP
