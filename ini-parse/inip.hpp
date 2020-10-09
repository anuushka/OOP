#if !defined(INIP_H_)
#define INIP_H_

#include <string>
#include <cstdint>
#include <vector>
#include <sstream>
#include <type_traits>
#include <exception>
#include "exception.h"


namespace inip
{
	struct Util
	{
		typedef uint64_t Hash;
		static Hash HashFunc(std::string value);

		static std::string& LTrim(std::string &str);
		static std::string& RTrim(std::string &str);
		static std::string& Trim(std::string &str);

		template <typename T>
		static std::string ToStr(T val);
	};

	struct Property
	{
		Util::Hash hash;
		std::string key;
		std::string value;

		Property(std::string key, std::string value);

		bool ToBool();
		int ToInt();
		float ToFloat();
	};

	class Section
	{
	public:
		Util::Hash hash;
		std::string name;
		std::vector<Property> properties;

	public:
		Section(std::string name);

		Property& FindProperty(std::string key);
	};

	class INI
	{
	public:
		std::vector<Property> globalProperties;
		std::vector<Section> sections;

	public:
		bool LoadFromFile(std::string filename);
		void LoadFromString(std::string ini);

		bool SaveToFile(std::string filename);
		std::string SaveToString();

		Section& FindSection(std::string name);
		Property& FindGlobalProperty(std::string key);

		void AddSection(std::string name); // adds a section
		void AddProperty(std::string key, std::string value); // if no section exists, it will add a global property
	};
	

	template <typename T>
	std::string Util::ToStr(T val)
	{
		std::ostringstream ss;
		ss << val;
		return ss.str();
	}

}

#endif
