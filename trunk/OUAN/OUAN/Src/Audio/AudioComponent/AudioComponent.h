#ifndef AUDIOCOMPONENTH_H
#define AUDIOCOMPONENTH_H

#include "../../Component/Component.h"

namespace OUAN{
	
	class AudioComponent: public Component
	{
	public:
		AudioComponent(const std::string& type="");
		~AudioComponent();

		virtual void update(long elapsedTime);
	private:
		// WIP for me: Define the data structure here.
		// It should contain keys linking states/sounds to entries
		// in the audio subsystem cache
		// The update method might have to fetch positional data
		// from its sibling

	};
}
#endif