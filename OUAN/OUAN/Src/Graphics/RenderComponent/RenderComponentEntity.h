#ifndef RenderComponentEntityH_H
#define RenderComponentEntityH_H

#include "RenderComponent.h"

namespace OUAN
{
	class RenderComponentEntity: public RenderComponent
	{
	private:
		Ogre::Entity * mEntity;
	public:

		RenderComponentEntity(const std::string& type="");
		~RenderComponentEntity();

		Ogre::Entity * getEntity() const;
		void setEntity(Ogre::Entity *);

		void setVisible(bool visible);
	};

	class TRenderComponentSubEntityParameters: public TRenderComponentParameters
	{
	public:
		TRenderComponentSubEntityParameters();
		~TRenderComponentSubEntityParameters();

		String material;
		bool visible;
	};

	class TRenderComponentEntityParameters: public TRenderComponentParameters
	{
	public:
		TRenderComponentEntityParameters();
		~TRenderComponentEntityParameters();

		String meshfile;
		bool castshadows;
		std::vector<TRenderComponentSubEntityParameters> tRenderComponentSubEntityParameters;
	};
}

#endif