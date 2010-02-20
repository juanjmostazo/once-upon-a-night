#include "GameObjectOny.h"

using namespace OUAN;

GameObjectOny::GameObjectOny(const std::string& name, const std::string& id)
:GameObjectMovableEntity(name,id)
{

}

GameObjectOny::~GameObjectOny()
{

}

TGameObjectOnyParameters::TGameObjectOnyParameters() : TGameObjectMovableEntityParameters()
{
}
TGameObjectOnyParameters::~TGameObjectOnyParameters()
{
}