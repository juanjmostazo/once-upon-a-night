#ifndef CONFIGURATIONH_H
#define CONFIGURATIONH_H

#include <map>
#include <string>

//Type definition for the data structure that'll hold the options:
//an STL map of pairs of strings
typedef std::map<std::string, std::string> TConfigMap;

//Aliases for the Config map iterators
typedef TConfigMap::iterator TConfigMapIterator;
typedef TConfigMap::const_iterator TConfigMapConstIterator;

//
class Configuration
{
private:
	TConfigMap configMap;
public:
	Configuration();
	~Configuration();
	//Import/Export
	bool loadFromFile(const std::string& fileName, unsigned int flags=0);
	bool saveToFile(const std::string& fileName, unsigned int flags=0) const;

	//Replace options map with the one from the argument list
	void setMap(const TConfigMap& newMap);
	
	//Add pairs <key,value> from newMap. Depending on the value of replaceExisting,
	//the values for those keys already present in the map will be overwritten or not.
	void addOptions(const TConfigMap& newMap, bool replaceExisting=true);

	//Tell if the given key is present in the config map
	bool hasOption(const std::string& key) const;
	//If the map has the given key, then set the 'value' parameter accordingly and return true;
	//Otherwise, return false
	bool getOption(const std::string& key,std::string& value);
	//Set the 'key' option to the specified value provided that the key is not found on the map 
	//or replaceExisting is true
	void setOption (const std::string& key, const std::string& value, bool replaceExisting=true);

	//Provide indirect access to the map (This can be useful when we need to traverse the map)
	TConfigMapConstIterator  begin() const;
	TConfigMapConstIterator  end() const;
};

#endif