#include "GameObjectMagicClock.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectMagicClock::GameObjectMagicClock(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_MAGICCLOCK)
{

}

GameObjectMagicClock::~GameObjectMagicClock()
{

}


TGameObjectMagicClockParameters::TGameObjectMagicClockParameters() : TGameObjectParameters()
{

}

TGameObjectMagicClockParameters::~TGameObjectMagicClockParameters()
{

}