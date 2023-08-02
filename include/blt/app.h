#pragma once

#include <fstream>
#include "traits.h"
#include <utility>
#include <vector>
#include "blt/std/logging.h"
#include "status.h"
#include "error_logging.h"
#include <variant>

namespace blt::graphics {
    enum class properties_t : int {
        // The display window's title
        WINDOW_TITLE,
        // the initial display width/height. This value does not change if the window is resized. Use Window::getWidth and Window::getHeight
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        WINDOW_RESIZABLE,
        RENDER_MODE, // INT
    };
    
    class Settings {
        public:
            typedef std::variant<int32_t, int64_t, float, bool, std::string> property_t;
            Settings() = default;
            Settings(std::initializer_list<std::pair<properties_t, property_t>> default_properties){
                for (const auto& v : default_properties)
                    setProperty(v.first, v.second);
            }
            
            ~Settings() = default;
            
            [[nodiscard]] inline const property_t* getProperty(properties_t property) const {
                if (values.size() <= static_cast<int>(property))
                    return nullptr;
                return &values[static_cast<int>(property)];
            }
            
            template<typename T>
            [[nodiscard]] inline  const T* getProperty(properties_t property) const {
                if ((int)values.size() <= static_cast<int>(property))
                    return nullptr;
                return &get<T>(values[static_cast<int>(property)]);
            }
            
            inline void setProperty(properties_t property, property_t value) {
                if (values.capacity() <= static_cast<int>(property))
                    values.resize(static_cast<int>(property) * 2);
                values[static_cast<int>(property)] = std::move(value);
            }
            
            bool save(std::ofstream& out);
            bool load(std::ifstream& in);
        
        private:
            std::vector<property_t> values;
            // handles saving of the variant's value
            class property_saver {
                private:
                    std::ofstream& out;
                public:
                    explicit property_saver(std::ofstream& out): out(out){}
                    inline void operator()(int32_t i) {
                        out << i;
                    }
                    inline void operator()(int64_t l){
                        out << l;
                        out << "l";
                    }
                    inline void operator()(float f){
                        out << f;
                        out << "f";
                    }
                    inline void operator()(bool b){
                        out << b;
                        out << "b";
                    }
                    inline void operator()(const std::string& s) {
                        out << s;
                    }
            };
    };
}