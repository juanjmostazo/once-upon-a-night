#include "GameObjectMagicClock.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectMagicClock::GameObjectMagicClock(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_MAGIC_CLOCK)
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