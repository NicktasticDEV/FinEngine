#pragma once
#include <FinEngine.h>
#include "Objects/Colorful.h"

class TestState : public FinEngine::FinState {

    public:
        void create() override;
        void update() override;
        void destroy() override;

    private:
        Colorful* colorfulObject;
        
};