#ifndef RayCastingH_H
#define RayCastingH_H
#include "../../OUAN.h"
namespace OUAN
{
	class RayCasting
	{
	public:
		RayCasting();
		~RayCasting();
		
		void init(Ogre::SceneManager * pSceneManager);

		bool raycastFromPoint(const Vector3 &point,const Vector3 &normal,Vector3 &result);


	private:

		Ogre::SceneManager * m_pscene_manager;
		Ogre::RaySceneQuery * m_pray_scene_query; 

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