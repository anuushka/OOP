#include "inip.hpp"
#include <cstddef>
#include <fstream>
#include <sstream>
#include <cctype>
#include <algorithm>


namespace inip
{
	// ################### Util ###################

	Util::Hash Util::HashFunc(std::string value)
	{
		Hash hash = 14695981039346656037ull;
		for (size_t i = 0; i <= value.length(); i++)
		{
			hash ^= value[i];
			hash *= 1099511628211ull;
		}
		return hash;
	}

	std::string& Util::LTrim(std::string &str)
	{
		auto it = std::find_if(str.begin(), str.end(), [](char ch) { return !std::isspace(ch); });
		str.erase(str.begin(), it);
		return str;
	}

	std::string& Util::RTrim(std::string &str)
	{
		auto it = std::find_if(str.rbegin(), str.rend(), [](char ch) { return !std::isspace(ch); });
		str.erase(it.base(), str.end());
		return str;
	}

	std::string& Util::Trim(std::string &str)
	{
		return LTrim(RTrim(str));
	}

	// ################### Parser ###################

	void ParseINI(INI *ini, std::string &data)
	{
		std::istringstream ss(data);
		std::string line;

		while (std::getline(ss, line))
		{
			line = Util::Trim(line);
			line.erase( std::find( line.begin(), line.end(), ';' ), line.end() );
							
			if (line.length() == 0) continue;

			if (line.front() == '#' || line.front() == ';')
			{
				continue;
			}
			else if (line.front() == '[')
			{
				if (line.back() == ']')
				{
					std::string name = line.substr(1, line.length() - 2);
					ini->AddSection(name);
				}
				else throw ("Invalid syntax");
			}
			else
			{
				auto result = std::find(line.begin(), line.end(), '=');
				if (result == line.end()) throw ("Invalid syntax");

				std::string key(line.begin(), result);
				key = Util::RTrim(key);
				std::string value(result + 1, line.end());
				value = Util::LTrim(value);
				ini->AddProperty(key, value);
			}
		}
	}

	// ################### Property ###################

	Property::Property(std::string key, std::string value) :
		hash(Util::HashFunc(key)), key(key), value(value)
	{}

	bool Property::ToBool()
	{
		if (value == "false" || value == "0")
			return false;
		else if (value == "true" || value == "1")
			return true;
		else throw ("Invalid syntax");
	}

	int Property::ToInt()
	{
		return std::atoi(value.c_str());
	}

	float Property::ToFloat()
	{
		return std::atof(value.c_str());
	}

	// ################### Section ###################

	Section::Section(std::string name) :
		hash(Util::HashFunc(name)), name(name)
	{}

	Property& Section::FindProperty(std::string key)
	{
		Util::Hash hash = Util::HashFunc(key);
		for (auto &property : properties)
			if (hash == property.hash)
				return property;
		throw NoSuchParameterException(key);
	}

	bool INI::LoadFromFile(std::string filename)
	{
		std::ifstream file(filename, std::ios::in);
		if (!file) throw IOException(filename);
		std::string data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
		file.close();
		LoadFromString(data);
		return true;
	}

	void INI::LoadFromString(std::string ini)
	{
		ParseINI(this, ini);
	}

	bool INI::SaveToFile(std::string filename)
	{
		std::string data = SaveToString();
		std::ofstream file(filename, std::ios::out);
		if (!file) return false;
		file << data;
		file.close();
		return true;
	}

	std::string INI::SaveToString()
	{
		std::stringstream ss;

		for (Property &p : globalProperties)
			ss << p.key << "=" << p.value << std::endl;

		for (Section &s : sections)
		{
			ss << std::endl << "[" << s.name << "]" << std::endl;
			for (Property &p : s.properties)
				ss << p.key << "=" << p.value << std::endl;
		}
		ss << std::endl;

		return ss.str();
	}

	Section& INI::FindSection(std::string name)
	{
		Util::Hash hash = Util::HashFunc(name);
		for (auto &section : sections)
			if (hash == section.hash)
				return section;
        throw SectionNotFoundException(name);
	}

	Property& INI::FindGlobalProperty(std::string key)
	{
		Util::Hash hash = Util::HashFunc(key);
		for (auto &property : globalProperties)
			if (hash == property.hash)
				return property;
		throw NoSuchParameterException(key);
	}

	void INI::AddSection(std::string name)
	{
		sections.push_back(Section(name));
	}

	void INI::AddProperty(std::string key, std::string value)
	{
		if (sections.size() == 0)
			globalProperties.push_back(Property(key, value));
		else
			sections.back().properties.push_back(Property(key, value));
	}

}
