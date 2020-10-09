#include "inip.hpp"
#include <iostream>
using namespace std;

int main()
{
	inip::INI ini;
	ini.LoadFromFile("test.ini");

	ini.globalProperties.push_back(inip::Property("testkey1", "value111"));
	ini.globalProperties.push_back(inip::Property("testkey2", "value 222"));
	ini.globalProperties.push_back(inip::Property("testkey3", "value  333"));
	ini.globalProperties.push_back(inip::Property("testkey4", "value   #444"));

	inip::Property p = ini.FindGlobalProperty("testkey4");
	std::cout << "Value of key testkey4: \'" << p.value << "\'" << std::endl;

	std::cout << "Global properties:" << std::endl;
	for (auto &p : ini.globalProperties)
		std::cout << "\t" << p.key << "[" << p.hash << "]: " << p.value << std::endl;

	std::cout << "Sections:" << std::endl;
	for (auto &s : ini.sections)
	{
		std::cout << "\t" << s.name << "[" << s.hash << "]:" << std::endl;
		for (auto &p : s.properties)
			std::cout << "\t\t" << p.key << "[" << p.hash << "]: " << p.value << std::endl;
	}

	std::cout << "\n\nNew ini data:\n" << ini.SaveToString() << std::endl;
	ini.SaveToFile("newfile.ini");
	
	try
	{
		inip::Property &p2 = ini.FindSection("DEBUG").FindProperty("EnableChannelControl");
		cout << "Found!" <<  p2.hash << p2.key << endl;
	}
	 catch (NoSuchParameterException &e) 
	{
        cout << e.what() << endl;
    }
	
	cout << "Now trying to find [NCMD] " << '\n';
	try
	{
		inip::Section &s = ini.FindSection("NCMD");
		cout << "Found!\n" << "[" << s.name << "]" << endl;
	}
	 catch (SectionNotFoundException &e) 
	{
        cout << e.what() << endl;
    }
	return 0;
}
