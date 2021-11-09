//
// Created by d.romanichenko on 12-Jul-21.
//

#ifndef BATTLEFIELD_HPP
#define BATTLEFIELD_HPP

#include <string>
#include <list>

#include <SDL2/SDL.h>

#include <IDestructibleObject.hpp>
#include <IShape.hpp>

class Battlefield
{

public:
	Battlefield(
		SDL_Window* Window)
	:
		window(Window)
	{ };

//	const std::string id = "battlefield";
//	std::string objectName = "Battlefield";
public:
	std::list<IShape*> shapedObjects;

	SDL_Window* window;
	//global state
	bool isInMenu = true;
	bool isGamePaused = false;
	int spawnPointsEn = 20;
	int levelNum = 1;
	bool isTimerBonusActEn = false;
	bool isTimerBonusActPl = false;
	bool isDestroyedHQ = false;
	bool p1Active = false;
	bool p2Active = false;
	bool focus = true;
	int gameMode = DEMO;
	enum gameType
	{
		DEMO,
		SOLO_MODE,
		DUO_MODE,
		COOP_MODE
	};

	//statisics
	int counterShoots;
	int counterTagetHits;
	int counterTankKils;
	int counterBulletHits;
	int counterBrickHits;
//property var listAllObjects: [];

public:
	[[nodiscard]] int getGameMode() const;
	void setGameMode(int gameMode);
	void onGameModeChanged();

	[[nodiscard]] bool isDestroyedHq() const;
	void setIsDestroyedHq(bool isDestroyedHq);
	void onIsDestroyedHQChanged();

//	Component.onCompleted: {startGame.play()}
//SoundEffect{id: bulletShoot; volume: .1; loops: 1; source: "qrc:/wav/shoot.wav" }
//SoundEffect{id: bonusPickUp; volume: .1; loops: 1; source: "qrc:/wav/bonusPickUp.wav" }
//SoundEffect{id: startGame;   volume: .1; loops: 1; source: "qrc:/wav/levelStarted.wav" }
//SoundEffect{id: explosion;   volume: .1; loops: 1; source: "qrc:/wav/explosion.wav" }

//// |tag:     |"E{Num}" |"P1"|"P2"|  "obsticle{name}" |
////  |fraction:|"Enemies"|"Players"|"neitral"|"bonuses"|
//TankEnemy{id: e1; property string tag: "E1" }
//TankEnemy{id: e2; property string tag: "E2" }
//TankEnemy{id: e3; property string tag: "E3" }
//TankEnemy{id: e4; property string tag: "E4" }
//
//TankPlayer{
//	id: p1
//	property string tag: "P1"
//	property string imgName: tag
//	property int spawnPosMinX: 0
//	property int spawnPosMaxX: mainWindow.width / 2 - battlefield.blockWidth * 6 - width
//}
//TankPlayer{
//	id: p2
//	property string tag: "P2"
//	property string imgName: tag
//	property int spawnPosMinX: mainWindow.width / 2 + battlefield.blockWidth * 4
//	property int spawnPosMaxX: mainWindow.width - width - sideBar.width
//}

};
//Timer{
//	interval: 10000;
//	running     = battlefield.isTimerBonusActPl;
//	onTriggered = battlefield.isTimerBonusActPl = false;
//}
//Timer{
//	interval: 10000;
//	running     = battlefield.isTimerBonusActEn;
//	onTriggered = battlefield.isTimerBonusActEn = false;
//}
//Timer{
//	id: drawBlock;
//	interval: 100;
//	running: true;
//	onTriggered:{
//	var currentLevel = Lvl.level1
//	var maxY = mainWindow.height
//	var maxX = mainWindow.width - sideBar.width
//
//	parent.blockWidth  = Math.round(maxX / currentLevel[0].length);
//	parent.blockHeight = Math.round(maxY / currentLevel.length);
//
//	for     (var i = 0; i < currentLevel.length   ; ++i)
//		for (var j = 0; j < currentLevel[i].length; ++j)
//		{
//			switch (currentLevel[i][j])
//			{
//				case 1: JS.makeObsticle(parent.blockWidth, parent.blockHeight, j, i, "brick"); break
//				case 2: JS.makeObsticle(parent.blockWidth, parent.blockHeight, j, i, "brickWhite"); break
//				case 3: JS.makeObsticle(parent.blockWidth, parent.blockHeight, j, i, "base"); break
//			}
//		}
//	}
//}
//Timer{
//	id: forPlaceBonuses;
//	interval: 30000
//	running: !battlefield.isGamePaused; repeat: true;
//	onTriggered: JS.makeBonus() //without arg, put in random empty space
//}


//
////test bonus for player and enemy
//// Bonuses{          x: 230; y: 510}
//// Bonuses{          x:   0; y:   0}


///TODO: move to UI
//Image{id: pauseImg
//		anchors.centerIn: noRevivalText
//		source: "qrc:/img/pause.fileFormat"
//visible: parent.isGamePaused
//		scale: 2
//}
//
//Text{id: noRevivalText
//		property bool isPassObsticle: true
//color: "white"
//text: "HQ is destroyed, no revival"
//font.pixelSize: 17
//x: (mainWindow.width - sideBar.width) / 2 - noRevivalText.width / 2
//y: mainWindow.height - parent.blockHeight * 7
//visible: false
//z:5
//Timer{id: blinking
////todo: not work, need fix
//interval: 500
//running: battlefield.isDestroyedHQ
//		repeat: true
//onTriggered: {parent.visible = (parent.visible) ? false : true}
//}
//Timer{id: textOff
//		interval: 5000
//running: battlefield.isDestroyedHQ
//		onTriggered: noRevivalText.destroy()
//}
//}
//}
//}
#endif //BATTLEFIELD_HPP
