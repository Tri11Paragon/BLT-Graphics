#pragma once

#include <iostream>
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
            typedef std::variant<int32_t, float, bool, std::string> property_t;
            Settings() = default;
            
            ~Settings() = default;
            
            [[nodiscard]] const property_t* getProperty(properties_t property) const {
                if (values.size() <= static_cast<int>(property))
                    return nullptr;
                return &values[static_cast<int>(property)];
            }
            
            template<typename T>
            [[nodiscard]] const T* getProperty(properties_t property) const {
                if ((int)values.size() <= static_cast<int>(property))
                    return nullptr;
                return &get<T>(values[static_cast<int>(property)]);
            }
            
            void setProperty(properties_t property, property_t value) {
                if (values.capacity() <= static_cast<int>(property))
                    values.resize(static_cast<int>(property) * 2);
                values[static_cast<int>(property)] = std::move(value);
            }
        
        private:
            std::vector<property_t> values;
    };
}