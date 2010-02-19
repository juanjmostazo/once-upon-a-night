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

		RenderComponentEntity(const std::string& name="");
		~RenderComponentEntity();

		Ogre::Entity * getEntity() const;
		void setEntity(Ogre::Entity *);

	};
}

#endif