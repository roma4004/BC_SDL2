//
// Created by d.romanichenko on 12-Jul-21.
//

#ifndef HEALTHBAR_HPP
#define HEALTHBAR_HPP

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class HealthBar
{
public:
	//TODO: set rect
//	SDL_Rect rect;
	float barWidth;
private:
	std::string id = "healthBar";
	SDL_Color color = { .r = 0, .g = 0, .b = 0 };
//		color: (health > 80) ? "green"  :
//			   (health > 40) ? "yellow" : "red"
//		border.color: "black"
	float opacity;
	bool visible = false;//= parent->health < 100.f;
	//anchors.horizontalCenter: parent.horizontalCenter
};

#endif //HEALTHBAR_HPP
