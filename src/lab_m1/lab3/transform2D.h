#pragma once
#include "utils/glm_utils.h"

namespace transform2D {

    inline glm::mat3 Translate(float translateX, float translateY) {
        // calculul matricei de translatie 
        
        return glm::transpose(glm::mat3(1, 0, translateX, 0, 1, translateY, 0, 0, 1));
    }

    inline glm::mat3 Scale(float scaleX, float scaleY) {
        // calculul matricei de scalare

        return glm::mat3(scaleX, 0, 0, 0, scaleY, 0, 0, 0, 1);
    }

    inline glm::mat3 Rotate(float radians) {
        // calculul matricei de rotatie 
        
        float c = cos(radians), s = sin(radians);
        return glm::mat3(c, s, 0, -s, c, 0, 0, 0, 1);
    }
}   
