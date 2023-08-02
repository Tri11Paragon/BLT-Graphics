#include "blt/app.h"
#include <blt/std/string.h>
#include <algorithm>

namespace blt::graphics {
    
    bool Settings::save(std::ofstream& out) {
        BLT_DEBUG("Saving settings");
        out << "# Warning: this file does not allow for comments or any form of manual modification!\n";
        out << "# All comments will be ignored, however changes will be accepted assuming the application is not running.\n";
        property_saver saver(out);
        try {
            for (size_t i = 0; i < values.size(); i++) {
                out << static_cast<int>(i);
                out << " = ";
                std::visit(saver, values[i]);
                out << '\n';
            }
        } catch (std::exception& e){
            BLT_ERROR("Error in settings save (%s)!", e.what());
            return false;
        }
        return true;
    }
    
    bool Settings::load(std::ifstream& in) {
        BLT_DEBUG("Loading settings");
        try {
            size_t currentLine = 0;
            while(!(in.eof() || in.fail())){
                currentLine++;
                std::string line;
                std::getline(in, line);
                blt::string::trim(line);
                
                if (line.starts_with('#') || line.empty())
                    continue;
                
                auto propertyToValue = blt::string::split(line, "=");
                for (auto& s : propertyToValue)
                    blt::string::trim(s);
                
                if (propertyToValue.size() < 2) {
                    BLT_WARN("Improperly formed key = value pair! Ignoring line %d ('%s')", currentLine, line.c_str());
                    continue;
                }
                
                auto property = static_cast<properties_t>(std::stoi(propertyToValue[0]));
                auto& value = propertyToValue[1];
                
                if (std::any_of(value.begin(), value.end(), ::isdigit)){
                    if (value.ends_with('l')) {
                        setProperty(property, std::stoll(value.substr(0, value.size()-1)));
                    } else if (value.ends_with('f')) {
                        setProperty(property, std::stof(value.substr(0, value.size()-1)));
                    } else if (value.ends_with('b')) {
                        setProperty(property, static_cast<bool>(std::stoi(value.substr(0, value.size()-1))));
                    } else
                        setProperty(property, std::stoi(value));
                } else
                    setProperty(property, value);
            }
        } catch (std::exception& e){
            BLT_ERROR("Error in settings load (%s)!", e.what());
            return false;
        }
        return true;
    }
}