//
// Created by d.romanichenko on 12-Jul-21.
//

#ifndef IDESTRUCTIBLEOBJECT_HPP
#define IDESTRUCTIBLEOBJECT_HPP

class IDestructibleObject
{
public:

	[[nodiscard]] virtual bool isPassObsticle() const = 0;
	[[nodiscard]] virtual bool isDestructible() const = 0;

};

#endif //IDESTRUCTIBLEOBJECT_HPP
