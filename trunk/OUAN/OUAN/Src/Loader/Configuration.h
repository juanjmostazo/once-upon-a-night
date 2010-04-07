#ifndef CONFIGURATIONH_H
#define CONFIGURATIONH_H

#include "../OUAN.h"

namespace OUAN
{
	//Constant names
	/// name of the xml's root element
	const std::string XML_ELEMENT_ROOT="Configuration";
	/// name of the xml's <options> element
	const std::string XML_ELEMENT_OPTIONS="Options";
	/// name of the xml's <option> element
	const std::string XML_ELEMENT_OPTION="Option";
	/// name of the xml's key attribute for the <option> element
	const std::string XML_ELEMENT_OPTION_ATTRIBUTE_KEY="key";
	/// default text for xml comment
	const std::string XML_COMMENT="Config options";
	/// xml declaration's version number
	const std::string XML_DECLARATION_VERSION="1.0";
	/// xml declaration's encoding
	const std::string XML_DECLARATION_ENCODING="";
	/// xml's standalone declaration
	const std::string XML_DECLARATION_STANDALONE="";

	/// This class holds an associative map of <key,value> pairs.
	/// It provides methods to set and retrieve options, as well
	/// as loading/saving a whole dictionary from an xml file
	class Configuration
	{
	private:
		/// Data structure to hold the options map
		TConfigMap configMap;

	public:
		/// Default constructor
		Configuration();
		/// Destructor
		~Configuration();
		
		//Import/Export methods

		/// Load a dictionary from the given fileName as an XML
		/// @param fileName	the name of the file from which the options map will be loaded
		/// @param flags	optional flags
		/// @return <b>true</b> if the file was correctly loaded;
		bool loadFromFile(const std::string& fileName, unsigned int flags=0);
		/// Save the contents of the options map to the given filename as an XML
		/// @param fileName	the name of the file where the options map will be saved to
		/// @return <b> true</b> if the file was saved correctly
		bool saveToFile(const std::string& fileName, unsigned int flags=0) const;

		/// Replace options map with the one from the argument list
		/// @param newMap	options map to replace the current one with
		void setMap(const TConfigMap& newMap);

		/// Add pairs <key,value> from newMap. Depending on the value of replaceExisting,
		/// the values for those keys already present in the map will be overwritten or not.
		/// @param newMap			dictionary containing the options to be added
		/// @param replaceExisting	if true, the values for the keys already found on the map 
		///							will be overwritten
		void addOptions(const TConfigMap& newMap, bool replaceExisting=true);

		/// Tell if the given key is present in the config map
		/// @param key	key to query
		/// @return <b>true</b> if the given key is found on the options map
		bool hasOption(const std::string& key) const;

		///If the map has the given key, then set the 'value' parameter accordingly and return true;
		///Otherwise, return false
		/// @param key		key to query
		/// @param value	if the key's found on the map, this parameter will hold the value from the 
		///					pair
		/// @return <b>true if the given option's been found on the map
		bool getOption(const std::string& key,std::string& value);

		/// Set the 'key' option to the specified value provided that the key is not found on the map 
		/// or replaceExisting is true
		/// @param key				key of the option pair to set
		/// @param value			value of the option pair
		/// @param replaceExisting  if true and key is found on the map, the value will be overwritten
		void setOption (const std::string& key, const std::string& value, bool replaceExisting=true);

		//Provide indirect access to the map (This can be useful when we need to traverse the map)
		
		/// Return const iterator to the beginning of the options map, so it can be traversed easily
		/// @return iterator to the beginning of the options map
		TConfigMapConstIterator  begin() const;
		/// Return const iterator to the end of the options map, so it can be traversed easily
		/// @return iterator to the end of the options map
		TConfigMapConstIterator  end() const;

		std::string operator[](const std::string& key);

		bool isEmpty() const;
		double parseDouble(const std::string& key);
		int parseInt(const std::string& key);
		long parseLong(const std::string& key);
		float parseFloat(const std::string& key);
		bool parseBool(const std::string& key);
	};
}

#endif