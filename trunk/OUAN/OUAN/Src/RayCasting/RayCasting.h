#ifndef RayCastingH_H
#define RayCastingH_H
#include "../OUAN.h"
namespace OUAN
{
	class RayCasting
	{
	public:
		RayCasting();
		~RayCasting();
		
		void init(RenderSubsystemPtr pRenderSubsystem,PhysicsSubsystemPtr pPhysicsSubsystem);

		bool raycastRenderClosestGeometry(const Vector3 point,const Vector3 normal,Vector3 &result,Ogre::Entity* & pEntity,double maxDistance=-1,QueryFlags flags=QUERYFLAGS_NONE);
		bool raycastPhysicsClosestGeometry(const Vector3 point,const Vector3 normal,Vector3 &result,Ogre::uint32 & collisionType,double maxDistance=-1,QueryFlags flags=QUERYFLAGS_NONE);

		bool raycastRenderClosestBoundings(const Vector3 point,const Vector3 normal,Vector3 &result,Ogre::uint32 &  collisionType,double maxDistance=-1,QueryFlags flags=QUERYFLAGS_NONE);
		bool raycastPhysicsClosestBoundings(const Vector3 point,const Vector3 normal,Vector3 &result,Ogre::uint32 & collisionType,double maxDistance=-1,QueryFlags flags=QUERYFLAGS_NONE);

		bool raycastPhysicsAllBoundings(const Vector3 point,const Vector3 normal,std::vector<GameObjectPtr> &result,Ogre::uint32 & collisionType,double maxDistance=-1,QueryFlags flags=QUERYFLAGS_NONE);

		bool raycastRenderAllGeometry(const Vector3 point,const Vector3 normal,Vector3 &result,Ogre::Entity* & pEntity,std::vector<Ogre::Entity*> &allCollisions,double maxDistance=-1,QueryFlags flags=QUERYFLAGS_NONE);


	private:

		Ogre::SceneManager * m_pscene_manager;
		Ogre::RaySceneQuery * m_pray_scene_query; 
		PhysicsSubsystemPtr mPhysicsSubsystem;

		void GetMeshInformation(const Ogre::MeshPtr mesh,
                                size_t &vertex_count,
                                Ogre::Vector3* &vertices,
                                size_t &index_count,
                                unsigned long* &indices,
                                const Ogre::Vector3 &position,
                                const Ogre::Quaternion &orient,
                                const Ogre::Vector3 &scale);
					
	};
}

#endif