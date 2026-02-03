#pragma once

#include <FinEngine.h>
#include <cmath>

class Colorful : public FinEngine::FinBasic {
    private:
        unsigned int frameCount = 0;
        float sinValue = 0.0f;

    public:
        void update() override {
            frameCount++;

            sinValue = (std::sin(frameCount * 0.025f) + 1.0f) / 8.0f + 0.2f;
        }

        void draw() override {
            FinEngine::FinGame::instance().GetGraphics().ClearScreen(0.2f, sinValue, 0.3f, 1.0f);
        }

};