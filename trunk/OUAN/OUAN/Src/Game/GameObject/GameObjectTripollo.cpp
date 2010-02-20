#include "GameObjectTripollo.h"

using namespace OUAN;

GameObjectTripollo::GameObjectTripollo(const std::string& name, const std::string& id)
:GameObjectMovableEntity(name,id)
{

}

GameObjectTripollo::~GameObjectTripollo()
{

}

TGameObjectTripolloParameters::TGameObjectTripolloParameters() : TGameObjectMovableEntityParameters()
{
}
TGameObjectTripolloParameters::~TGameObjectTripolloParameters()
{
}