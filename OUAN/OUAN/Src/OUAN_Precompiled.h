#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <sstream>
#include <iostream>
#include <fstream>
#include <iomanip>

#include <cstdlib>
#include <cmath>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cassert>
#include <ctype.h>
#include <cstddef>

#include <string>
#include <queue>
#include <list>
#include <vector>
#include <map>
#include <set>
//#include <sys/stat.h>
#include <algorithm>

#include <Ogre.h>
#include <OgreTagPoint.h>
#include <NxOgre.h>
#include <NxOgreOGRE3D.h>
#include <NxOgreAddonCharacterController.h>

#include <ois/OIS.h>
#include <cegui/CEGUI.h>
#include <OgreCEGUIRenderer.h>

extern "C" {
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}
#include <luabind/luabind.hpp>

#include <Dshow.h>   // DirectShow (using DirectX 9.0 for dev)

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/random.hpp>
#include <boost/nondet_random.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/astar_search.hpp>

#include <fmod.hpp>
#include <fmod_errors.h>

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseScriptDeserializer.h"
#include "ParticleUniverseScriptSerializer.h"
#include "ParticleUniverseRendererFactory.h"
#include "ParticleRenderers/ParticleUniverseBoxSet.h"
#include "ParticleRenderers/ParticleUniverseBox.h"
#include "ParticleRenderers/ParticleUniverseSphereSet.h"
#include "ParticleRenderers/ParticleUniverseSphere.h"
#include "ParticleUniverseEmitterFactory.h"
#include "ParticleUniverseAffectorFactory.h"
#include "ParticleUniverseObserverFactory.h"
#include "ParticleUniverseEventHandlerFactory.h"
#include "ParticleUniverseExternFactory.h"
#include "ParticleUniverseBehaviourFactory.h"
#include "ParticleUniverseITokenBind.h"
#include "ParticleUniverseIAlias.h"
#include "ParticleUniverseCameraDependency.h"
#include "ParticleUniverseSystemTokens.h"
#include "ParticleUniverseTechniqueTokens.h"
#include "ParticleUniverseRendererTokens.h"
#include "ParticleUniverseEmitterTokens.h"
#include "ParticleUniverseAffectorTokens.h"
#include "ParticleUniverseObserverTokens.h"
#include "ParticleUniverseAttachableTokens.h"
#include "ParticleUniverseDynamicAttributeTokens.h"
#include "ParticleUniverseSystemManagerTokens.h"
#include "ParticleUniverseCameraDependencyTokens.h"
#include "ParticleUniverseAttachable.h"

/// These macros will reset the shared pointers, just in case 
/// clearing the containers will mess with the pointers' references count
#define EMPTY_VECTOR(T,v) \
	for (T::iterator it=v.begin();it!=v.end();++it) \
	{ \
		(*it).reset(); \
	}\
	v.clear();
#define EMPTY_MAP(T,v) \
	for (T::iterator it=v.begin();it!=v.end();++it) \
	{ \
		(it->second).reset(); \
	}\
	v.clear();

#define SAFEDELETE(ptr) if(ptr){ delete ptr;ptr=NULL;}

#define BOOST_PTR_CAST(type, var) boost::dynamic_pointer_cast<type>(var)

//EXAMPLE OF USE
// GameObjectOny => CLASS_DECLARATIONS(GameObjectOny);
// Result:
//	class GameObjectOny;
//	class TGameObjectOnyParameters;
//  typedef boost::shared_ptr<GameObjectOny> GameObjectOnyPtr;
#define CLASS_DECLARATIONS(x) class x;\
	class T##x##Parameters;\
	typedef boost::shared_ptr<x> x##Ptr

//EXAMPLE OF USE
// RenderSubsystem => CLASS_DECLARATIONS_NO_PARAMS(RenderSubsystem);
// Result:
//	class RenderSubsystem;
//  typedef boost::shared_ptr<RenderSubsystem> RenderSubsystemPtr;
#define CLASS_DECLARATIONS_NO_PARAMS(y) class y;\
	typedef boost::shared_ptr<y> y##Ptr

//EXAMPLE OF USE
// GAMEOBJECT_CONTAINER_DECL(Animated);
// Result:
//	typedef std::vector<GameObjectPtr> TGameObjectAnimatedContainer;
#define GAMEOBJECT_CONTAINER_DECL(x) \
	typedef std::vector<GameObjectPtr> TGameObject##x##Container

//EXAMPLE OF USE
// CONCRETE_GAMEOBJECT_CONTAINER_DECL(Ony);
// Result:
//	typedef std::vector<GameObjectOnyPtr> TGameObjectOnyContainer;
#define CONCRETE_GAMEOBJECT_CONTAINER_DECL(x) \
	typedef std::vector<GameObject##x##Ptr> TGameObject##x##Container

//EXAMPLE OF USE
// GAMEOBJECT_CLASS_DECL(Ony);
// Result:
// class GameObjectOny;
// class TGameObjectOnyParameters;
// typedef boost::shared_ptr<GameObjectOny> GameObjectOnyPtr;
// typedef std::vector<GameObjectOnyPtr> TGameObjectOnyContainer;
#define GAMEOBJECT_CLASS_DECL(x)\
	CLASS_DECLARATIONS(GameObject##x);\
	CONCRETE_GAMEOBJECT_CONTAINER_DECL(x)

typedef std::map<int,Ogre::VertexPoseKeyFrame*> TKeyFrameMap;

#define _CRT_SECURE_NO_WARNINGS