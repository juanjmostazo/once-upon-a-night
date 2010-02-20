#ifndef PhysicsComponentTerrainH_H
#define PhysicsComponentTerrainH_H

#include "PhysicsComponentNonMovable.h"
namespace OUAN
{
	class PhysicsComponentTerrain: public PhysicsComponentNonMovable
	{
	public:
		PhysicsComponentTerrain(const std::string& name="");
		~PhysicsComponentTerrain();
	};

	class TPhysicsComponentTerrainParameters: public TPhysicsComponentNonMovableParameters
	{
	public:
		TPhysicsComponentTerrainParameters();
		~TPhysicsComponentTerrainParameters();
	};
}

#endif