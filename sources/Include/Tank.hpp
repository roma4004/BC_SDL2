//
// Created by d.romanichenko on 10-Jul-21.
//

#ifndef TANK_HPP
#define TANK_HPP

#include <map>
#include <string>
#include <functional>
#include <random>

#include <SDL2/SDL.h>

#include <IDestructibleObject.hpp>
#include <IShape.hpp>
#include <Events.hpp>
#include <TankControls.hpp>
#include <Timer.hpp>

#include <EnumDirectionType.hpp>
#include <EnumObjectType.hpp>
#include <Logics.hpp>
#include <Render.hpp>
#include <ObjectsManager.hpp>
#include <HealthBar.hpp>

class Tank :
		public IDestructibleObject,
		public IMovableObject,
		public IDrawable,
		public IShape
{
public:
	Tank(
		ObjectsManager& ObjectsManager,
		IShootable& reference,
		Events& Events,
		SDL_Window* Window,
		SDL_Renderer* Renderer,
		Logics* Logics,
		Render* Render,
		Battlefield& Bf,
		objectType ObjectTypeName,
		directionType ImageDirection = UP)
	:
		objectsManager(ObjectsManager),
		shootDelegate(std::ref(reference)),
		events(Events),
		window(Window),
		renderer(Renderer),
		logics(Logics),
		render(Render),
		bf(Bf),
		direction(ImageDirection),
		objectTypeName(ObjectTypeName),
		control(Events, ObjectTypeName),
		image(Window, Renderer, ObjectTypeName, ImageDirection, 4),
		generator(random_device())
	{
		//get width and height of object
		auto newRect = getFRectFromRect(image.rect);
		rect = newRect;

//		tankIndex = objectsManager->add(ObjectTypeName);
//		objectsManager->setLogicRect(ObjectTypeName, tankIndex, rect);
//		objectsManager->setTexture(		ObjectTypeName, tankIndex, image.texture);
//		objectsManager->setTextureRect(	ObjectTypeName, tankIndex, image.rect);

		if (ObjectTypeName == TANK_E)
			startRandomDirectionTimer();
	};

	~Tank()
	{
		//TODO: remove this useless map<int, Timer*>
		for (auto& timer : timers)
		{
			//stop all the timers
			auto stopIt =
				timers.find(RANDOM_DIRECTION);
			if (stopIt != timers.end())
			{
				delete stopIt->second;
				timers.erase(stopIt);
			}
		}
	}

	std::random_device	random_device;
	std::knuth_b		generator;

	IShootable& 		shootDelegate;
	ObjectsManager&		objectsManager;
	Events&				events;
	SDL_Window*			window;
	SDL_Renderer*		renderer;
	Logics*				logics;
	Render*				render;
	Battlefield&		bf;
	TankControls		control;

	HealthBar			healthBar;
//	std::size_t			tankIndex;

	//image prop
	ObjectImage			image;
	directionType		direction { UP };
	objectType			objectTypeName { TANK_P1 };

	SDL_FRect			rect {};
//	std::atomic<bool>	isHelmetBonusAct;
	const int			randomDirectionalInterval { 6000 }; //ms
	int					helmetInterval { 10000 }; //ms
	int					reloadInterval { 1000 }; //ms
	bool				isCanShootReload { true };
	float				health { 100.f };

	//tank prop
	bool				isNeedExplode { false };
	bool				spawnReady { false };
	bool				isTankBonusAct { false };
	float				speed { 3.f };

	float				bulletSpeed { 14 };
	float				bulletMinDamage { 10 };
	float				bulletMaxDamage { 50 };

	/*constexpr */std::map<int, Timer*> timers;
	enum timerType { RANDOM_DIRECTION, RELOAD };
	void startTimer(
		int timerType,
		const std::function<int()>& callback,
		int intervalMs,
		bool IsRepeatable);
	void startRandomDirectionTimer();
	void stopRandomDirectionTimer();
	void startReloadTimer();
	void stopReloadTimer();

	[[nodiscard]] bool getIsTankBonusAct() const;
	void setIsTankBonusAct(bool newValue);
	void ToggleScaleTankBonusAct(bool isActive);
	void onIsTankBonusActChanged();

	void debug_print_pos() const;

	[[nodiscard]] directionType getRamdomDirectionAI();
	int getRandomDistribution(int min, int max);
	void setRamdomDirectionAI();

	void fire();
	void onHealthChange();
	void toggleIsCanShootReload();

	bool moveAI();

	//IDestructibleObject
	[[nodiscard]] bool isPassObsticle() const						override { return false; };
	[[nodiscard]] bool isDestructible() const			override { return true; };

	//IMovableObject
	void move()														override;
	void moveRect(const SDL_FPoint& moveDelta)						override;
	bool moveForward(directionType newDirection)					override;
	bool moveForward()												override;
	[[nodiscard]] bool isCanMove(directionType newDirection) const	override;
	[[nodiscard]] bool isCanMove() const							override;
	void addObject(IMovableObject* newObject)						override { logics->addObject(newObject); };

	//IDrawable
	void draw() const												override { image.draw(); }
	void addObject(IDrawable* newObject)							override { render->addObject(newObject); };

	//IShape
	[[nodiscard]] SDL_FRect getRect() const							override { return rect; };

};

#endif //TANK_HPP



//AnimatedImage{
//	width:  parent.width  * 1.3
//	height: parent.height * 1.3
//
//	source: imgPath + "Helmet.gif"
//	visible: playing
//	playing: isHelmetBonusAct
//}
//
//AnimatedSprite{id: explSprite;
//		anchors{fill: parent; centerIn: parent}
//source: imgPath + "spriteExpl9.fileFormat"
//frameCount: 9
//frameWidth: 32
//frameHeight: 32
//frameDuration: 900 / frameCount
//		visible: running
//		running: isNeedExplode
//}
//
//AnimatedSprite{id: spawnSprite
//		anchors{fill: parent; centerIn: parent}
//source: imgPath + "sprateSpawn7.fileFormat"
//frameCount: 7
//frameWidth: 15
//frameHeight: 15
//frameDuration: 700 / frameCount
//		visible: running
//		running: spawnReady
//		z:5
//}
//

//
//Timer{
//interval: 2100
//running: spawnReady
//		onTriggered:{
//spawnReady = false
//image.visible = true
//if (tag === "P1"
//|| tag === "P2") isHelmetBonusAct = true
//if (tag === "P1") battlefield.p1Active = true
//if (tag === "P2") battlefield.p1Active = true
//}
//}
//

//
//Timer{
//interval: 15000
//running: isTankBonusAct
//		onTriggered: isTankBonusAct = false
//}
//
//Timer{
//interval: 900
//running: isNeedExplode
//		onTriggered:{
//isNeedExplode = false
//if (tag === "P1" && parent.spawnPoints === 0)
//battlefield.p1Active = false
//if (tag === "P2" && parent.spawnPoints === 0)
//battlefield.p1Active = false
//parent.x = -100
//}
//}
//
//Timer{
//interval: 80
//running: image.visible
//&& !isTimerBonusAct
//&& !battlefield.isGamePaused
//		repeat: true
//onTriggered:{
//
//if (parent.isControledByAI){
//
//if (Cpp.isCanMoveAI(battlefield, parent, parent.direction,
//maxWidth, maxHeight) === false)
//randomChangedirectionAI.interval = 100
//Cpp.moveObj(battlefield, parent, parent.direction,
//maxWidth, maxHeight)
//
////below comented is a JavaScript variant
////if (JS.isCanMoveAI(parent, parent.direction) === false)
////    randomChangedirectionAI.interval = 100
////JS.moveObj(parent, parent.direction)
//
//}else{
//
//if (parent.isPressedUp){
//Cpp.moveObj(battlefield, parent, "U",
//maxWidth, maxHeight)
//}else
//if (parent.isPressedRight){
//Cpp.moveObj(battlefield, parent, "R",
//maxWidth, maxHeight)
//}else
//if (parent.isPressedDown){
//Cpp.moveObj(battlefield, parent, "D",
//maxWidth, maxHeight)
//}else
//if (parent.isPressedLeft){
//Cpp.moveObj(battlefield, parent, "L",
//maxWidth, maxHeight)
//}
////below comented is a JavaScript variant
///* if (parent.isPressedUp) {
//	   JS.moveObj(parent, "U")
//   }else
//	   if (parent.isPressedRight) {
//		   JS.moveObj(parent, "R")
//	   }else
//		   if (parent.isPressedDown) {
//			   JS.moveObj(parent, "D")
//		   }else
//			   if (parent.isPressedLeft) {
//				   JS.moveObj(parent, "L")
//			   }
//*/
//}
//if (parent.isPressedFire && !reloadInterval.running){
//
//Cpp.makeShoot(parent, JS.createQmlObj("Bullet") )
////below comented is a JavaScript variant
////JS.makeShoot(parent)
//
//bulletShoot.play()
//reloadInterval.start()
//}
//
//}
//}
//
//Timer{id: reloadInterval
//		interval: parent.reloadInterval
//}
//
//Timer{
//interval: 3000
//running: !image.visible
//		&& parent.spawnPoints > 0
//&& !battlefield.isGamePaused
//		onTriggered:{
//if (tag === "P1" || tag === "P2"){
//parent.spawnPoints--
//}else{
//battlefield.spawnPointsEn--
//}
//parent.health = 100
//
//if (parent.isControledByAI){
//
//Cpp.setRandomXY(battlefield, parent, parent.width, parent.height)
////below comented JavaScript variant
////JS.setRandomXY(parent)
//
//}else{
//
//Cpp.setRandomXY(battlefield, parent, parent.width, parent.height)
////below comented JavaScript variant
////JS.setRandomXY(parent)
//
//}
//parent.spawnReady = true
//}
//}
//
//Timer{id: mayOpenFireAI
//		interval: 300
//running: parent.isControledByAI
//		&& image.visible
//&& !reloadInterval.running
//&& !isTimerBonusAct
//&& !battlefield.isGamePaused
//		repeat: true
//onTriggered:{
//if (Cpp.mayShootAI(battlefield, parent, maxWidth, maxHeight) ){
//Cpp.makeShoot(parent, JS.createQmlObj("Bullet") )
//
///*below comented JavaScript variant
//  if (JS.mayShootAI(parent){
//	  JS.makeShoot(parent)
//*/
//bulletShoot.play()
//reloadInterval.start()
//}
//}
//}
//
//Timer{id: randomChangedirectionAI
//		interval: 5000
//running: parent.isControledByAI
//		&& image.visible
//&& !isTimerBonusAct
//&& !battlefield.isGamePaused
//		repeat: true
//onTriggered:{
//
//Cpp.setRandomDirectionAI(battlefield, parent, maxWidth, maxHeight)
////below comented JavaScript variant
////JS.setRandomDirectionAI(parent)
//
//interval = JS.getRandomInt(2000, 6000)
//}
//}
//}
