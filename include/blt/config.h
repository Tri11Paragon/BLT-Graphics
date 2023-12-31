//
// Created by brett on 6/11/23.
//

#ifndef PARKSNREC_CONFIG_H
#define PARKSNREC_CONFIG_H

#include <unordered_map>

namespace blt::graphics {

# define PI           3.14159265358979323846
    inline double degreeToRad(double deg){
        return deg * (PI / 180);
    }
    
    // Build Config
#define BUILD_DEV_TOOLS
//#define BUILD_RELEASE_MODE
    
    // Types
    template<typename K, typename V, typename hash = std::hash<K>>
    using hashmap = std::unordered_map<K, V, hash>;



}

#endif //PARKSNREC_CONFIG_H
