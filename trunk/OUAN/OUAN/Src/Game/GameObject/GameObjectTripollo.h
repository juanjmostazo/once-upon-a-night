#ifndef GameObjectTripolloH_H
#define GameObjectTripolloH_H
#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Graphics/RenderComponent/RenderComponentEntity.h"
namespace OUAN
{
	/// Class modelling a particular enemy type
	class GameObjectTripollo : public GameObject
	{
	private:
		/// Visual component
		RenderComponentEntityPtr mRenderComponentEntity;
		/// Positional component
		RenderComponentPositionalPtr mRenderComponentPositional;

	public:
		/// Constructor
		/// @param name name of the game object, specific to this class
		/// @param id unique id of the game object
		GameObjectTripollo(const std::string& name, const std::string& id);

		//Destructor
		~GameObjectTripollo();

		/// Return render component entity 
		/// @return render component entity
		RenderComponentEntityPtr getRenderComponentEntity() const;

		/// Set render component
		/// @param pRenderComponentEntity
		void setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity);

		/// Set positional component
		/// @param pRenderComponentPositional the component containing the positional information
		void setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional);

		/// Return positional component 
		/// @return positional component
		RenderComponentPositionalPtr getRenderComponentPositional() const;
	};
	
	/// Information data structure to carry around data between the
	/// level loader and the "GameObjectTripollo"
	class TGameObjectTripolloParameters: public TGameObjectParameters
	{
	public:
		/// Default constructor
		TGameObjectTripolloParameters();
		/// Default destructor
		~TGameObjectTripolloParameters();

		///Parameters specific to an Ogre Entity
		TRenderComponentEntityParameters tRenderComponentEntityParameters;
		///Positional parameters
		TRenderComponentPositionalParameters tRenderComponentPositionalParameters;

	};

}
#endif