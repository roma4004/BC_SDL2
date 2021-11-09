//
// Created by d.romanichenko on 20-Aug-21.
//

#ifndef LOGICS_HPP
#define LOGICS_HPP

#include <vector>

#include <IMovableObject.hpp>

class Logics
{
	std::vector<IMovableObject*> movableObjects {};
public:
//	~Logics()
//	{
//		//delete every movable object (tanks, bricks and bullets)
//		for (auto& obj : movableObjects)
//		{
//			delete obj;
//		}
//	};

	void addObject(IMovableObject* newObject)
	{
		movableObjects.push_back(newObject);
	}

	void moveAll()
	{
		//move every movable object (tanks and bullets)
		for (auto& obj : movableObjects)
		{
			obj->move();
		}
	}
};

#endif //LOGICS_HPP
