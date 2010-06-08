#ifndef SOUNDH_H
#define SOUNDH_H

namespace FMOD
{
	class Sound;
}
namespace OUAN
{
	struct TSoundData
	{
		std::string mId;
		std::string mFileName;
		std::string mChannelGroupID;
		bool mLoop;
		bool mHardware;
		bool m3D;
		bool mStream;
		//These arguments are used on a per-channel basis. However, since
		//all the instances will most likely be using the same values, I'm creating
		//them here so that this information is loaded together with the rest of sound data
		double minDistance;
		double maxDistance;
	};

	class Sound: public Ogre::Resource
	{
	private:
		FMOD::Sound* mFMODSound;
	protected:
		// must implement these from the Ogre::Resource interface
		void loadImpl();
		void unloadImpl();
		size_t calculateSize() const;
	public:
		Sound(Ogre::ResourceManager* creator, const Ogre::String& name,
			Ogre::ResourceHandle handle, const Ogre::String& group, 
			bool isManual=false,Ogre::ManualResourceLoader* loader=NULL);
		virtual ~Sound();

		TSoundData mSoundData;			

		FMOD::Sound* getFMODSound() const;
		void setFMODSound(FMOD::Sound* FMODSound);
	};

	//Needed so it can be used as a Resource
	class SoundPtr : public Ogre::SharedPtr<Sound> 
	{
	public:
		SoundPtr() : Ogre::SharedPtr<Sound>() {}
		explicit SoundPtr(Sound *rep) : Ogre::SharedPtr<Sound>(rep) {}
		SoundPtr(const SoundPtr &r) : Ogre::SharedPtr<Sound>(r) {} 
		SoundPtr(const Ogre::ResourcePtr &r) : Ogre::SharedPtr<Sound>()
		{
			if( r.isNull() )
				return;
			// lock & copy other mutex pointer
			OGRE_LOCK_MUTEX(*r.OGRE_AUTO_MUTEX_NAME)
				OGRE_COPY_AUTO_SHARED_MUTEX(r.OGRE_AUTO_MUTEX_NAME)
				pRep = static_cast<Sound*>(r.getPointer());
			pUseCount = r.useCountPointer();
			useFreeMethod = r.freeMethod();
			if (pUseCount)
			{
				++(*pUseCount);
			}
		}

		/// Operator used to convert a ResourcePtr to a SoundPtr
		SoundPtr& operator=(const Ogre::ResourcePtr& r)
		{
			if(pRep == static_cast<Sound*>(r.getPointer()))
				return *this;
			release();
			if( r.isNull() )
				return *this; // resource ptr is null, so the call to release above has done all we need to do.
			// lock & copy other mutex pointer
			OGRE_LOCK_MUTEX(*r.OGRE_AUTO_MUTEX_NAME)
				OGRE_COPY_AUTO_SHARED_MUTEX(r.OGRE_AUTO_MUTEX_NAME)
				pRep = static_cast<Sound*>(r.getPointer());
			pUseCount = r.useCountPointer();
			useFreeMethod = r.freeMethod();
			if (pUseCount)
			{
				++(*pUseCount);
			}
			return *this;
		}
	};
}
#endif