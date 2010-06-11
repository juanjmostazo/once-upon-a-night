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

#define _CRT_SECURE_NO_WARNINGS