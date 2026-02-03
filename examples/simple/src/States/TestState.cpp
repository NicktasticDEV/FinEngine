#include "TestState.h"

#include <FinEngine.h>
#include "FinEngine/Log.h"

void TestState::create() {
    LOG_INFO("TestState", "Initialized");
    
    colorfulObject = new Colorful();
    add(colorfulObject);
}

void TestState::update() {
    FinEngine::FinState::update();
    
}

void TestState::destroy() {
    FinEngine::FinState::destroy();

    delete colorfulObject;
    colorfulObject = nullptr;

    LOG_INFO("TestState", "Cleaned up");
}