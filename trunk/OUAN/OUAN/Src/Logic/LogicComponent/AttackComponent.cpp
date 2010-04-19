#include "AttackComponent.h"
using namespace OUAN;

AttackComponent::AttackComponent(const std::string& type)
:Component(COMPONENT_TYPE_ATTACK)
{

}
AttackComponent::~AttackComponent()
{

}

void AttackComponent::init(TAttackCollection attacks, const std::string& selectedAttack)
{
	mAttacks.clear();
	for (TAttackCollection::iterator it=attacks.begin();it!=attacks.end();++it)
	{
		mAttacks[it->first]=it->second;
	}
	if (!selectedAttack.empty())
	{
		mSelectedAttackData=mAttacks[selectedAttack];
	}

}
void AttackComponent::cleanUp()
{
	mAttacks.clear();
}

void AttackComponent::setSelectedAttack(const std::string attackName)
{
	mSelectedAttackData=mAttacks[attackName];
}
AttackDataPtr AttackComponent::getSelectedAttack()
{
	return mSelectedAttackData;
}

void AttackComponent::update(long elapsedTime)
{

}
TAttackComponentParameters::TAttackComponentParameters()
{
}
TAttackComponentParameters::~TAttackComponentParameters()
{

}
