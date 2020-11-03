#pragma once
#include <exception>
#include <stdexcept>

class IniException : public std::runtime_error {
public:
    explicit IniException(const std::string &__arg) : runtime_error(__arg) {}
};

class IOException : public IniException {
	
private:
    std::string filename;

public:
    explicit IOException(const std::string &filename) : IniException(filename + " doesn't exist or can't be read"),
                                                        filename(filename) {}

    std::string getFileName() const {
        return filename;
    }
};

class FileNotInitialisedException : public IniException {
public:
    explicit FileNotInitialisedException() : IniException("File couldn't be initialized") {}
};

class SectionException : public IniException {
	
private:
    std::string section;
    
public:
    explicit SectionException(const std::string &section) : IniException(
            "Section: " + section + " doesn't exist"), section(section) {}

    std::string GetSectionName() const {
        return section;
    }
};

class PropertyException : public IniException {

private:
    std::string Property;
    
public:
    explicit PropertyException(const std::string &Property) : IniException(
            "Parameter: " + Property + " doesn't exist"), Property(Property) {}

    std::string GetPropertyName() const {
        return Property;
    }
};
