#ifndef ATTACKCOMPONENTH_H
#define ATTACKCOMPONENTH_H

#include "../../Component/Component.h"
namespace OUAN
{
	typedef enum
	{
		ATTACK_TYPE_DEFAULT=0,
		ATTACK_TYPE_FLASHLIGHT=1,
		ATTACK_TYPE_PILLOW=2
	} TAttackType;

	class AttackData
	{
	public:
		AttackData(){}
		virtual ~AttackData(){}
		std::string attackName;
		int damage;
		int attackRange;
		std::string animationName;
		double cooldownDelay;
		double area; //Area damage radius: 0.0 for single target
		int powerCost;
		//when choosing an attack type, the chance of this particular type being selected
		//by the AI
		double weight; 
	};

	class FlashlightAttackData: public AttackData
	{
	public:
		FlashlightAttackData(){}
		virtual ~FlashlightAttackData(){}
		int rgb;
		double coneRadius;
	};

	typedef boost::shared_ptr<AttackData> AttackDataPtr;
	typedef boost::shared_ptr<FlashlightAttackData> FlashlightAttackDataPtr;
	
	typedef std::map<std::string, AttackDataPtr> TAttackCollection;
	
	/// Class to model and manage the available attacks that a GameObject may have.
	class AttackComponent: public Component
	{
	private:
		TAttackCollection mAttacks;
		AttackDataPtr mSelectedAttackData;
	public:
		AttackComponent(const std::string& type="");
		~AttackComponent();

		void init(TAttackCollection attacks, const std::string& selectedAttack="");
		void cleanUp();

		void setSelectedAttack(const std::string attackName);
		AttackDataPtr getSelectedAttack();

		void update(long elapsedTime);
	};
	class TAttackComponentParameters: public TComponentParameters
	{
	public:
		TAttackComponentParameters();
		~TAttackComponentParameters();
		TAttackCollection mAttacks;
		std::string mSelectedAttack;
	};
}
#endif