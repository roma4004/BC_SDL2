//
// Created by d.romanichenko on 20-Aug-21.
//

#ifndef RENDER_HPP
#define RENDER_HPP

#include <vector>

#include <IDrawable.hpp>

class Render
{
	std::vector<IDrawable* > drawableObjects {};
public:
//	~Render()
//	{
//		//delete every drawable object (tanks, bricks and bullets)
//		for (auto& obj : drawableObjects)
//		{
//			delete obj;
//		}
//	};

	void addObject(IDrawable* newObject)
	{
		drawableObjects.push_back(newObject);
	}

	void drawAll()
	{
		//draw every drawable object (tanks, bricks and bullets)
		for (auto& obj : drawableObjects)
		{
			obj->draw();
		}
	}
};

#endif //RENDER_HPP
