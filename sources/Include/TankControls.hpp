//
// Created by d.romanichenko on 19-Jul-21.
//

#ifndef TANKCONTROLS_HPP
#define TANKCONTROLS_HPP

#include <Events.hpp>
#include <ObjectImage.hpp>

class TankControls
{
public:
	TankControls(Events& events, int ObjectName)
	{
		if (ObjectName == TANK_P1)
		{
			isPressedUp    = &events.isPressedUpP1,
			isPressedLeft  = &events.isPressedLeftP1,
			isPressedDown  = &events.isPressedDownP1,
			isPressedRight = &events.isPressedRightP1,
			isPressedFire  = &events.isPressedFireP1;
		}
		else if (ObjectName == TANK_P2)
		{
			isPressedUp    = &events.isPressedUpP2,
			isPressedLeft  = &events.isPressedLeftP2,
			isPressedDown  = &events.isPressedDownP2,
			isPressedRight = &events.isPressedRightP2,
			isPressedFire  = &events.isPressedFireP2;
		}
	};

	bool* isPressedUp    = nullptr;
	bool* isPressedLeft  = nullptr;
	bool* isPressedDown  = nullptr;
	bool* isPressedRight = nullptr;
	bool* isPressedFire  = nullptr;
};

#endif //TANKCONTROLS_HPP
