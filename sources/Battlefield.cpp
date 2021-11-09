//
// Created by d.romanichenko on 12-Jul-21.
//

#include <Battlefield.hpp>

bool Battlefield::isDestroyedHq() const
{
	return isDestroyedHQ;
}
void Battlefield::setIsDestroyedHq(bool isDestroyedHq)
{
	isDestroyedHQ = isDestroyedHq;
	onIsDestroyedHQChanged();
}
void Battlefield::onIsDestroyedHQChanged()
{
//p1.spawnPoints = 0
//p2.spawnPoints = 0
}

int Battlefield::getGameMode() const
{
	return gameMode;
}
void Battlefield::setGameMode(int _gameMode)
{
	gameMode = _gameMode;
}
void Battlefield::onGameModeChanged()
{
	spawnPointsEn = 20;
	switch (gameMode)
	{
		case SOLO_MODE:
//			p1.spawnPoints = 3;
//			p2.spawnPoints = 0;
			p1Active = true;
			p2Active = false;
//			p1.isControledByAI = false;
//			p2.isControledByAI = false;
			break;

		case DUO_MODE:
//			p1.spawnPoints = 3;
//			p2.spawnPoints = 3;
			p1Active = true;
			p2Active = true;
//			p1.isControledByAI = false;
//			p2.isControledByAI = false;
			break;
		case COOP_MODE:
//			p1.spawnPoints = 3;
//			p2.spawnPoints = 3;
			p1Active = true;
			p2Active = true;
//			p1.isControledByAI = false;
//			p2.isControledByAI = true;
			break;
	}
//	p1.health = 0; p1.spawnReady = false;
//	p2.health = 0; p2.spawnReady = false;
//	e1.health = 0; e1.spawnReady = false;
//	e2.health = 0; e2.spawnReady = false;
//	e3.health = 0; e3.spawnReady = false;
//	e4.health = 0; e4.spawnReady = false;

//	p1.counterShoots     = 0; p2.counterShoots     = 0;
//	p1.counterTagetHits  = 0; p2.counterTagetHits  = 0;
//	p1.counterTankKils   = 0; p2.counterTankKils   = 0;
//	p1.counterBulletHits = 0; p2.counterBulletHits = 0;
//	p1.counterBrickHits  = 0; p2.counterBrickHits  = 0;

//	listAllObjects.forEach(
//		function(item, i, listAllObjects) {
//			item.health = 0
//			delete listAllObjects[i]
//	})
//	drawBlock.running = true;
//	focus = true;
//	battlefield.isDestroyedHQ = false;
}
