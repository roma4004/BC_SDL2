//
// Created by d.romanichenko on 13-Jul-21.
//

#ifndef IDRAWABLE_HPP
#define IDRAWABLE_HPP

class IDrawable
{
public:
//	virtual ~IDrawable() = 0;

	virtual void draw() const = 0;
	virtual void addObject(IDrawable* newObject) = 0;
};

#endif //IDRAWABLE_HPP
