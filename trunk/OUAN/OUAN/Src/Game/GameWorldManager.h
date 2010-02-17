#ifndef GAMEWORLDMANAGERH_H
#define GAMEWORLDMANAGERH_H
#include "../OUAN.h"

namespace OUAN
{
	/// Manages the game scene:
	/// the landscape, all of its objects (creatures, props,...)
	class GameWorldManager
	{
	public:
		GameWorldManager();
		~GameWorldManager();
		/// find gameObject by Id
		/// @param objectId identifier of the object to retrieve
		/// @return pointer to the object, if found
		GameObjectPtr getObject(const std::string& objectId);
		
		/// Load level from the given file
		/// @param levelFileName name of the level file
		void loadLevel (const std::string& levelFileName);

		/// Unload data from current level
		/// (i.e, clear all object lists, destroy landscape
		/// and so on)
		void unloadLevel();

		/// Initialise object
		/// @param pointer to the application object
		void initialise(ApplicationPtr app);
		/// Free resources
		void cleanUp();

		/// Load global parameters
		void initialiseGlobalWorldData( /*const TGlobalWorldParameters& worldParams*/);

		/// Create a game object using the given 'parameters' object
		/// @param objectParams parameters to initialise the game object and its components
		/// @return the game object instance that's been created
		GameObjectPtr createGameObject(String name/*const TObjectParameters& objectParams*/);


		//Create Ogre component for the game object
		OgreComponentPtr createOgreComponent(GameObjectPtr gameObject);

		void createMeshFile(String meshfile);
		void createEntity(String name,String meshfile,bool castshadows);
		void createSubEntity(String name,int num,String material,bool visible);
		void createSceneNode(String name,String parentSceneNodeName,Vector3 position,Quaternion orientation,Vector3 scale,String autotracktarget);
		void createLight(String name,Ogre::Light::LightTypes lighttype,ColourValue diffuse,ColourValue specular,Vector3 direction,bool castshadows,Vector3 lightrange,Vector4 attenuation,Real power);
		void createParticleSystem(String name,String particle,bool castshadows);
		void createBillboard(String billBoardSetName,ColourValue colour,Vector2 dimensions,Vector3 position,Real rotation,int texcoordindex,Vector4 texrect);
		void createBillboardSet(String name,String material,Ogre::BillboardOrigin billboardorigin,Ogre::BillboardRotationType billboardrotation,Ogre::BillboardType billboardtype,Real defaultheight,Real defaultwidth,bool pointrendering,Real renderdistance,bool sorting);
		void createViewport(String name,ColourValue colour,int compositorcount,int index,bool overlays,bool shadows,bool skies);
		void createCamera(String name,Vector3 position,Quaternion orientation,String autotracktarget,bool autoaspectratio,Vector2 clipdistance,Real fov,Ogre::PolygonMode polygonmode, int viewmode);
		void createOctreeSceneManager(String name,ColourValue ambient);
		void createSkyBox(bool active, String material, Real distance);
		void createSkyDome(bool active, String material);

		/// Add the game object pointer to the objects List
		/// @param gameObject pointer to the object to add to the main list
		void addGameObject(GameObjectPtr gameObject);

		//[TODO]: Do the same with the toAdd/toDelete lists?

		/// Update world state
		/// @param elapsedTime time since last update
		void update(long elapsedTime);

		/// [TODO] Add input event handlers
		/// so that objects using a inputController
		/// (i.e, Ony, Free-lookaround cameras)
		/// can be notified

		/// Return an id value and increment it
		/// @return id value
		inline unsigned long nextId() {return mNextIdNum++;}

		/// Return the last id value used
		/// @return last id value used
		inline unsigned long lastId() {return mNextIdNum;}

	private:
		/// Generate a unique id string with the following format:
		/// "baseString"_"00value"
		/// @param baseString	reference string to make the id
		/// @param padding		number of spaces for the value.
		///						if the number is too small, it'll be padded
		///						with 'padding' zeroes
		/// @param value		the value to append to the string
		/// @return id string
		std::string makeIdString(const std::string& baseString,const int& padding, const unsigned long& value);
		//[TODO]: Uncomment line with the LevelLoader member object
		// when available (unless it's a singleton?)
		/// Level file loader
		//LevelLoaderPtr mLoader;

		/// Pointer to the main application object
		ApplicationPtr mApp;
		
		///number used to generate a unique identifier
		///for every game object that is created
		static unsigned long mNextIdNum;

		/// Game objects currently existing in the world
		TGameObjectContainer mGameObjects;
	
		// Lists of objects to be created/deleted as a result of an
		// update frame. 
		// Addition/Deletion will be effective just before the next
		// update cycle
		TGameObjectContainer mGameObjectsToAdd;
		TGameObjectContainer mGameObjectsToDelete;
		
		//BEWARE!! Delay further analysis on this till
		// we have the class on terrains and such
		// For the time being, just render island, etc meshes
		// as game objects :S	

		//LandscapePtr mLandscape; 
	};
}
#endif