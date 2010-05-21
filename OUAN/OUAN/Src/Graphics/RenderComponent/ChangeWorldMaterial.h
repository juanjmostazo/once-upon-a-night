#ifndef ChangeWorldMaterialH_H
#define ChangeWorldMaterialH_H

#include "../../OUAN.h"
namespace OUAN
{
	class ChangeWorldMaterial
	{
	public:
		ChangeWorldMaterial();
		~ChangeWorldMaterial();

		virtual void update(long elapsedTime);

	};

}

#endif