#pragma once

#include "FinEngine/FinEngineAPI.h"
#include "FinEngine/Core/FinGroup.h"
#include "FinEngine/Core/FinBasic.h"

namespace FinEngine {

    class FINENGINE_API FinState : public FinGroup  {
        public:

            virtual void create() {};
            void update() override;
            void draw() override;
            void destroy() override;
    };

}
