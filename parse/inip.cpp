#include <iostream>
#include <algorithm>
#include <sstream>
#include "inip.h"

using namespace std;

	
// ################### Parser ###################

void IniParser::ParseINI(string const &filename) {
    ifstream file(filename, std::ios::in);
    if (!file) throw IOException(filename);
    string sections;
    string line;
    while (!file.eof() && getline(file, line)) {
        line.erase( std::find( line.begin(), line.end(), ';' ), line.end() );
        if (line.length() == 0) continue;
        if (line.find('[') != string::npos) {
        	sections = line.substr(line.find('[') + 1, line.find(']') - 1);
            continue;
        }
        pair<string, string> properties = FindProperty(line);
        data[sections][properties.first] = properties.second;
    }
    file.close();
    isInitialised = true;
}

// ################### Property ###################

pair<string, string> IniParser::FindProperty(string &line) const {
    line.erase(remove(line.begin(), line.end(), ' '), line.end());
    string key = line.substr(0, line.find('='));
    string value = line.substr(line.find('=') + 1);
    return {key, value};
}

template<>
std::string IniParser::FindValue<string>(string const &section,
                                        string const &key) const {
	if(data.count(section) == 0) //that section doesn't exist in map
	{
		throw SectionException(section);
	}
    else if(data.at(section).count(key) == 0) //that key doesn't exist in map[sections]
	{
    	throw PropertyException(key);
    }
		return data.at(section).at(key);
}

template<>
int IniParser::FindValue<int>(string const &section,
                             string const &key) const {

    if(data.count(section) == 0) //that section doesn't exist in map
	{
		throw SectionException(section);
	}
    else if (data.at(section).count(key) == 0) //that key doesn't exist in map[sections]
	{
    	throw PropertyException(key);
    }  
    	return stoll(data.at(section).at(key)); //stoll can handle exceptions (Don't use atoi 'cause it can't)
}

template<>
double IniParser::FindValue<double>(string const &section,
                                   string const &key) const {
    if(data.count(section) == 0) //that section doesn't exist in map
	{
		throw SectionException(section);
	}
    else if (data.at(section).count(key) == 0) //that key doesn't exist in map[sections]
	{
    	throw PropertyException(key);
    } 
    	return stod(data.at(section).at(key)); //stod can handle exceptions ((Don't use atof 'cause it can't)
}

// ################### Output ###################

const string IniParser::SaveToString() const {
	std::stringstream ss;
    for (auto s : data) {
        ss << "["  << s.first << "]" << endl;
        map<string, string> properties = s.second;
        for (auto p : properties) {
            ss << p.first << "=" << p.second << endl;
        }
		ss << std::endl;
    }
	return ss.str();
}




