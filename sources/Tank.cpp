//
// Created by d.romanichenko on 10-Jul-21.
//

//#include <random>

#include <Tank.hpp>
#include <Events.hpp>
#include <Timer.hpp>
//#include <Bullet.hpp>
#include <rectUtils.hpp>

void Tank::ToggleScaleTankBonusAct(bool isActive)
{
	const float bulletMinDamageDefault = 10.f;
	const float bulletMaxDamageDefault = 50.f;
	bulletMinDamage = bulletMinDamageDefault * ((isTankBonusAct) ? 1.5f : 1.f);
	bulletMaxDamage = bulletMaxDamageDefault * ((isTankBonusAct) ? 1.5f : 1.f);
}

bool Tank::getIsTankBonusAct() const { return isTankBonusAct; }
void Tank::setIsTankBonusAct(bool newValue)
{
	isTankBonusAct = newValue;
	onIsTankBonusActChanged();
}

void Tank::onIsTankBonusActChanged()
{
	float tankScale = isTankBonusAct ? 1.5f : 1.f;
	health = isTankBonusAct
		? health * tankScale
		: health / tankScale;
}

void Tank::onHealthChange()
{
	if (health < 1.f)
	{
		//image.visible = false;
		isNeedExplode = true;
	}
}

bool Tank::isCanMove() const
{
	return isCanMove(direction);
}

/// \brief logics::isCanMove - check whether the path is free, before move;
/// \param newDirection - posible move newDirection
/// \return      - true - way clear; false - movement blocked
bool Tank::isCanMove(directionType newDirection) const
{
	if (newDirection == NONE)
		newDirection = direction;

	const SDL_FPoint moveUp    { 0.f, -speed };
	const SDL_FPoint moveLeft  { -speed, 0.f };
	const SDL_FPoint moveDown  { 0.f, speed };
	const SDL_FPoint moveRight { speed, 0.f };

	SDL_FPoint delta;
	switch (newDirection)
	{
		case NONE: break;
		case UP: 	delta = moveUp;    break;
		case LEFT:	delta = moveLeft;  break;
		case DOWN:	delta = moveDown;  break;
		case RIGHT:	delta = moveRight; break;
	}

	float	x = rect.x + delta.x;
	float	y = rect.y + delta.y;
	auto	w = rect.w;
	auto	h = rect.h;

	int		width;
	int		height;
	SDL_GetWindowSize(window, &width, &height);
	auto	maxWidth  = static_cast<float>(width);
	auto	maxHeight = static_cast<float>(height);

	// check window edges
	switch (newDirection)
	{
		case NONE: break;
		case UP: 	if (y     < 0        ) return false; break;
		case LEFT:	if (x     < 0        ) return false; break;
		case DOWN:	if (y + h > maxHeight) return false; break;
		case RIGHT:	if (x + w > maxWidth ) return false; break;
	}

	//TODO: check std::all_of() loop
	if (!isTankBonusAct)
		for (const IShape* object : bf.shapedObjects)
		{
			//self skip
			if (object == static_cast<const IShape*>(this))
				continue;

			//init possible intersected rectangle
			auto thisGB = getRectFromFRect(        getRect());
			auto objGB  = getRectFromFRect(object->getRect());

			// delta to check next move step
			thisGB.x += static_cast<int>(delta.x);
			thisGB.y += static_cast<int>(delta.y);

			return !SDL_HasIntersection(&thisGB, &objGB);
		}

	return true;
}

inline void Tank::debug_print_pos() const
{
	SDL_Log("debug_print_pos(): position() x: %f position() y: %f.", rect.x, rect.y);
	SDL_Log("debug_print_pos(): image.position() x: %d image.position() y: %d.", image.rect.x, image.rect.y);
}

void Tank::setRamdomDirectionAI()
{
	directionType newDir;
	newDir = getRamdomDirectionAI();
	if (newDir != NONE)
		image.UpdateDirection(newDir);
}

/// \brief       get random in range from min to max inclusive
/// \param min - minimum random value inclusive
/// \param min - maximum random value inclusive
/// \return    - random int
int Tank::getRandomDistribution(int min, int max)
{
	std::uniform_int_distribution<> distribution(min, max); // Равномерное распределение [min, max]

	return distribution(generator);
}

/// \brief  get random from clear ways sides
/// \return  - random sides for surceased moving
directionType Tank::getRamdomDirectionAI()
{
	std::vector<directionType> variants;

	//generating variants
	if (isCanMove(UP))
	{
		variants.push_back(UP);
		variants.push_back(UP);
		variants.push_back(UP);
		variants.push_back(UP);
	}
	if (isCanMove(DOWN))
	{
		variants.push_back(DOWN);
		variants.push_back(DOWN);
		variants.push_back(DOWN);
		variants.push_back(DOWN);
	}
	if (isCanMove(LEFT))
	{
		variants.push_back(LEFT);
		variants.push_back(LEFT);
		variants.push_back(LEFT);
		variants.push_back(LEFT);
	}
	if (isCanMove(RIGHT))
	{
		variants.push_back(RIGHT);
		variants.push_back(RIGHT);
		variants.push_back(RIGHT);
		variants.push_back(RIGHT);
	}

	if (variants.empty())
		return NONE;

	std::shuffle(variants.begin(), variants.end(), generator);

	const int min = 0;
	const auto max = static_cast<int>(variants.size() - 1);
	const auto randomIndex =
			static_cast<unsigned int>(getRandomDistribution(min, max));

	//chose random side from clear way variants only
	return variants[randomIndex];
//	return variants[0];
}

void Tank::fire()
{
	if (isCanShootReload)
	{
		isCanShootReload = false;
		startReloadTimer();
		shootDelegate.shoot(
			SDL_Point {
				static_cast<int>(rect.x),
				static_cast<int>(rect.y) },
			direction);
//		auto* bullet = new Bullet(events, window, renderer, logics, render, bf, *this);
//		//TODO: refactor to common method process with internal draw and move for unified processing for all objects in one collection
//		addObject(static_cast<IMovableObject*>(bullet));
//		addObject(static_cast<IDrawable*>(bullet));
//		bf.shapedObjects.push_back(bullet);
	}
}

bool Tank::moveAI()
{
	// move if way is clear (except for tank bonus)
	bool isMove = isCanMove(direction);

	//new dirrection if way is not clear
	bool isControlledByAI = image.objectTypeName == TANK_E;
	if (!isMove && isControlledByAI)
	{
		direction = getRamdomDirectionAI();
		if (direction == NONE)
			return false;

		isMove = true;
		//SDL_Log("newDirection %d", newDirection);
	}

	const SDL_FPoint moveUp    { 0.f, -speed };
	const SDL_FPoint moveLeft  { -speed, 0.f };
	const SDL_FPoint moveDown  { 0.f, speed  };
	const SDL_FPoint moveRight { speed , 0.f };
	switch (direction)
	{
		case NONE: break;
		case UP:	if (isMove)	moveRect(moveUp);		break;
		case DOWN:	if (isMove)	moveRect(moveDown);		break;
		case LEFT:	if (isMove)	moveRect(moveLeft);		break;
		case RIGHT:	if (isMove)	moveRect(moveRight);	break;
	}

	//call every frame to animate tank trucks when its moving
	image.UpdateDirection(direction);

	if (isMove)
		return true;

	return false;
}

bool Tank::moveForward()
{
	return moveForward(direction);
}

bool Tank::moveForward(directionType newDirection)
{
	if (newDirection != NONE)
		direction = newDirection;

	// move if way is clear (except for tank bonus)
	bool isMove = isCanMove(direction);

	const SDL_FPoint moveUp    { 0.f, -speed };
	const SDL_FPoint moveLeft  { -speed, 0.f };
	const SDL_FPoint moveDown  { 0.f, speed  };
	const SDL_FPoint moveRight { speed , 0.f };
	switch (direction)
	{
	case NONE: break;
	case UP:	if (isMove)	moveRect(moveUp);		break;
	case DOWN:	if (isMove)	moveRect(moveDown);		break;
	case LEFT:	if (isMove)	moveRect(moveLeft);		break;
	case RIGHT:	if (isMove)	moveRect(moveRight);	break;
	}

	//call every frame to animate tank trucks when its moving
	image.UpdateDirection(direction);

	if (isMove)
		return true;

	return false;
}

void Tank::moveRect(const SDL_FPoint& moveDelta)
{
	rect.x += moveDelta.x;
	rect.y += moveDelta.y;

	//update image
	SDL_Rect newImageRect = getRectFromFRect(rect);
	image.rect = newImageRect;
}
void Tank::move()
{
	if (bool isControlledByAI = image.objectTypeName == TANK_E)
	{
		moveAI();
		return;
	}

	if		(*control.isPressedUp)		moveForward(UP);
	else if (*control.isPressedDown)	moveForward(DOWN);
	else if (*control.isPressedLeft)	moveForward(LEFT);
	else if (*control.isPressedRight)	moveForward(RIGHT);
	else if (*control.isPressedFire)	fire();
}

void Tank::startTimer(
		int timerType,
		const std::function<int()>& callback,
		int intervalMs,
		bool IsRepeatable)
{
	timers[timerType] = new Timer(
		true,
		IsRepeatable,
		std::chrono::milliseconds(intervalMs),
		callback);
}

void Tank::startRandomDirectionTimer()
{
	startTimer(
			RANDOM_DIRECTION,
			[&](){ setRamdomDirectionAI(); return 0; },
			randomDirectionalInterval,
			true);
}

void Tank::stopRandomDirectionTimer()
{
	auto stopIt = timers.find(RANDOM_DIRECTION);
	if (stopIt != timers.end())
	{
		delete stopIt->second;
		timers.erase(stopIt);
	}
}

void Tank::toggleIsCanShootReload()
{
	this->isCanShootReload = !this->isCanShootReload;
}

void Tank::startReloadTimer()
{
//	SDL_Log("reload start");
	startTimer(
		RELOAD,
		[&](){ toggleIsCanShootReload(); return 0; },
		reloadInterval,
		false);
}

void Tank::stopReloadTimer()
{
	auto stopIt = timers.find(RELOAD);
	if (stopIt != timers.end())
	{
		delete stopIt->second;
		timers.erase(stopIt);
	}
}

//const std::atomic<bool> &Tank::getIsHelmetBonusAct() const
//{
//	return isHelmetBonusAct;
//}

//void Tank::setIsHelmetBonusAct(const std::atomic<bool> &isHelmetBonusAct)
//{
//	isHelmetBonusAct = isHelmetBonusAct;
////	Timer (
////			[&isHelmetBonusAct](){ isHelmetBonusAct = false },
////			helmetInterval);
//}
