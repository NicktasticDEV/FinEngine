#pragma once

#include "FinEngine/FinEngineAPI.h"

namespace FinEngine {

    class FINENGINE_API FinBasic {
        public:
            virtual void init() = 0;
            virtual void update() = 0;
            virtual void render() = 0;
            virtual void destroy() = 0;

            bool visible = true;
            bool active = true;
    };

}
