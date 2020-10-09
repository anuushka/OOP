#pragma once
#include <fstream>
#include <map>
#include <string>
#include "exception.h"

class IniParser {
	
	private:
    std::map<std::string, std::map<std::string, std::string>> data;
    bool isInitialised = false;
    std::pair<std::string, std::string> FindProperty(std::string &line) const;
    
	public:
    void ParseINI(std::string const &filename);
    template<typename T>
    T FindValue(std::string const &section, std::string const &key) const;
    const std::string SaveToString() const;
};


