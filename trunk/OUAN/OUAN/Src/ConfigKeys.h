#ifndef CONFIGKEYSH_H
#define CONFIGKEYSH_H

namespace OUAN
{
	const std::string CONFIG_KEYS_OGRE_PLUGINS_PATH="ogrePluginsPath";
	const std::string CONFIG_KEYS_OGRE_CONFIG_PATH="ogreConfigPath";
	const std::string CONFIG_KEYS_OGRE_LOG_PATH="ogreLogPath";
	const std::string CONFIG_KEYS_OGRE_RESOURCES_PATH="ogreResourcesPath";
	const std::string CONFIG_KEYS_OGRE_DEFAULT_MIPMAPS_NUMBER="ogreDefaultMipmapsNum";

	//Global application keys
	const std::string CONFIG_KEYS_SKIP_INTRO="SKIP_INTRO";
	const std::string CONFIG_KEYS_SUPPORTED_LANGUAGES="SUPPORTED_LANGUAGES";
	const std::string CONFIG_KEYS_INITIAL_LANGUAGE="INITIAL_LANGUAGE";
	
	//Video option keys
	const std::string CONFIG_KEYS_RENDER_SYSTEM="RENDER_SYSTEM";
	const std::string CONFIG_KEYS_FULLSCREEN="FULLSCREEN";
	const std::string CONFIG_KEYS_AA="ANTIALIASING";
	const std::string CONFIG_KEYS_BPP="BPP";
	const std::string CONFIG_KEYS_VRES="VERT_RESOLUTION";
	const std::string CONFIG_KEYS_HRES="HORIZ_RESOLUTION";
	const std::string CONFIG_KEYS_VSYNC="V_SYNC";
}

#endif