#include "GameObjectNonMovable.h"

using namespace OUAN;

GameObjectNonMovable::GameObjectNonMovable(const std::string& name, const std::string& id)
:GameObjectPositional(name,id)
{

}

GameObjectNonMovable::~GameObjectNonMovable()
{

}

TGameObjectNonMovableParameters::TGameObjectNonMovableParameters() :TGameObjectPositionalParameters()
{
}
TGameObjectNonMovableParameters::~TGameObjectNonMovableParameters()
{
}