#ifndef LOGGERH_H
#define LOGGERH_H
namespace OUAN
{
	class Logger
	{
	private:
		static Logger* mInstance;
		Logger();

		bool mEnabled;

	public:
		~Logger();
		static Logger* getInstance();
		void log(Ogre::String message);
	};
}

#endif