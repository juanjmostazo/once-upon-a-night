#ifndef RenderComponentInitialH_H
#define RenderComponentInitialH_H

#include "RenderComponent.h"
#include "../RenderSubsystem.h"
namespace OUAN
{
	class RenderComponentInitial: public RenderComponent
	{
	private:
		Vector3 mPosition;
		Quaternion mOrientation;

	public:
		RenderComponentInitial(const std::string& type="");
		~RenderComponentInitial();

		Vector3 getPosition() const;
		void setPosition(Vector3);

		Quaternion getOrientation() const;
		void setOrientation(Quaternion);
	};
}

#endif