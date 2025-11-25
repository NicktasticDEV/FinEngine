#pragma once

#include "FinEngine/FinEngineAPI.h"

namespace FinEngine {

    class FINENGINE_API FinBasic {
        public:
            FinBasic() {};
            virtual ~FinBasic() = default;

            virtual void update() {};
            virtual void draw() {};
            virtual void destroy() {};

            bool visible = true;
            bool active = true;
    };

}
