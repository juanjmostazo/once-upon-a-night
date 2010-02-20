#include "GameObjectMovable.h"

using namespace OUAN;

GameObjectMovable::GameObjectMovable(const std::string& name, const std::string& id)
:GameObjectPositional(name,id)
{

}

GameObjectMovable::~GameObjectMovable()
{

}

TGameObjectMovableParameters::TGameObjectMovableParameters() : TGameObjectPositionalParameters()
{
}
TGameObjectMovableParameters::~TGameObjectMovableParameters()
{
}