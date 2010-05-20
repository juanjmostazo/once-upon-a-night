#ifndef HUDINGAMEH_H
#define HUDINGAMEH_H
#include "HUDBase.h"
#include "../../Event/EventDefs.h"
#include <boost/enable_shared_from_this.hpp>
namespace OUAN
{
	const std::string OVERLAY_INGAME_HUD = "OUAN/HUDOverlay";

	//Take this out to a file

	//Flashlight roulette textures
	const std::string TEX_ROULETTE_COLOUR_BLUE="roulette_n_blue.png";
	const std::string TEX_ROULETTE_COLOUR_RED="roulette_n_red.png";
	const std::string TEX_ROULETTE_COLOUR_GREEN="roulette_n_green.png";
	const std::string TEX_ROULETTE_TRANSITION_RG="roulette_n_rg.png";
	const std::string TEX_ROULETTE_TRANSITION_GB="roulette_n_gb.png";
	const std::string TEX_ROULETTE_TRANSITION_BR="roulette_n_br.png";
	const std::string TEX_ROULETTE_TRANSITION_GR="roulette_n_gr.png";
	const std::string TEX_ROULETTE_TRANSITION_RB="roulette_n_rb.png";
	const std::string TEX_ROULETTE_TRANSITION_BG="roulette_n_bg.png";
	
	//TODO: Pillow roulette textures?

	//Health icon textures
	const std::string TEX_HEALTH_HUD_NAME_FULL="HUDHealth03.png";
	const std::string TEX_HEALTH_HUD_NAME_X2="HUDHealth02.png";
	const std::string TEX_HEALTH_HUD_NAME_X1="HUDHealth01.png";
	const std::string TEX_HEALTH_HUD_NAME_EMPTY="HUDHealth00.png";

	const std::string OVERLAY_INGAME_HUD_LIVES_TEXT="OUAN/NumLives";
	const std::string MATERIAL_ROULETTE="OUAN/Hud/Roulette";
	const std::string MATERIAL_HEALTH="OUAN/Hud/Health";
	
	const std::string PANEL_ROULETTE="OUAN/RoulettePanel";

	const int TRANSITION_NFRAMES=2;
	const float TRANSITION_DURATION=0.5f;

	typedef enum 
	{
		ROULETTE_TRANSITION_02=0,
		ROULETTE_STATE_0,
		ROULETTE_TRANSITION_01,
		ROULETTE_TRANSITION_10,
		ROULETTE_STATE_1,
		ROULETTE_TRANSITION_12,
		ROULETTE_TRANSITION_21,
		ROULETTE_STATE_2,
		ROULETTE_TRANSITION_20
	}TRouletteState;
	const int NUM_ROULETTE_STATES=ROULETTE_TRANSITION_20-ROULETTE_TRANSITION_02+1;

	typedef struct
	{
		std::string textureName;
		bool isAnimated;
		float duration;
		int numFrames;
	} TRouletteInfo;
	typedef std::map<TRouletteState,TRouletteInfo> TRouletteInfoMap;

	const int NUM_HEALTH_POINTS=3; //TODO: Change this so it doesn't depend on hardcoded values!!

	//-- 
	class HUDInGame: public HUDBase, public boost::enable_shared_from_this<HUDInGame>
	{
	private:
		TRouletteInfoMap mRouletteData;
		TRouletteState mCurrentRouletteState;

		std::string mHealthHudTextures[NUM_HEALTH_POINTS+1];

		Ogre::MaterialPtr mRouletteMaterial;
		Ogre::MaterialPtr mHealthMaterial;

		Ogre::OverlayElement* mLives;

		void initRouletteData();
		void initHealthHud(int healthPoints, int numLives);
		void updateRoulette();		
		bool isRouletteAnimationFinished();
		void updateRouletteHUD();
		void updateHealthHUD(int healthPoints, int numLives);

		bool mSelectedModeChanged;

		//Changeworld functions and variables
		void changeToWorld(int newWorld, double perc);
		void changeWorldFinished(int newWorld);
		void changeWorldStarted(int newWorld);
		void activateChangeWorld();
		void activateChangeWorldFast();

		double mChangeWorldTotalTime;
		double mChangeWorldElapsedTime;
		bool mIsChangingWorld;
		int mWorld;

	public:
		HUDInGame();
		~HUDInGame();
		void init(int healthPoints, int numLives, int newWorld);
		void destroy();
		void update(double elapsedSeconds,int healthPoints, int numLives);

		void spinRoulette(bool forward);

		bool isSelectedModeChanged();
		void setSelectedModeChanged(bool selectedModeChanged);
		TRouletteState getCurrentState() const;

		//register/unregister
		void registerEventHandlers(EventManagerPtr evtMgr);
		void unregisterEventHandlers(EventManagerPtr evtMgr);
		void processChangeWorld(ChangeWorldEventPtr evt);
		
	};
}
#endif