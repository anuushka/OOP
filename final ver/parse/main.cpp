#include <iostream>
#include "inip.h"

using namespace std;

int main() {
	
	IniParser ini;
	
    try 
	{
		ini.ParseINI("newfile.ini");
    } 
    catch(IOException &e)
    {
    	cout << "File exception detected: " << e.what() << '\n';
		return 0;
	}
	
	cout << ini.SaveToString() << endl;
	
    try
    {
        cout << ini.FindValue<string>("ADC_DEV", "BufferLenSeconds") << endl;
        cout << ini.FindValue<string>("ADC_DEV", "blank") << endl;
	}
	
	catch (PropertyException &e) 
	{
        cout << "Property exception detected: " << e.what() << endl;
    }
    
    try
	{
		cout << ini.FindValue<string>("TESTS", "testkey1") << endl;
		cout << ini.FindValue<string>("DEMODS", "blank") << endl;
	}
	catch(SectionException &e)
	{
		cout << "Section exception detected: " << e.what() << endl;
	}
	  
    return 0;
}


