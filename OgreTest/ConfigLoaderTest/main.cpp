#include "Configuration.h"

#include <iostream>

const std::string INPUT_FILE="configTest_IN.xml";
const std::string OUTPUT_FILE="configTest_OUT.xml";

int main()
{
	Configuration config;
	if(!config.loadFromFile(INPUT_FILE))
		return 1;
	std::cout<<"------------------------------------------"<<std::endl;
	std::cout<<"Accessor test 1- existing key \"fullscreen\" ";
	std::string value;
	bool result=config.getOption("fullscreen",value);
	if(result)
		std::cout<<" FOUND. Value:"<<value<<std::endl;
	else
		std::cout<<"NOT FOUND";
	std::cout<<"Accessor test 2- non-existing key \"useHDR\" ";

	result=config.getOption("useHDR",value);
	if(result)
		std::cout<<" FOUND. Value:"<<value<<std::endl;
	else
		std::cout<<"NOT FOUND";
	std::cout<<"------------------------------------------"<<std::endl;
	std::cout<<"Traversal test"<<std::endl;
	for (TConfigMapConstIterator iter=config.begin();iter!=config.end();++iter)
	{
		std::cout<<"Key: "<<iter->first<<", Value: "<<iter->second<<std::endl;
	}
	std::cout<<"------------------------------------------"<<std::endl;
	std::cout<<"Option modifying test 1 - new key \"textureDetail\", value \"High\""<<std::endl;
	config.setOption("textureDetail","High");
	if(config.getOption("textureDetail",value))
		std::cout<<"Key addition successful. Value: "<<value<<std::endl;
	std::cout<<"Option modifying test 2 - existing key \"textureDetail\", value \"Low\", replace=true"<<std::endl;
	config.setOption("textureDetail","Low");
	if(config.getOption("textureDetail",value))
		std::cout<<"Key substitution successful. Value: "<<value<<std::endl;
	std::cout<<"Option modifying test 3 - new key \"textureDetail\", value \"Medium\", replace=false"<<std::endl;
	config.setOption("textureDetail","Medium",false);
	if(!config.getOption("textureDetail",value))
		std::cout<<"Key wasn't replaced. Old Value: "<<value<<std::endl;
	std::cout<<"------------------------------------------"<<std::endl;
	std::cout<<"New map creation"<<std::endl;
	TConfigMap newMap;
	newMap["difficultyLevel"]="Easy";
	newMap["numLives"]="3";
	newMap["autoSaveEnabled"]="true";
	config.setMap(newMap);
	std::cout<<"New map traversal:"<<std::endl;
	for (TConfigMapConstIterator iter=config.begin();iter!=config.end();++iter)
	{
		std::cout<<"Key: "<<iter->first<<", Value: "<<iter->second<<std::endl;
	}

	config.saveToFile(OUTPUT_FILE);
	return 0;

}